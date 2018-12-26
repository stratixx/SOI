#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <string.h>
#include "../inc/tools.h"
#include "../inc/queue.h"

char Queue::last_queue = 'A'-1;

Queue::Queue()
{
    int n;
    Queue::last_queue++;
    this->queue_name = Queue::last_queue;

    this->full_id = semget(SEM_FULL_KEY(this->queue_name), 1, IPC_CREAT|IPC_EXCL|0600);	
    semctl(this->full_id, 0, SETVAL, (int)0);        
    this->empty_id = semget(SEM_EMPTY_KEY(this->queue_name), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(this->empty_id, 0, SETVAL, QUEUE_SIZE);          
    this->mutex_id = semget(SEM_MUTEX_KEY(this->queue_name), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(this->mutex_id, 0, SETVAL, (int)1);

	this->head = 0;
	this->tail = 0;
	this->count = 0;	
    for(n=0; n<QUEUE_SIZE; n++)
        this->table[n].valid = 0;
    this->valid = 1;
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

    sem_down(this->empty_id, 0);
	sem_down(this->mutex_id, 0);

    if(this->count>=QUEUE_SIZE)
    {
        printf("send_msg: queue is full!");
        exit(-4);
    }

    for(msg_index=0; msg_index<=QUEUE_SIZE; msg_index++)
        if( this->table[msg_index].valid==0 )
            break;

    
    if(msg_index>=QUEUE_SIZE)
    {
        printf("send_msg: data corruption, there is no empty message slot!");
        exit(-5);
    }

    copy_msg(&this->table[msg_index], msg);
    this->table[msg_index].valid = 1;
    this->table[msg_index].next = QUEUE_NO_MSG;
    
    if(this->count==0)
    {
        /* first message in queue */
        this->tail = msg_index;
        this->head = msg_index;

        this->count++;
        return this->count;
    }

    
	if(msg->priority == 2) /* priority equals 2 */
    {
        if( this->table[this->head].priority < 2 ) /* if head has lower priority than 2 */
        {
            /* insert priority message as head */
            this->table[msg_index].next = this->head;
            this->head = msg_index;
        }
        else
        {
            tmp = this->head;
            /* tmp element is tail or next element is first lower priority message in queue */
            while( tmp!=this->tail && this->table[this->table[tmp].next].priority>=2 )
                tmp = this->table[tmp].next;
            if(tmp==this->tail)
                this->tail = msg_index;
            this->table[msg_index].next = this->table[tmp].next;
            this->table[tmp].next = msg_index;
        }
    }
	else if(msg->priority == 1) /* priority equals 1 */
	{
        if( this->table[this->head].priority<1 ) /* if head has zero priority */
        {
            /* insert priority message as head */
            this->table[msg_index].next = this->head;
            this->head = msg_index;
        }
        else
        {
            tmp = this->head;
            /* tmp element is tail or next element is first non-priority message in queue */
            while( tmp!=this->tail && this->table[this->table[tmp].next].priority>=1 )
                tmp = this->table[tmp].next;
            if(tmp==this->tail)
                this->tail = msg_index;
            this->table[msg_index].next = this->table[tmp].next;
            this->table[tmp].next = msg_index;
        }
	}
	else if(msg->priority == 0) /* priority equals 0 */
	{
        /* insert message at end of queue */
        this->table[this->tail].next = msg_index;
        this->tail = msg_index;
	}
	else /* unsuported priority */
    {
        printf("send_msg: unsuported priority!");
        exit(-6);
    }
	this->count++;

	sem_up(this->mutex_id, 0);
	sem_up(this->full_id, 0);	

    return this->count;
}

Message_t* Queue::read_msg(Message_t *msg)
{			
    sem_down(this->full_id, 0);
	sem_down(this->mutex_id, 0);

    if(this->count<=0)
    {
        printf("read_msg: no messages in queue!");
        exit(-3);
    }
    copy_msg(msg, &this->table[this->head]);
    this->table[this->head].valid = 0;
	//m = this->table[this->head];
    this->head = this->table[this->head].next;
	this->count--;
	
	sem_up(this->mutex_id, 0);
	sem_up(this->empty_id, 0);	

	return msg;
}
