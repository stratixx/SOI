#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


#include "../inc/producer.h"
#include "../inc/tools.h"
#include "../inc/queue.h"

extern Queue queue[QUEUE_NUMBER];

int producer(int argc, char* argv[])
{
    char queue_name;
    Message_t msg;
	int tmp;

    sprintf(msg.producer, "_Producer_%s_", argv[1] );  
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
	Queue *my_queue = &queue[queue_name-'A'];

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