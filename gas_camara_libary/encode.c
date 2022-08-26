#include "encode.h"

encoder_t * init_encoder(int w,int h,int gop){
    const AVCodec *codec;
    int ret=0;
    encoder_t *p_encoder =(encoder_t*) calloc (1,sizeof (encoder_t)) ;
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
    assert(codec);
    p_encoder->frame=av_frame_alloc();
    assert(p_encoder->frame);

    p_encoder->frame->width=w;
    p_encoder->frame->height=h;
    p_encoder->frame->format=AV_PIX_FMT_YUV420P;
    ret = av_frame_get_buffer(p_encoder->frame, 0);
    assert(ret>=0);

    p_encoder->enc_ctx=avcodec_alloc_context3(codec);
    assert(p_encoder->enc_ctx) ;

    p_encoder->pkt=av_packet_alloc();
    assert(p_encoder->pkt);
    p_encoder->enc_ctx->bit_rate=400000;
    p_encoder->enc_ctx->width=w;
    p_encoder->enc_ctx->height=h;

    p_encoder->enc_ctx->time_base = (AVRational){1, 25};
    p_encoder->enc_ctx->framerate = (AVRational){25, 1};
    p_encoder->enc_ctx->gop_size = gop;
    p_encoder->enc_ctx->max_b_frames = 1;
    p_encoder->enc_ctx->pix_fmt=AV_PIX_FMT_YUV420P;

    ret=avcodec_open2(p_encoder->enc_ctx, codec, NULL);
    assert(ret>=0);

    p_encoder->start_time=0;
    p_encoder->outline=NULL;
    return (p_encoder);

}

int ff_encoder(encoder_t *p_encoder,FILE * outfile){

    int ret=0;
    ret = avcodec_send_frame(p_encoder->enc_ctx, p_encoder->frame);
    assert(ret >= 0);
    while (ret >= 0) {
        ret = avcodec_receive_packet(p_encoder->enc_ctx, p_encoder->pkt);

        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return 0;
        assert(ret >= 0) ;
        fwrite(p_encoder->pkt->data, 1, p_encoder->pkt->size, outfile);
        av_packet_unref(p_encoder->pkt);


    }

}

Node  * encode_record(void * my_arg,Node * node){
    printf("encode!!!!!\n");
    encoder_t * p_encoder=(encoder_t*)(my_arg);
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    if(node->data)
    {
        int ret=0;
        AVFrame *frame=NULL;

        fflush(stdout);
        frame=p_encoder->frame;
        int count =0;
        if(p_encoder->start_time==0)
        {
       // time_t t=time(NULL);
//            struct tm tm=*localtime(&t);
//            int n=25;//sprintf(NULL,"%d-%02d-%02d %02d:%02d:%02d\0", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
//            char* name=(char*)malloc(n+5);
//            sprintf(name,"%d-%02d-%02d %02d:%02d:%02d.", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
//            char  name1[100]="/home/zipi/sambashare/";
//            strcat(name1,name);
//            strcat(name1,".ts");
            p_encoder->outline=fopen("/home/zipi/sambashare/t4.ts","wb");
            assert(p_encoder->outline);
        }

        YUV *my_yuv=(YUV*)node->data;
        ret = av_frame_make_writable(frame);
        for (int i=0;i<frame->height;i++)
            for (int j=0;j<frame->width;j++)
                frame->data[0][i*frame->linesize[0]+j]=my_yuv->y[i*frame->width+j/2];
        for(int i=0;i<p_encoder->enc_ctx->height/2;i++)
            for(int j=0;j<p_encoder->enc_ctx->width/2;j++){
                frame->data [1][i*frame->linesize[1]+j]= my_yuv->u[(i/2)*frame->width+j/2];
                frame->data [2][i*frame->linesize[2]+j]= my_yuv->u[(i/2)*frame->width+j/2];
            }
        if (p_encoder->start_time==0){
            frame->pts=0;
            p_encoder->start_time=GetMHClock();
        }
        else
            frame->pts = GetMHClock()-p_encoder->start_time;

        ff_encoder(p_encoder,p_encoder->outline);
        free_yuv(my_yuv);
        //data 1 means the node not used
        //data null means finish pipline
        node->data=1;
    }
    else
    {  fwrite(endcode, 1, sizeof(endcode), p_encoder->outline);
        fclose(p_encoder->outline);
    }

    return node;
}
