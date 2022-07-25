/*
 #include "HashTable.h"

struct table *createTable(int size)
{
    struct table *t = (struct table *)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node **)malloc(sizeof(struct node *) * size);
    int i;
    for (i = 0; i < size; i++)
        t->list[i] = NULL;
    return t;
}
int hashCode(struct table *t, char* key)
{
    return *key % t->size;
}
void set(struct table *t, char* key, genericFunc val)
{
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    struct node *temp = list;
    while (temp)
    {
        if (temp->key == key)
        {
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}
genericFunc get(struct table *t, char* key)
{
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while (temp)
    {
        if (!strcmp(temp->key,key))
        {
            return temp->val;
        }
        temp = temp->next;
    }
    return NULL;
}
*/
