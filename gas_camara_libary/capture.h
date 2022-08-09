#ifndef CAPTURE_H
#define CAPTURE_H

#include "queue.h"
#include <stdbool.h>

typedef struct capture_t{
    int * status;
    int record_active_bit;
    int stop_active_bit;
    int snapshot_active_bit;
    bool * snapshot_handler_bit;
}capture_t;
capture_t * init_capture_t(int * st,int record_bit,int stop_active_bit,int snapshot_bit,bool * snap_hand_bit);
Node  *capture(void * my_arg,Node * node);
#endif // CAPTURE_H
