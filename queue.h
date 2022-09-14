#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "linkedlist.h"

typedef struct Queue
{
    LinkedList* list;
    int size;
} Queue;

Queue *create_queue(void)
{
    Queue *q = malloc(sizeof(Queue));
    q->list = create_list();
    q->size = 0;
    return q;
}

int isEmpty(Queue *q)
{
    return (q == NULL || q->size == 0);
}

void enqueue(Queue *q, Process *data)
{
    if (q == NULL || q->list == NULL)
        return;

    q->size++;
    priority_insert(q->list, data);
}

Process* dequeue(Queue *q)
{
    if (isEmpty(q))
        return NULL;
    
    q->size--;
    return head_delete(q->list);
}

Process* peek(Queue *q)
{
    if (isEmpty(q))
        return NULL;

    return q->list->head->data;
}

#endif