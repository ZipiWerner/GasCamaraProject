#ifndef GAS_CAMARA_LIBARY_H
#define GAS_CAMARA_LIBARY_H
#define STAGES_NUMBER 5
#define CAPACITY 20
#include "libary_handler.h"
#include "rgb_converter.h"
#include "capture.h"
#include "queue.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "libary_handler.h"
#include "yuv_converter.h"
#include "write.h"
#include "encode.h"
#include <stage.h>
#include "func_tool.h"
#ifdef __cplusplus

extern "C" {
#endif

typedef enum status{
  NO_STATUS=0,
  INIT=1,
  CAPTURE_ACTIVE=2,
  RECORD_ACTIVE=4,
  STOP_ACTIVE=8,
  SNAPSHOT_ACTIVE=16
}status;
typedef struct streaming_t{
    int ip;
    int port;
}streaming_t;

typedef struct gpio_t{
    int num;
    int dir;  //in ,out
    int value;  //1 ,0
    int is_blink;
    int operation;  //record,straming
}gpio_t;

typedef struct record_t{
    char* file_name;
    int codec;
    int width;
    int height;
    int fps;
}record_t;
typedef struct ppm_image{
    int width;
    int height;
    char *data;
    size_t size;
    char * name;
} ppm_image;

typedef struct handler{
    char static_mat_rgb[MAX_TEMP*3];
    stage * stages;
    FILE *  fp;
    status status;
    bool snapshot_bit;
    pool_node *my_pool_node;
    snapshot_t * my_snapshot;
}handler;
typedef struct {

    void* (*init)();
    void (*free_all)(void* handle);
    status (*get_status)(handler * handle);
    int (*signal_handler_interrupt)(handler * handler);
    int (*start_record)(void* handler,record_t * );
    int (*stop_record)(void* handler);
    int (*start_streaming)(streaming_t*,char * file_name);
    int (*stop_streamig)(streaming_t*);
    int (*do_snapshot)(void*);
    char* (*get_dll_version)();
    char* (*get_video_statics)(record_t*);

}gazapi_t;

#ifdef __cplusplus
}
#endif
#endif // GAS_CAMARA_LIBARY_H


