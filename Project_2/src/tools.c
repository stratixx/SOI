#include <stdio.h>
#include <stdlib.h>
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

int get_queue_size(Queue_t *q)
{
	return q->count;
}

int send_msg(Queue_t *q, Message_t *msg)
{
	if(msg->priority == 1)
	{
		q->head = (q->head - 1);
        	if(q->head < 0) q->head = QUEUE_SIZE - 1;
            copy_msg(&q->table[q->head], msg);
        	//q->table[q->head] = msg;
	}
	else
	{
        copy_msg(&q->table[q->tail], msg);
		//q->table[q->tail] = msg;
		q->tail = (q->tail + 1) % QUEUE_SIZE;
	}
	q->count++;
    return 0;
}

Message_t* read_msg(Queue_t *q, Message_t *msg)
{	
	//Message_t m;
    copy_msg(msg, &q->table[q->head]);
    q->table[q->head].valid = 0;
	//m = q->table[q->head];
	q->head = (q->head+1) % QUEUE_SIZE;
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