#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <string.h>
#include "../inc/tools.h"



void sem_down(int semid, int semnum, struct sembuf * buf)
{
    buf->sem_num = semnum;
    buf->sem_op = -1;
    buf->sem_flg = 0;
    if (semop(semid, buf, 1) == -1)
    {
        perror("sem_down: EXIT ERROR -1");
        exit(-1);
    }
}

void sem_up(int semid, int semnum, struct sembuf * buf)
{
    buf->sem_num = semnum;
    buf->sem_op = 1;
    buf->sem_flg = 0;
    if (semop(semid, buf, 1) == -1)
    {
        perror("sem_up: EXIT ERROR -1");
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