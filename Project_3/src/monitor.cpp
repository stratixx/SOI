#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sem.h>
#include <string.h>
#include "../inc/tools.h"
#include "../inc/monitor.h"


Monitor::Monitor(char key)
{
    printf("Monitor constructor: %c\n\r", key);

    full_id = semget(SEM_FULL_KEY(key), 1, IPC_CREAT|IPC_EXCL|0600);	
    semctl(full_id, 0, SETVAL, (int)0);        
    empty_id = semget(SEM_EMPTY_KEY(key), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(empty_id, 0, SETVAL, QUEUE_SIZE);          
    mutex_id = semget(SEM_MUTEX_KEY(key), 1, IPC_CREAT|IPC_EXCL|0600);
    semctl(mutex_id, 0, SETVAL, (int)1);

}

void Monitor::enter()
{
	sem_down(mutex_id, 0);
}

void Monitor::leave()
{
	sem_up(mutex_id, 0);
}

void Monitor::wait_full()
{
    sem_down(empty_id, 0);
}

void Monitor::signal_full()
{
	sem_up(empty_id, 0);
}


void Monitor::wait_empty()
{
    sem_down(full_id, 0);
}

void Monitor::signal_empty()
{
	sem_up(full_id, 0);
}
