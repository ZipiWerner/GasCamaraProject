#ifndef RGB_CONVERTER_H
#define RGB_CONVERTER_H

#include <stdlib.h>
#include <stdio.h>
#include "libary_handler.h"
#include "queue.h"
#include "save_snapshot.h"

typedef struct rgb_converter_t{
 int * status;
 char * static_rgb_matrix;
 int record_active_bit;
 int snapshot_active_bit;
}rgb_converter_t;
Node  * rgb_converter(void * my_arg,Node * node);
rgb_converter_t * init_rgb_converter_t(int * st,char * rgb_matrix,int  snapshot_bit,int  record_bit);

#endif // RGB_CONVERTER_H
