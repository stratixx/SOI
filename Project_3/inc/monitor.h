#ifndef MONITOR_H
#define MONITOR_H

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
class Monitor
{
  public:
    int full_id;
	int empty_id;
	int mutex_id;

    /*
    *
    */
    Monitor(char key);

    void enter();
    void leave();
    void wait_full();
    void signal_full();
    void wait_empty();
    void signal_empty();
};
/* ------------------------------------------------------------------------*/


#endif