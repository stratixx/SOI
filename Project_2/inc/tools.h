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

#define QUEUE_NUMBER            3
#define QUEUE_SIZE              9
#define QUEUE_NO_MSG            QUEUE_SIZE
#define KEY_OFFSET              8100+31+31+31+31
#define QUEUE_KEY(queue)        (KEY_OFFSET+queue-'A')

#define MESSAGE_PRODUCER_LENGTH 15

#define SEM_FULL_KEY(queue)     (KEY_OFFSET+10+queue-'A')
#define SEM_EMPTY_KEY(queue)    (KEY_OFFSET+20+queue-'A')
#define SEM_MUTEX_KEY(queue)    (KEY_OFFSET+30+queue-'A')

#define SUBPROCESSES_PRINT_ENABLE
//#define MAIN_PRINT_ENABLE

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
typedef struct 
{
    int priority;                           /* priorytet */
    char producer[MESSAGE_PRODUCER_LENGTH]; /* nazwa nadawcy */
    char data[DATA_SIZE];                   /* dane */
    int next;                               /* następna wiadomość w liście po indeksie */
    int valid;                              /* czy wiadomość jest ważna? */
}Message_t;


/*
*
*/
typedef struct 
{
	Message_t table[QUEUE_SIZE];    /* tablica wiadomości */
	int head;                       /* indeks pierwszego elementu listy */
	int tail;                       /* indeks ostatniego elementu listy */        
	int count;                      /* ilość elementów w liście */
    int valid;                      /* czy lista jest ważna? */
}Queue_t;
/* ------------------------------------------------------------------------*/


/*
*
*/
void queue_init(Queue_t *q);

/*
*
*/
void copy_msg(Message_t *dest, const Message_t *src);

/*
*
*/
int send_msg(Queue_t *q, Message_t *msg);

/*
*
*/
Message_t* read_msg(Queue_t *q, Message_t *msg);

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