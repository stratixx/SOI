#ifndef QUEUE_H
#define QUEUE_H

/*
*
*
*
*/

#include "tools.h"

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
class Queue
{
  public:
	Message_t table[QUEUE_SIZE];    /* tablica wiadomości */
	int head;                       /* indeks pierwszego elementu listy */
	int tail;                       /* indeks ostatniego elementu listy */        
	int count;                      /* ilość elementów w liście */
    int valid;                      /* czy lista jest ważna? */
    int full_id;
	int empty_id;
	int mutex_id;

    char queue_name;

    static char last_queue;


    /*
    *
    */
    Queue();

    /*
    *
    */
    void copy_msg(Message_t *dest, const Message_t *src);

    /*
    *
    */
    int send_msg(Message_t *msg, struct sembuf * buf);

    /*
    *
    */
    Message_t* read_msg(Message_t *msg, struct sembuf * buf);
};
/* ------------------------------------------------------------------------*/


#endif