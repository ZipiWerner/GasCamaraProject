#ifndef YUV_CONVERTER_H
#define YUV_CONVERTER_H

#include "libary_handler.h"
#include "queue.h"
#include <libavcodec/avcodec.h>
typedef struct yuv{
    char y[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH];
    char u[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
    char v[SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH/4];
}YUV;
#define YFORMULA(R,G,B) (0.257 * R) + (0.504 * G) + (0.098 * B) + 16 + '0'
#define UFORMULA(R,G,B) (0.439 * R) - (0.368 * G) - (0.071 * B) + 128 + '0'
#define VFORMULA(R,G,B) -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128 + '0'
#include "assert.h"
typedef struct yuv_converter_t{
    int * status;

}yuv_converter_t;
void free_yuv(YUV *);
Node * yuv_converter(void *,Node * node);
yuv_converter_t *init_yuv_converter_t(int *);
#endif // YUV_CONVERTER_H
