#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../inc/protector.h"
#include "../inc/tools.h"
#include "../inc/queue.h"

    
extern Queue queue[QUEUE_NUMBER];


int protector(int argc, char* argv[])
{    
    // dostaje jako argument częstotliwosć akcji
    Message_t msg;
    float pr;
    int full_id[QUEUE_NUMBER], empty_id[QUEUE_NUMBER], mutex_id[QUEUE_NUMBER];
    int tmp, readed;

    sprintf(msg.producer, "_Protector_" );  
    
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        full_id[tmp] =  semget(SEM_FULL_KEY(tmp+'A') , 1, 0600);	     
        empty_id[tmp] = semget(SEM_EMPTY_KEY(tmp+'A'), 1, 0600);     
        mutex_id[tmp] = semget(SEM_MUTEX_KEY(tmp+'A'), 1, 0600);
    }

    msg.priority = 1;
    msg.valid = 1;

    rand_init();

	while(1)
	{
        /* generate random message */
        for(tmp=0; tmp<DATA_SIZE; tmp++)
            msg.data[tmp] = rand_value('A', 'C');

        /* select random queue */    
        tmp = rand_value('A', 'C')-'A';

        /* send message to selected queue */
		sem_down(empty_id[tmp], 0);
		sem_down(mutex_id[tmp], 0);

		queue[tmp].send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, tmp+'A', msg.data, queue[tmp].count, QUEUE_SIZE);)

		sem_up(mutex_id[tmp], 0);
		sem_up(full_id[tmp], 0);	

        /* wait */
        sleep(PROTECTOR_SLEEP_TIME);
	}	

    printf("%s end\n", msg.producer);
    return 0;
}