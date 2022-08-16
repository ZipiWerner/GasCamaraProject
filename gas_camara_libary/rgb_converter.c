#include "rgb_converter.h"

void free_matrix(int** m){
    for(int i=0;i<SNAPSHOT_HEIGHT;i++){
        free(m[i]);
        m[i]=NULL;
    }
    m=NULL;
}
void covert_to_rgb(char *rgb_matrix,int** matrix,char * static_mat_rgb){//[SNAPSHOT_HEIGHT][SNAPSHOT_WIDTH] [SNAPSHOT_HEIGHT][SNAPSHOT_WIDTH]
    int k=0;
    for(int i=0;i<SNAPSHOT_HEIGHT;i++)
        for(int j=0;j<SNAPSHOT_WIDTH;j++)
        {
            int t=matrix[i][j]*3;
            rgb_matrix[k++]=static_mat_rgb[t];
            rgb_matrix[k++]=static_mat_rgb[t+1];
            rgb_matrix[k++]=static_mat_rgb[t+2];
        }
}
rgb_converter_t * init_rgb_converter_t(int * st,char * rgb_matrix,int  snapshot_bit,int  record_bit)
{
    rgb_converter_t  *rgb_c_t=(rgb_converter_t*)malloc(sizeof(rgb_converter_t));
    rgb_c_t->status=st;
    rgb_c_t->static_rgb_matrix=rgb_matrix;
    rgb_c_t->snapshot_active_bit=snapshot_bit;
    rgb_c_t->record_active_bit=record_bit;
    return rgb_c_t;
}
Node  * rgb_converter(void * my_arg,Node * node)
{
    if(node->data!=NULL)
    {  rgb_converter_t * rgb_t=(rgb_converter_t*)my_arg;
        printf("rgb convert\n");
        char * rgb_matrix=(char *)malloc(sizeof(char)*(SNAPSHOT_HEIGHT*SNAPSHOT_WIDTH*3));
        covert_to_rgb(rgb_matrix,(int**)node->data,rgb_t->static_rgb_matrix);
        *rgb_matrix=0;
        free_matrix((int**)node->data);
        // freeNode(node);
        //need to get argument status in order to now if to snapshot and get the static mat
        if((*(rgb_t->status))&(rgb_t->snapshot_active_bit))
        {
            save_snapshot(NULL,rgb_matrix);
            if(!(*(rgb_t->status)&(rgb_t->record_active_bit)))
            {
                free(rgb_matrix);
                rgb_matrix=NULL;
            }
            //to turn off the bit of the snapshot
            //in order to turn on the led
            printf("snapshot now!!!\n");
            *(rgb_t->status)=((*(rgb_t->status))&(~(rgb_t->snapshot_active_bit)));
        }
        node->data=rgb_matrix;
    }
    return node;
}
