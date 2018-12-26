#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../inc/special.h"
#include "../inc/tools.h"
#include "../inc/queue.h"

    
extern Queue queue[QUEUE_NUMBER];


int special(int argc, char* argv[])
{    
    Message_t msg;
    int tmp, readed;
	struct sembuf buf;

    sprintf(msg.producer, "_Special_" );  
    
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
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
		queue[tmp].send_msg(&msg, &buf);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, tmp+'A', msg.data, queue[tmp].count, QUEUE_SIZE);)

        /* wait */
        sleep(SPECIAL_SLEEP_TIME);
	}	

    printf("%s end\n", msg.producer);
    return 0;
}