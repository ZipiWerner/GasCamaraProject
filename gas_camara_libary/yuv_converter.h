#ifndef YUV_CONVERTER_H
#define YUV_CONVERTER_H

#include "libary_handler.h"
#include "queue.h"
#include <libavcodec/avcodec.h>
//typedef struct yuv{
//    char y[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH];
//    char u[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
//    char v[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
//}YUV;
typedef struct yuv_converter_t{
    int * status;

}yuv_converter_t;
Node * yuv_converter(void *,Node * node);
yuv_converter_t *init_yuv_converter_t(int *);
#endif // YUV_CONVERTER_H
