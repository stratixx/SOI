#ifndef QUEUE_H
#define QUEUE_H

/*
*
*
*
*/

#include "tools.h"
#include "monitor.h"

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
class Queue : public Monitor
{
  public:
	Message_t table[QUEUE_SIZE];    /* tablica wiadomości */
	int head;                       /* indeks pierwszego elementu listy */
	int tail;                       /* indeks ostatniego elementu listy */        
	int count;                      /* ilość elementów w liście */
    int valid;                      /* czy lista jest ważna? */

    char queue_name;

    static char last_queue;


    /*
    *
    */
    Queue(char queue_name);

    /*
    *
    */
    void copy_msg(Message_t *dest, const Message_t *src);

    /*
    *
    */
    int send_msg(Message_t *msg);

    /*
    *
    */
    Message_t* read_msg(Message_t *msg);
};
/* ------------------------------------------------------------------------*/


#endif