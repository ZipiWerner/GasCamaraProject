//#include <libavcodec/avcodec.h>
//static void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
//                   FILE *outfile)
//{
//    int ret;

//    /* send the frame to the encoder */
//    //if (frame)
//      //  printf("Send frame %3PRId64 count= %d\n", frame->pts,count);

//    ret = avcodec_send_frame(enc_ctx, frame);

//    if (ret < 0) {
//        fprintf(stderr, "Error sending a frame for encoding\n");
//        exit(1);
//   }
//    while (ret >= 0) {
//        ret = avcodec_receive_packet(enc_ctx, pkt);
//        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
//            return;
//        else if (ret < 0) {
//            fprintf(stderr, "Error during encoding\n");
//            exit(1);
//        }

//      //  if(pkt->flags==1&& first==1){
//            //yuv420p_save(frame,frame->width,frame->height,pkt->flags);
//         // AVPicture *picture;;
//          //  avpicture_fill((AVPicture *)&picture, pkt->data, enc_ctx->pix_fmt, enc_ctx->width, enc_ctx->height);

//        //}
//             printf("Write packet %d (size=%5d) flag=%d \n", pkt->pts, pkt->size,pkt->flags);

//        fwrite(pkt->data, 1, pkt->size, outfile);
//        //send_msg(pkt);
//        av_packet_unref(pkt);
//    }
//}

//void try_func(){

//    const char *filename={"f.ts"}, *codec_name;
//    const AVCodec *codec;
//    AVCodecContext *c= NULL;
//    int i, ret, x, y;
//    FILE *f;
//    AVFrame *frame;  //rgb-> yuv raw
//    AVPacket *pkt;   //
//    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
//    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
//    if (!codec) {
//        fprintf(stderr, "Codec '%s' not found\n", codec_name);
//        exit(1);
//    }

//    c = avcodec_alloc_context3(codec);
//    if (!c) {
//        fprintf(stderr, "Could not allocate video codec context\n");
//        exit(1);
//    ////
//    }

//    pkt = av_packet_alloc();
//    if (!pkt)
//        exit(1);

//    /* put sample parameters */
//    c->bit_rate = 400000;
//    /* resolution must be a multiple of two */
//    c->width = 620;
//    c->height = 480;
//    /* frames per second */
//    c->time_base = (AVRational){1, 25};
//    c->framerate = (AVRational){25, 1};
//    c->gop_size = 5;
//    c->max_b_frames = 1;
//   // c->pix_fmt = AV_PIX_FMT_YUV420P;
//   c->pix_fmt=AV_PIX_FMT_YUV420P;
//   ret = avcodec_open2(c, codec, NULL);
//   if (ret < 0) {
//       //fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
//       exit(1);
//   }

//   f = fopen(filename, "wb");
//   if (!f) {
//       fprintf(stderr, "Could not open %s\n", filename);
//       exit(1);
//   }


//   frame = av_frame_alloc();
//   if (!frame) {
//       fprintf(stderr, "Could not allocate video frame\n");
//       exit(1);
//   }
//   frame->format = c->pix_fmt;
//   frame->width  = c->width;
//   frame->height = c->height;

//   rgb_t mat[620*480];
//   char *dst_mat;

// //  count++;
//  // fprintf(stderr, "count =%d i=%d\n",count,j);

//   //sleep(1);
//   ret = av_frame_get_buffer(frame, 0);
//   if (ret < 0) {
//       fprintf(stderr, "Could not allocate the video frame data\n");
//       exit(1);
//   }
//   for (i = 0; i < 1000; i++) {
//       msleep(10);
//       fflush(stdout);

//       /* Make sure the frame data is writable.
//          On the first round, the frame is fresh from av_frame_get_buffer()
//          and therefore we know it is writable.
//          But on the next rounds, encode() will have called
//          avcodec_send_frame(), and the codec may have kept a reference to
//          the frame in its internal structures, that makes the frame
//          unwritable.
//          av_frame_make_writable() checks that and allocates a new buffer
//          for the frame only if necessary.
//        */
//       ret = av_frame_make_writable(frame);
//       if (ret < 0)
//           exit(1);

//       /* Prepare a dummy image.
//          In real code, this is where you would have your own logic for
//          filling the frame. FFmpeg does not care what you put in the
//          frame.
//        */
//       /* Y */

//       int w=620;
//       int h=480;

//      create_rgb(mat,w,h);
//      if (first==1){
//      saveFrame_jpg((uint8_t*) mat, 5,w,h);
//      first =0;
//      }

//        #if 0
//     ppm_image ppm ;
//     ppm.width=w;
//     ppm.height=h;
//     ppm.data= (char*)mat;
//     ppm.size=w*h*3;
//     FILE *x=fopen("t.bmp","wb+");

//     ppm_save(&ppm,x);
//     fclose(x);
//#endif
//       //char *pixel=&mat[0];
//       //printf ("pixel %p [%d][%d][%d] \n\r",pixel,pixel[0],pixel[1],pixel[2]);
//       //printf ("mat   %p [%d][%d][%d] \n\r",mat,mat[0],mat[1],mat[2]);
//      // sleep(100);
//      //int l1=sizeof(frame->buf);
//      //int l2=sizeof(frame->data);
//    //  printf("%d %d\n\r",c->height,c->width);

