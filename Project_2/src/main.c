#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../inc/main.h"
#include "../inc/tools.h"
#include "../inc/producer.h"
#include "../inc/prosumer.h"
#include "../inc/special.h"


int main(int argc, char * argv[])
{
    int queue_id[QUEUE_NUMBER];
    Queue_t* queue[QUEUE_NUMBER];
    int full_id[QUEUE_NUMBER];
    int empty_id[QUEUE_NUMBER];
    int mutex_id[QUEUE_NUMBER];
    int tmp, count;

    char * args[3];


    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        queue_id[tmp] = shmget(QUEUE_KEY(tmp+'A'), sizeof(Queue_t), IPC_CREAT|0666);
        queue[tmp] = (Queue_t*)shmat(queue_id[tmp], NULL, 0);
        queue_init(queue[tmp]);

        full_id[tmp] = semget(SEM_FULL_KEY(tmp+'A'), 1, IPC_CREAT|IPC_EXCL|0600);	
        semctl(full_id[tmp], 0, SETVAL, (int)0);        
        empty_id[tmp] = semget(SEM_EMPTY_KEY(tmp+'A'), 1, IPC_CREAT|IPC_EXCL|0600);
        semctl(empty_id[tmp], 0, SETVAL, QUEUE_SIZE);          
        mutex_id[tmp] = semget(SEM_MUTEX_KEY(tmp+'A'), 1, IPC_CREAT|IPC_EXCL|0600);
        semctl(mutex_id[tmp], 0, SETVAL, (int)1);
    }

	if(argc != 2 )
	{
		printf("Bad number of input arguments!\n");
		return -2;
	}
	
    args[0] = argv[0];
    args[2] = argv[1];
    #define WAIT_TIME 200

    args[1] = "A";
    fork_child(prosumer, 3, args);
    usleep(WAIT_TIME);
    args[1] = "B";
    fork_child(prosumer, 3, args);
    usleep(WAIT_TIME);
    args[1] = "C";
    fork_child(prosumer, 3, args);
    usleep(WAIT_TIME);

    args[1] = "A";
    fork_child(producer, 2, args);
    usleep(WAIT_TIME);
    args[1] = "B";
    fork_child(producer, 2, args);
    usleep(WAIT_TIME);
    args[1] = "C";
    fork_child(producer, 2, args);
    usleep(WAIT_TIME);

    fork_child(special, 1, args);

    count = 0;
    while( count <= (60*1000/250))
    {
        MAIN_PRINT_CMD(for(tmp=0; tmp<QUEUE_NUMBER; tmp++) printf("%c: %d | ", tmp+'A', queue[tmp]->count);)
        MAIN_PRINT_CMD(printf("time: %.2fs\n", (float)(count*250.0/1000));)
        
        usleep(1000*250);
        count++;
    }
	
	while(wait(&tmp) != -1)
    {
    }	

	return 0;
}

/*
*
*/
void fork_child(int (*child)(int, char**), int argc, char * argv[])
{
	if( fork()==0 )
	{
        // only child will enter here
		exit(child(argc, argv));
	}
	/* only parrent will return from function */
}
