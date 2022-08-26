#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include  <semaphore.h>
#define SIZE_POOL_NODE 20
typedef struct node{
    void* data;
    struct node* next;
}Node;

typedef struct queue{

    sem_t mutex;
    sem_t is_full_mutex;
    unsigned int size;
    unsigned int capacity;
    struct node* head;
    struct node* tail;
}Queue;
typedef struct pool_node{
    int index_arr;
    Node * arr_node[SIZE_POOL_NODE];
} pool_node;
pool_node *init_pool_queue();
void free_pool_node(pool_node * pn);
Node * createNode(pool_node * pn,void * data);
Queue* createQueue(int capacity);
void initQueue(Queue*,int capacity);
void freeNode(Node* node);
void freeQueue(Queue* q);
int getCapacity(Queue* q);
int getSize(Queue* q);
void enqueu(Queue* q,Node* data);
Node* dequeue(Queue* q);
int isEmpty(Queue* q);
int isFull(Queue *q);
#endif // QUEUE_H