//     //  convert_rgb2yuv(mat,(char*)&frame->data[0][frame->linesize[0]],w,h);
//         // int ind_w=0;
//       // printf ("[%d][%d][%d] \n\r",mat[3],mat[4],mat[5]);
//int ind_mat=0;

//       for(int i=0;i<c->height;i++)
//         for(int j=0;j<c->width;j++){

//             rgb_t pixel=mat[i*c->width+j];
//          //   printf ("pixel [%d][%d][%d] \n\r",pixel[0],pixel[1],pixel[2]);
//             //printf ("mat  %d [%d][%d][%d] \n\r",ind_mat,mat[ind_mat],mat[ind_mat+1],mat[ind_mat+2]);
//             //ind_mat
//           //  printf ("[%x][%x][%x] \n\r",pixel[0],pixel[1],pixel[2]);
//             unsigned char R=pixel.r;
//             unsigned   char G=pixel.g;
//             unsigned char B=pixel.b;
//             //R=0;
//            // G=0;
//             //B=255;
//             //sleep(1);
//         //    printf ("[%d][%d][%d] \n\r",R,G,B);

//             //int R=pixel[0];
//             //int G=pixel [1];
//             //int B=pixel [2];

//             unsigned int Y= (0.257 * R) + (0.504 * G) + (0.098 * B) + 16;
//             unsigned int Cr  =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128;
//             unsigned int Cb  = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128;


//             //    frame->data[0][i* frame->linesize[0]+j]=Y;
//                 frame->data[0][frame->linesize[0]]=Y;
//                 frame->data [1][frame->linesize[1]]=U;
//                 frame->data [2][frame->linesize[2]]= V;

//                //int Cb = ((-38*R + -74*G + 112*B) >> 8) + 128;
//                //int Cr = ((112*R + -94*G + -18*B) >> 8) + 128;
//               // printf("i=%d j=5b %d cr %d b=%d,r=%d,y=%d\n\r",Cb,Cr,B,R,Y);

//              //  frame->data [1][(i/2)*frame->linesize[1]+j/2]= 128 + i + count * 2;
//                frame->data [1][(i/2)*frame->linesize[1]+j/2]=Cb;
//                frame->data [2][(i/2)*frame->linesize[2]+j/2]= Cr;

//              //  frame->data [2][(i/2)*frame->linesize[2]+j/2]= 64 + j + count * 5;


//              #if 0
//                for (y = 0; y < c->height; y++) {
//                    for (x = 0; x < c->width; x++) {
//                        frame->data[0][y * frame->linesize[0] + x] = x+y + i * 3;
//                    }
//                }

//                /* Cb and Cr */
//                for (y = 0; y < c->height/2; y++) {
//                    for (x = 0; x < c->width/2; x++) {
//                        frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
//                        frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
//                    }
//                }
//             #endif


//}


///*
//       for (y = 0; y < c->height/2; y++) {
//                 for (x = 0; x < c->width/2; x++) {
//                     frame->data[1][y * frame->linesize[1] + x] = 0xff;
//                     frame->data[2][y * frame->linesize[2] + x] = 0xff;
//                 }
//       }
//*/
///*
//         for(int i=0;i<c->width/2;i++)
//             for(int j=0;j<c->height/2;j++){


//                int Y= ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16;


//                int Cb = ((-38*R + -74*G + 112*B) >> 8) + 128;
//                int Cr = ((112*R + -94*G + -18*B) >> 8) + 128;
//               // printf("i=%d j=5b %d cr %d b=%d,r=%d,y=%d\n\r",Cb,Cr,B,R,Y);

//                frame->data [1][i*frame->linesize[1]+j]= Cb;
//                frame->data [2][i*frame->linesize[2]+j]= Cr;
//        }*/

//       /*       for (y = 0; y < c->height/2; y++) {
//           for (x = 0; x < c->width/2; x++) {
//               frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
//               frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
//           }
//       }
//*/


//      // c->

//       if (start_time==0){
//           frame->pts=0;
//       start_time=GetMHClock();
//       }
//       else
//       frame->pts = GetMHClock()-start_time;
//      // frame->
//       //frame->pts=count*36000L;
//       /* encode the image */
//     //  frame->i
//      // sleep(100);

//       encode(c, frame, pkt, f);
//       count ++;

//       // printf("i=%d flags=%d size=%d\n",i,pkt.,pkt->size);
//   }

//   /* flush the encoder */
//   //encode(c, NULL, pkt, f);

//   /* Add sequence end code to have a real MPEG file.
//      It makes only sense because this tiny examples writes packets
//      directly. This is called "elementary stream" and only works for some
//      codecs. To create a valid file, you usually need to write packets
//      into a proper file format or protocol; see muxing.c.
//    */
//       fwrite(endcode, 1, sizeof(endcode), f);


//   fclose(f);

//   avcodec_free_context(&c);
//   av_frame_free(&frame);
//   av_packet_free(&pkt);

////   return 0;
//}
