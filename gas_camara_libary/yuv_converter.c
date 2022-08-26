#include "yuv_converter.h"
void convert_to_yuv(char rgb_matrix[],  YUV *yuv){
    char R,G,B;
    int i=0,j=0;
    for(int i=0;i<SNAPSHOT_HEIGHT;i++)
    {
        for(int j=0;j<SNAPSHOT_WIDTH;j++)
        {
            R=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3);
            G=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3+1);
            B=*(rgb_matrix+i*SNAPSHOT_WIDTH*3+j*3+2);
            yuv->y[SNAPSHOT_WIDTH*i+j]= (0.257 * R) + (0.504 * G) + (0.098 * B) + 16+'0';
            if(i%2==0&&j%2==0)
            {
                yuv->u[(SNAPSHOT_WIDTH*i+j)/4]= (0.439 * R) - (0.368 * G) - (0.071 * B) + 128+'0';
                yuv->v[(SNAPSHOT_WIDTH*i+j)/4]= -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128+'0';
            }
        }
    }
}
void free_rgb_matrix(char * m){
    free(m);
    m=NULL;
}
yuv_converter_t *init_yuv_converter_t(int *st){
    yuv_converter_t *yuv_c_t=(yuv_converter_t*)malloc(sizeof (yuv_converter_t));
    yuv_c_t->status=st;
    return yuv_c_t;
}
void free_yuv(YUV *yuv){
    free(yuv);
}
Node* yuv_converter(void * my_arg,Node * node)
{
    if(node->data!=NULL)
    {   YUV * yuv=(YUV*)malloc(sizeof(YUV));
        convert_to_yuv((char*)node->data,yuv);
        char * c=(char*)(node->data);
        free_rgb_matrix(c);
        node->data=yuv;
        printf("yuv %c\n",((YUV*)(node->data))->u[0]);
    }
    return node;
}







