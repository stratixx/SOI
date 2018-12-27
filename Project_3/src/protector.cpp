#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../inc/protector.h"
#include "../inc/tools.h"
#include "../inc/queue.h"




int protector(int argc, char* argv[])
{    
    Queue * queue[QUEUE_NUMBER];
    int tmp, count, queue_id[QUEUE_NUMBER];
    // dostaje jako argument częstotliwosć akcji
    Message_t msg;
    int readed;
    Queue * my_queue;

    sprintf(msg.producer, "_Protector_" );  
    
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        queue_id[tmp] = shmget(QUEUE_KEY(tmp+'A'), sizeof(Queue), 0666);
        queue[tmp] = (Queue*)shmat(queue_id[tmp], NULL, 0);
    }

    msg.priority = 2;
    msg.valid = 1;

    rand_init();

	while(1)
	{
        msg.data[0] = 0;
        msg.data[1] = 0;
        msg.data[2] = 0;
        
        tmp = 0;
        my_queue = queue[0];
        /* select queue */
        for( int n=0; n<QUEUE_NUMBER; n++ )   
            if(queue[n]->count > my_queue->count)
                my_queue = queue[n];        

        /* send message to selected queue */
		my_queue->send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, tmp+'A', msg.data, my_queue->count, QUEUE_SIZE);)

        /* wait */
        usleep(PROTECTOR_SLEEP_TIME);
	}	

    printf("%s end\n", msg.producer);
    return 0;
}