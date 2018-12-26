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
    int my_full_id, my_empty_id, my_mutex_id;
    int full_id[QUEUE_NUMBER], empty_id[QUEUE_NUMBER], mutex_id[QUEUE_NUMBER];
    int tmp, readed;

    sprintf(msg.producer, "_Prosumer_%s_", argv[1] );  
    sscanf(argv[2], "%f", &pr);    
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start with pr=%1.3f\n", msg.producer, pr);)
    
    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        full_id[tmp] =  semget(SEM_FULL_KEY(tmp+'A') , 1, 0600);	     
        empty_id[tmp] = semget(SEM_EMPTY_KEY(tmp+'A'), 1, 0600);     
        mutex_id[tmp] = semget(SEM_MUTEX_KEY(tmp+'A'), 1, 0600);
    }

	my_queue = &queue[queue_name-'A'];

	my_full_id  = full_id[queue_name-'A'];
	my_empty_id = empty_id[queue_name-'A'];
	my_mutex_id = mutex_id[queue_name-'A'];	

    msg.priority = 0;
    msg.valid = 1;

    rand_init();
		
	while(1)
	{	        
		/* receive message */
		sem_down(my_full_id, 0);
		sem_down(my_mutex_id, 0);

        my_queue->read_msg(&rec_msg);
		SUBPROCESSES_PRINT_CMD(printf("%s received msg from %s: \"%3s\"; %d/%d\n", msg.producer, rec_msg.producer, rec_msg.data, my_queue->count, QUEUE_SIZE);)

		sem_up(my_mutex_id, 0);
		sem_up(my_empty_id, 0);	
		
        /* wait */
        usleep(PROSUMER_SLEEP_TIME);

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
		sem_down(empty_id[readed], 0);
		sem_down(mutex_id[readed], 0);

		queue[readed].send_msg(&msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, readed+'A', msg.data, queue[readed].count, QUEUE_SIZE);)

		sem_up(mutex_id[readed], 0);
		sem_up(full_id[readed], 0);	
	}	




    printf("%s end\n", msg.producer);
    return 0;
}
