#ifndef GAS_CAM_H
#define GAS_CAM_H
#define STAGES_NUMBER 5
#define CAPACITY 10
#include "Queue.h"
#include "gas_cam_global.h"
#include <pthread.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct stage{

   void* (*func)(void*);
   pthread_t thread;
   bool isActive;
   Queue sourseQu;
   Queue destQu;
}stage;

typedef struct handler{
    stage stages[STAGES_NUMBER];
}handler;

typedef struct streaming_t{
    int ip;
    int port;
}streaming_t;

typedef struct snapshot_t{
    char* file_name;  //full path ?
    int width;
    int height;
    int type;  //GPEG,PNG
}snapshot_t;

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

typedef struct {
void* (*init)();
int (*start_record)(void* handler);
int (*stop_record)(record_t*);
int (*start_streaming)(streaming_t*,char * file_name);
int (*stop_streamig)(streaming_t*);
int (*do_snapshot)(snapshot_t*);
char* (*get_dll_version)();
char* (*get_video_statics)(record_t*);
char* (*get_status)();
}gazapi_t;


#ifdef __cplusplus
}
#endif

#endif // GAS_CAM_H
