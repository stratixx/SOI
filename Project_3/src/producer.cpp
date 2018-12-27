#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


#include "../inc/producer.h"
#include "../inc/tools.h"
#include "../inc/queue.h"


int producer(int argc, char* argv[])
{
    Queue * queue[QUEUE_NUMBER];
    int tmp, count, queue_id[QUEUE_NUMBER];
    char queue_name;
    Message_t msg;

    sprintf(msg.producer, "_Producer_%s_", argv[1] );  
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        queue_id[tmp] = shmget(QUEUE_KEY(tmp+'A'), sizeof(Queue), 0666);
        queue[tmp] = (Queue*)shmat(queue_id[tmp], NULL, 0);
    }

	Queue *my_queue = queue[queue_name-'A'];

    msg.priority = 0;
    msg.valid = 1;

    rand_init();
		
	while(1)
	{	
		/* generate random message */
		for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
			msg.data[tmp] = rand_value('A', 'C');        
		
		/* send message */
		my_queue->send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send msg: \"%3s\"; %d/%d\n", msg.producer, msg.data, my_queue->count, QUEUE_SIZE);)
		
		/* wait */
        sleep(PRODUCER_SLEEP_TIME);			
	}	




    SUBPROCESSES_PRINT_CMD(printf("%s end\n", msg.producer);)
    return 0;
}