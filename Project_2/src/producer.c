#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


#include "../inc/producer.h"
#include "../inc/tools.h"

int producer(int argc, char* argv[])
{
    char queue_name;
    Message_t msg;
    int queue_id;
    int full_id, empty_id, mutex_id;
	int tmp;

    sprintf(msg.producer, "_Producer_%s_", argv[1] );  
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
	queue_id = shmget( QUEUE_KEY(queue_name), sizeof(Queue_t), 0666);
	Queue_t *queue = (Queue_t*)shmat(queue_id, NULL, 0);

	full_id  = semget(SEM_FULL_KEY(queue_name) , 1, 0600);
	empty_id = semget(SEM_EMPTY_KEY(queue_name), 1, 0600);
	mutex_id = semget(SEM_MUTEX_KEY(queue_name), 1, 0600);	

    msg.priority = 0;
    msg.valid = 1;

    rand_init();
		
	while(1)
	{	
		/* generate random message */
		for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
			msg.data[tmp] = rand_value('A', 'C');        
		
		/* send message */
		sem_down(empty_id, 0);
		sem_down(mutex_id, 0);

		send_msg(queue, &msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send msg: \"%3s\"; %d/%d\n", msg.producer, msg.data, queue->count, QUEUE_SIZE);)

		sem_up(mutex_id, 0);
		sem_up(full_id, 0);	
		
		/* wait */
        sleep(PRODUCER_SLEEP_TIME);			
	}	




    SUBPROCESSES_PRINT_CMD(printf("%s end\n", msg.producer);)
    return 0;
}