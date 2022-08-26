#ifndef SATGE_H
#define SATGE_H
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <unistd.h>
#define SECOND 1000000
#define NUM_FRANE_PER_SECOND 40
#define WAIT SECOND/NUM_FRANE_PER_SECOND
#include "libary_handler.h"
typedef Node * (*task_func)(int * ,Node  *);
typedef struct stage{
    pthread_t thread;
    bool isActive;
    Queue* sourseQu;
    Queue* destQu;
    task_func func;
    void * my_arg;
    struct stage * next_satge;
}stage;

typedef  struct task{
    stage * my_stage;
     // node * my_current_node;

} task_t;
stage * init_stage(task_func func ,Queue * destq,Queue * sourcq,stage* next,void * arg);
void * main_satge(void *);
#endif // SATGE_H
