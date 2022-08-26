#ifndef CAPTURE_H
#define CAPTURE_H

#include "queue.h"
#include <stdbool.h>
#include "libary_handler.h"
#include "queue.h"
#include "stdbool.h"
#include "func_tool.h"
#define MACROSECONDSPERSECOND 1000000
#define FRAMESPERSECOND 250
#define WAITPERSECONDS MACROSECONDSPERSECOND/FRAMESPERSECOND
static int count = 0;
typedef struct capture_t{
    int * status;
    int record_active_bit;
    int stop_active_bit;
    int snapshot_active_bit;
    bool * snapshot_handler_bit;
    int bit;
    pool_node * pn;
}capture_t;
capture_t * init_capture_t(int * st,int record_bit,int stop_active_bit,int snapshot_bit,bool * snap_hand_bit,pool_node *);
Node  *capture(void * my_arg,Node * node);
#endif // CAPTURE_H
