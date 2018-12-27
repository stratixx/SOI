#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <string.h>
#include "../inc/tools.h"
#include "../inc/queue.h"

char Queue::last_queue = 'A'-1;

Queue::Queue(char queue_name)
{
    int n;
    Queue::last_queue++;
    queue_name = queue_name;
    //printf("queue constructor: %c\n\r", queue_name);

    full_id = semget(SEM_FULL_KEY(queue_name), 1, IPC_CREAT|IPC_EXCL|0600);	
    semctl(full_id, 0, SETVAL, (int)0);        
    empty_id = semget(SEM_EMPTY_KEY(queue_name), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(empty_id, 0, SETVAL, QUEUE_SIZE);          
    mutex_id = semget(SEM_MUTEX_KEY(queue_name), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(mutex_id, 0, SETVAL, (int)1);

	head = 0;
	tail = 0;
	count = 0;	
    for(n=0; n<QUEUE_SIZE; n++)
        table[n].valid = 0;
    valid = 1;
}

void Queue::copy_msg(Message_t *dest, const Message_t *src)
{
	dest->priority = src->priority;
    memcpy(dest->producer, src->producer, MESSAGE_PRODUCER_LENGTH);
    memcpy(dest->data, src->data, DATA_SIZE);
    dest->next = src->next;
    dest->valid = src->valid;  
}

int Queue::send_msg(Message_t *msg)
{
    int tmp, msg_index;

    wait(empty_id);
	enter();

    if(count>=QUEUE_SIZE)
    {
        printf("send_msg: queue is full!");
        exit(-4);
    }

    for(msg_index=0; msg_index<=QUEUE_SIZE; msg_index++)
        if( table[msg_index].valid==0 )
            break;

    
    if(msg_index>=QUEUE_SIZE)
    {
        printf("send_msg: data corruption, there is no empty message slot!");
        exit(-5);
    }

    copy_msg(&table[msg_index], msg);
    table[msg_index].valid = 1;
    table[msg_index].next = QUEUE_NO_MSG;
    
    if(count==0)
    {
        /* first message in queue */
        tail = msg_index;
        head = msg_index;
    }
    else if(msg->priority == 2) /* priority equals 2 */
    {
        if( table[head].priority < 2 ) /* if head has lower priority than 2 */
        {
            /* insert priority message as head */
            table[msg_index].next = head;
            head = msg_index;
        }
        else
        {
            tmp = head;
            /* tmp element is tail or next element is first lower priority message in queue */
            while( tmp!=tail && table[table[tmp].next].priority>=2 )
                tmp = table[tmp].next;
            if(tmp==tail)
                tail = msg_index;
            table[msg_index].next = table[tmp].next;
            table[tmp].next = msg_index;
        }
    }
	else if(msg->priority == 1) /* priority equals 1 */
	{
        if( table[head].priority<1 ) /* if head has zero priority */
        {
            /* insert priority message as head */
            table[msg_index].next = head;
            head = msg_index;
        }
        else
        {
            tmp = head;
            /* tmp element is tail or next element is first non-priority message in queue */
            while( tmp!=tail && table[table[tmp].next].priority>=1 )
                tmp = table[tmp].next;
            if(tmp==tail)
                tail = msg_index;
            table[msg_index].next = table[tmp].next;
            table[tmp].next = msg_index;
        }
	}
	else if(msg->priority == 0) /* priority equals 0 */
	{
        /* insert message at end of queue */
        table[tail].next = msg_index;
        tail = msg_index;
	}
	else /* unsuported priority */
    {
        printf("send_msg: unsuported priority!");
        exit(-6);
    }
	count++;

	leave();
	signal(full_id);	

    return count;
}

Message_t* Queue::read_msg(Message_t *msg)
{			
    wait(full_id);
	enter();

    if(count<=0)
    {
        printf("read_msg: no messages in queue!");
        exit(-3);
    }
    copy_msg(msg, &table[head]);
    table[head].valid = 0;
	//m = table[head];
    head = table[head].next;
	count--;
	
	leave();
	signal(empty_id);	

	return msg;
}


void Queue::enter()
{
	sem_down(mutex_id, 0);
}

void Queue::leave()
{
	sem_up(mutex_id, 0);
}

void Queue::wait( int id )
{
    sem_down(id, 0);
}

void Queue::signal( int id )
{
	sem_up(id, 0);
}
