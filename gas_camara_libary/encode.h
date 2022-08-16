#ifndef ENCODE_H
#define ENCODE_H
#include "assert.h"
#include "libary_handler.h"
#include "queue.h"
#include "yuv_converter.h"
#include "func_tool.h"
#include <libavcodec/avcodec.h>

typedef struct
{
    AVCodecContext *enc_ctx;
    AVFrame *frame;
    AVPacket *pkt;
    uint64_t start_time;
    FILE *outline;

}encoder_t;

encoder_t * init_encoder(int w,int h,int gop);
int ff_encoder(encoder_t *p_encoder,FILE * outline);
Node  * encode_record(void * my_arg,Node * node);

#endif // ENCODE_H
