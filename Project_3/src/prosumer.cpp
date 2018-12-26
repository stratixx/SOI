#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../inc/prosumer.h"
#include "../inc/tools.h"
#include "../inc/queue.h"


extern Queue queue[QUEUE_NUMBER];


int prosumer(int argc, char* argv[])
{    
    char queue_name;
    Queue * my_queue;
    Message_t msg, rec_msg;
    float pr;
    int tmp, readed;
    int instant_read = 0;

    sprintf(msg.producer, "_Prosumer_%s_", argv[1] );  
    sscanf(argv[2], "%f", &pr);    
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start with pr=%1.3f\n", msg.producer, pr);)
    

	my_queue = &queue[queue_name-'A'];


    msg.priority = 0;
    msg.valid = 1;

    rand_init();
		
	while(1)
	{	        
		/* receive message */
        my_queue->read_msg(&rec_msg);
		SUBPROCESSES_PRINT_CMD(printf("%s received msg from %s: \"%3s\"; %d/%d\n", msg.producer, rec_msg.producer, rec_msg.data, my_queue->count, QUEUE_SIZE);)
		
        /* wait */
        if( instant_read==0 )
            usleep(PROSUMER_SLEEP_TIME);
        else
            instant_read--;

        /* if received message from protector then read 5 messages without waiting */
        if( rec_msg.priority==2 )
        {
            instant_read = 5;
            continue;
        }
        /* remove empty message */
        if( rec_msg.data[0]==0 )
            continue;

        /* prepare message to send */
        readed      = rec_msg.data[0] - 'A';
        msg.data[0] = rec_msg.data[1];
        msg.data[1] = rec_msg.data[2];
        msg.data[2] = 0;
        if( rand_bool(pr)==1 )
        {
            tmp = rand_value('A', 'C');
		    SUBPROCESSES_PRINT_CMD(printf("%s will send random message to \"%c\"\n", msg.producer, tmp);)
            if(msg.data[0]==0)
                msg.data[0] = tmp;
            else if(msg.data[1]==0)
                msg.data[1] = tmp;
            else 
                msg.data[2] = tmp;
        }

        /* send message to selected queue */
		queue[readed].send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, readed+'A', msg.data, queue[readed].count, QUEUE_SIZE);)

	}	




    printf("%s end\n", msg.producer);
    return 0;
}
