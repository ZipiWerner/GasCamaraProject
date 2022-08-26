#ifndef LIBARY_HANDLER_H
#define LIBARY_HANDLER_H


#define SNAPSHOT_HEIGHT 240
#define SNAPSHOT_WIDTH 360
#define MAX_TEMP 30
#include <stdlib.h>
#include "stdio.h"
typedef struct snapshot_t{
    char* file_name;  //full path ?
    int width;
    int height;
    int type;  //GPEG,PNG,ppm
}snapshot_t;
#endif // LIBARY_HANDLER_H
