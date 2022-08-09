#ifndef ENCODE_H
#define ENCODE_H

#include "libary_handler.h"
#include "queue.h"
#include <libavcodec/avcodec.h>
typedef struct encode_t{

}encode_t;
typedef struct{
    AVFrame *frame;
    AVPacket *pkt;
    AVCodecContext *c;

}encoder_t;
Node  * encode_record(void * my_arg,Node * node);

#endif // ENCODE_H
