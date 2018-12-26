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
    int tmp, readed;
    Queue * my_queue;

    sprintf(msg.producer, "_Protector_" );  
    
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
    msg.priority = 2;
    msg.valid = 1;

    rand_init();

	while(1)
	{
        msg.data[0] = 0;
        msg.data[1] = 0;
        msg.data[2] = 0;
        
        tmp = 0;
        my_queue = &queue[0];
        /* select queue */
        for( int n=0; n<QUEUE_NUMBER; n++ )   
            if(queue[n].count > my_queue->count)
                my_queue = &queue[n];        

        /* send message to selected queue */
		my_queue->send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, tmp+'A', msg.data, my_queue->count, QUEUE_SIZE);)

        /* wait */
        usleep(PROTECTOR_SLEEP_TIME);
	}	

    printf("%s end\n", msg.producer);
    return 0;
}