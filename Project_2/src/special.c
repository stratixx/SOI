#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "../inc/special.h"
#include "../inc/tools.h"

int special(int argc, char* argv[])
{    
    char queue_name;
    Queue_t *queue[QUEUE_NUMBER];
    Message_t msg;
    int queue_id[QUEUE_NUMBER];
    float pr;
    int full_id[QUEUE_NUMBER], empty_id[QUEUE_NUMBER], mutex_id[QUEUE_NUMBER];
    int tmp, readed;

    sprintf(msg.producer, "_Special_%s_", argv[1] );  
    queue_name = *argv[1];  
    SUBPROCESSES_PRINT_CMD(printf("%s start\n", msg.producer);)
    
    for(tmp=0; tmp<QUEUE_NUMBER; tmp++)
    {
        queue_id[tmp] = shmget(QUEUE_KEY(tmp+'A'), sizeof(Queue_t), 0666);
        queue[tmp] = (Queue_t*)shmat(queue_id[tmp], NULL, 0);
        queue_init(queue[tmp]);

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

		send_msg(queue[tmp], &msg);
		SUBPROCESSES_PRINT_CMD(printf("%s send to queue \"%c\" msg: \"%3s\"; %d/%d\n", msg.producer, tmp+'A', msg.data, queue[tmp]->count, QUEUE_SIZE);)

		sem_up(mutex_id[tmp], 0);
		sem_up(full_id[tmp], 0);	

        /* wait */
        sleep(SPECIAL_SLEEP_TIME);
	}	

    printf("%s end\n", msg.producer);
    return 0;
}