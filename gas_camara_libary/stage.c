#include "stage.h"

int i=1;
stage * init_stage(task_func func ,Queue * destq,Queue * sourcq,stage* next,void * arg)
{
    stage * my_stage=(stage *)malloc(sizeof(stage));
    my_stage->isActive=0;
    my_stage->next_satge=NULL;
    my_stage->destQu=destq;
    my_stage->sourseQu=sourcq;
    my_stage->func=func;
    my_stage->next_satge=next;
    my_stage->my_arg=arg;
    return my_stage;
}
void * main_satge(void * arg)
{
  stage * my_stage=(stage*)(arg);

    Node * n=NULL;
    if(my_stage->sourseQu)
        n=dequeue(my_stage->sourseQu);
    do{
        n= my_stage->func(my_stage->my_arg,n);
        if((my_stage->destQu)!=NULL)
        {  enqueu(my_stage->destQu,n);
            sleep(2);
        }
        else
        {
            freeNode(n);
        }
        if((my_stage->sourseQu!=NULL))
        {
            n=dequeue(my_stage->sourseQu);

        }
        if(n->data==NULL)
            printf("N->data is NULL");
    }while(n->data);
    if(my_stage->destQu)
        enqueu(my_stage->destQu,n);
    else
        freeNode(n);
}
