#include "queue.h"

Node * createNode(pool_node * pn,void * data){
    if(pn->index_arr==SIZE_POOL_NODE)
        pn->index_arr=0;
    if(pn->arr_node[pn->index_arr]->data!=1&&pn->arr_node[pn->index_arr]->data!=NULL)
    {
     printf("the pool is full!\nexit");
     exit(1);
    }
    Node* node=pn->arr_node[pn->index_arr++];
    node->data=data;
    node->next=NULL;
    return node;
}
pool_node *init_pool_queue(){
    pool_node * pn=(pool_node*)malloc(sizeof(pool_node));
    for(int i=0;i<50;i++)
    {
        pn->arr_node[i]=(Node*)malloc(sizeof(Node));
        pn->arr_node[i]->data=NULL;
    }
    pn->index_arr=0;
}
void free_pool_node(pool_node * pn)
{
    for(int i=0;i<50;i++)
    {
        freeNode(pn->arr_node[i]);
    }
    free(pn);
    pn=NULL;
}
Queue* createQueue(int capacity){
    printf("capacity!!! %d",capacity);
    Queue *q=(Queue*)malloc(sizeof(Queue));
    initQueue(q,capacity);
    return q;
}
void initQueue(Queue* q,int capacity){


    q->capacity=capacity;
    q->size=0;
    q->head=NULL;
    q->tail=NULL;
    sem_init(&(q->mutex),0,1);//to do sync
    sem_init(&(q->is_full_mutex),0,capacity);//to check if there is place
    while(capacity)
    {
        sem_wait(&(q->is_full_mutex));
        capacity--;
    }
    return;
}
void freeNode(Node* node){
    if(node==NULL)
        return;
    free(node);
    node=NULL;
}
void freeQueue(Queue* q){
    if(q==NULL)
        return;
    sem_destroy(&q->mutex);
    sem_destroy(&q->is_full_mutex);
    while(!isEmpty(q)){
        freeNode(dequeue(q));
    }
    free(q);
    q=NULL;
}
int getCapacity(Queue* q){
    return q->capacity;
}
int getSize(Queue* q){
    return q->size;
}
void enqueu(Queue* q,Node* data){

    sem_wait(&q->mutex);//lock sem

    if(q->size==q->capacity){
        return;
    }
    if(q->head==NULL){
        q->head=q->tail=data;
    }
    else{
        q->tail->next=data;
        q->tail=data;
    }
    q->size++;
    sem_post(&q->mutex);//free sem
    sem_post(&q->is_full_mutex);
}
Node* dequeue(Queue* q){
    Node* temp;
    sem_wait(&q->is_full_mutex);
    sem_wait(&q->mutex);//lock sem
    temp=q->head;
    q->head=q->head->next;
    q->size--;
    if(isEmpty(q))
        q->head=q->tail=NULL;
    sem_post(&q->mutex);//free sem
    return temp;
}
int isEmpty(Queue* q){
    return q->size==0;
}
int isFull(Queue *q){
    sem_wait(&q->mutex);//lock sem
    int isFull=q->size==q->capacity;
    sem_post(&q->mutex);//free sem
    return isFull;
}
