#include "capture.h"
#include "libary_handler.h"
#include "queue.h"
#include "stdbool.h"
capture_t * init_capture_t(int * st,int record_bit,int stop_active_bit,int snapshot_bit,bool * snap_hand_bit )
{
    capture_t *cap_t=(capture_t*)malloc(sizeof(capture_t));
    cap_t->status=st;
    cap_t->record_active_bit=record_bit;
    cap_t->snapshot_active_bit=snapshot_bit;
    cap_t->stop_active_bit=stop_active_bit;
    cap_t->snapshot_handler_bit=snap_hand_bit;
    return cap_t;
}
void randMat(int** matrix_temp){
    int i,j,new_temp,height_pos,width_pos,num_iterations=0.1*SNAPSHOT_WIDTH*SNAPSHOT_HEIGHT;
    for(i=0;i<SNAPSHOT_HEIGHT;i++){
        for(j=0;j<SNAPSHOT_WIDTH;j++){
            matrix_temp[i][j]=27;
        }
    }
    for(i=0;i<num_iterations;i++)
    {
        height_pos=rand() % SNAPSHOT_HEIGHT;
        width_pos=rand() % SNAPSHOT_WIDTH;
        new_temp=rand()%(MAX_TEMP+1);
        matrix_temp[height_pos][width_pos]=new_temp;
    }
}
Node  *capture(void * my_arg,Node * node)
{
    printf("capture\n");
    capture_t *cap_t=(capture_t*)my_arg;
    if((*(cap_t->status)&cap_t->record_active_bit)||(*(cap_t->snapshot_handler_bit)==true))
    {
       //to off the bit becase we want to create only one matrix when the snapsot is on
        if(*(cap_t->snapshot_handler_bit)==true)
           *(cap_t->snapshot_handler_bit)=false;
        int **  matrix=(int**)malloc(sizeof(int *)*SNAPSHOT_HEIGHT);
        matrix=(int**)malloc(sizeof(int *)*SNAPSHOT_HEIGHT);
        for(int i=0;i<SNAPSHOT_HEIGHT;i++)  {
            matrix[i]=NULL;
            matrix[i]=(int *)malloc(sizeof(int)*SNAPSHOT_WIDTH);
        }
        randMat(matrix);
        node=createNode(matrix, sizeof(int));

    }

    else
        node=createNode(NULL,0);
    return node;
}
