#ifndef TOOLS_H
#define TOOLS_H

/*
*
*
*
*/


/* ------------------------------------------------------------ */


#define DATA_SIZE               3

#define QUEUE_NUMBER            3
#define QUEUE_SIZE              9
#define QUEUE_NO_MSG            QUEUE_SIZE
#define QUEUE_KEY(queue)        (8000+queue-'A')

#define MESSAGE_PRODUCER_LENGTH 15

#define SEM_FULL_KEY(queue)     (8010+queue-'A')
#define SEM_EMPTY_KEY(queue)    (8020+queue-'A')
#define SEM_MUTEX_KEY(queue)    (8030+queue-'A')


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
int get_queue_size(Queue_t *q);

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


#endif