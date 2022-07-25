/*#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


 typedef struct node
{
    char* key;
  //  Func val;
    struct node *next;
}Node;
typedef struct table
{
    int size;
    struct node **list;
}Table;
struct table *createTable(int size);
int hashCode(struct table *t, char* key);
void set(struct table *t, char* key, genericFunc val);
genericFunc get(struct table *t, char* key);

#endif // HASHTABLE_H
*/
