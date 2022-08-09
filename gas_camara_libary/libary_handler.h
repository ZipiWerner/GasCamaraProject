#ifndef LIBARY_HANDLER_H
#define LIBARY_HANDLER_H

#include <time.h>
#include <errno.h>
#define SNAPSHOT_HEIGHT 240
#define SNAPSHOT_WIDTH 360
#define MAX_TEMP 30
#include <stdlib.h>
#include "stdio.h"

typedef struct yuv{
    char y[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH];
    char u[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
    char v[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
}YUV;
int msleep(long msec);
#endif // LIBARY_HANDLER_H
