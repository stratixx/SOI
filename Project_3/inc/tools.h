#ifndef TOOLS_H
#define TOOLS_H

/*
*
*
*
*/


/* ------------------------------------------------------------ */


#define DATA_SIZE               3

#define PRODUCER_SLEEP_TIME     3
#define SPECIAL_SLEEP_TIME      3
#define PROSUMER_SLEEP_TIME     (500*1000)
#define PROTECTOR_SLEEP_TIME    (1000*1000)

#define QUEUE_NUMBER            3
#define QUEUE_SIZE              20
#define QUEUE_NO_MSG            QUEUE_SIZE
#define KEY_OFFSET              8200

#define MESSAGE_PRODUCER_LENGTH 15

#define QUEUE_KEY(queue)        (KEY_OFFSET+queue-'A')

#define SEM_FULL_KEY(queue)     (KEY_OFFSET+10+queue-'A')
#define SEM_EMPTY_KEY(queue)    (KEY_OFFSET+20+queue-'A')
#define SEM_MUTEX_KEY(queue)    (KEY_OFFSET+30+queue-'A')


//#define SUBPROCESSES_PRINT_ENABLE
#define MAIN_PRINT_ENABLE

#ifdef SUBPROCESSES_PRINT_ENABLE
    #define SUBPROCESSES_PRINT_CMD(arg) arg
#else
    #define SUBPROCESSES_PRINT_CMD(arg) 
#endif

#ifdef MAIN_PRINT_ENABLE
    #define MAIN_PRINT_CMD(arg) arg
#else
    #define MAIN_PRINT_CMD(arg)
#endif

/* ----------------------------------------------------------- */

/*
*
*/
void sem_down(int semid, int semnum);

/*
*
*/
void sem_up(int semid, int semnum);

/*
*
*/
void rand_init();

/*
*
*/
int rand_value(int min, int max);

/*
*
*/
int rand_bool(float pr);

#endif