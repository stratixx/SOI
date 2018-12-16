#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <string.h>
#include "../inc/tools.h"


void queue_init(Queue_t *q)
{
    int n;
	q->head = 0;
	q->tail = 0;
	q->count = 0;	
    for(n=0; n<QUEUE_SIZE; n++)
        q->table[n].valid = 0;
    q->valid = 1;
}

void copy_msg(Message_t *dest, const Message_t *src)
{
	dest->priority = src->priority;
    memcpy(dest->producer, src->producer, MESSAGE_PRODUCER_LENGTH);
    memcpy(dest->data, src->data, DATA_SIZE);
    dest->next = src->next;
    dest->valid = src->valid;  
}

int send_msg(Queue_t *q, Message_t *msg)
{
    int tmp, msg_index;

    if(q->count>=QUEUE_SIZE)
    {
        printf("send_msg: queue is full!");
        exit(-4);
    }

    for(msg_index=0; msg_index<=QUEUE_SIZE; msg_index++)
        if( q->table[msg_index].valid==0 )
            break;

    
    if(msg_index>=QUEUE_SIZE)
    {
        printf("send_msg: data corruption, there is no empty message slot!");
        exit(-5);
    }

    copy_msg(&q->table[msg_index], msg);
    q->table[msg_index].valid = 1;
    q->table[msg_index].next = QUEUE_NO_MSG;
    
    if(q->count==0)
    {
        /* first message in queue */
        q->tail = msg_index;
        q->head = msg_index;

        q->count++;
        return q->count;
    }

	if(msg->priority == 1)
	{
        if( q->table[q->head].priority==0 )
        {
            /* insert priority message as head */
            q->table[msg_index].next = q->head;
            q->head = msg_index;
        }
        else
        {
            tmp = q->head;
            /* tmp element is tail or next element is first non-priority message in queue */
            while( tmp!=q->tail && q->table[q->table[tmp].next].priority==1 )
                tmp = q->table[tmp].next;
            if(tmp==q->tail)
                q->tail = msg_index;
            q->table[msg_index].next = q->table[tmp].next;
            q->table[tmp].next = msg_index;
        }
	}
	else
	{
        /* insert message at end of queue */
        q->table[q->tail].next = msg_index;
        q->tail = msg_index;
	}
	q->count++;
    return q->count;
}

Message_t* read_msg(Queue_t *q, Message_t *msg)
{	
	//Message_t m;
    if(q->count<=0)
    {
        printf("read_msg: no messages in queue!");
        exit(-3);
    }
    copy_msg(msg, &q->table[q->head]);
    q->table[q->head].valid = 0;
	//m = q->table[q->head];
    q->head = q->table[q->head].next;
	q->count--;
	
	return msg;
}

void sem_down(int semid, int semnum)
{
    struct sembuf buf;
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("sem_down: EXIT ERROR -1");
        exit(-1);
    }
}

void sem_up(int semid, int semnum)
{
    struct sembuf buf;
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1)
    {
        perror("sem_UP: EXIT ERROR -1");
        exit(-1);
    }
}

/*
*
*/
void rand_init()
{
    static int initiated = 0;
    if( initiated!=0 )
        return;
    srand(time(NULL));
    
    initiated = 1;
}

/*
*
*/
int rand_value(int min, int max)
{
    int val;

    val = rand() % (max-min+1) + min;
    return val;
}

/*
*
*/
int rand_bool(float pr)
{
    float val;
    val = rand() %1000;
    val = val /1000;
    if(pr>val)
        return 1;
    else
        return 0;
}