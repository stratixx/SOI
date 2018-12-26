#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../inc/main.h"
#include "../inc/tools.h"
#include "../inc/queue.h"
#include "../inc/producer.h"
#include "../inc/prosumer.h"
#include "../inc/special.h"
#include "../inc/protector.h"


Queue queue[QUEUE_NUMBER];


int main(int argc, char * argv[])
{
    int tmp, count;

    char * args[3];


	if(argc != 2 )
	{
		printf("Bad number of input arguments!\n");
		printf("Should be: project3.bin <prosumer_pr>\n");
		return -2;
	}
	
    args[0] = argv[0];
    args[2] = argv[1];
    #define WAIT_TIME 300

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
    usleep(WAIT_TIME);

    fork_child(protector, 1, args);


    count = 0;
    while( count <= (5*60*1000/250))
    {
        MAIN_PRINT_CMD(for(tmp=0; tmp<QUEUE_NUMBER; tmp++) printf("%c: %d | ", tmp+'A', queue[tmp].count);)
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
