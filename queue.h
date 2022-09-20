#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "linkedlist.h"

typedef struct Queue
{
    LinkedList* list;
    int size;
} Queue;

// creates a queue
Queue *create_queue(void)
{
    Queue *q = malloc(sizeof(Queue));
    q->list = create_list();
    q->size = 0;
    return q;
}

// checks if a queue is empty. returns 1 if empty, else returns 0
int isEmpty(Queue *q)
{
    return (q == NULL || q->size == 0 || q->list == NULL || q->list->head == NULL);
}

// enqueues data into our queue, sorted by arrival time
void a_enqueue(Queue *q, Process *data)
{
    if (q == NULL || q->list == NULL)
        return;

    q->size++;
    arrival_insert(q->list, data);
}

// enqueues data into our queue, sorted by time left
void t_enqueue(Queue *q, Process *data)
{
    if (q == NULL || q->list == NULL)
        return;

    q->size++;
    tleft_insert(q->list, data);
}

// enqueues data into our queue, sorted by process number
void n_enqueue(Queue *q, Process *data)
{
    if (q == NULL || q->list == NULL)
        return;

    q->size++;
    num_insert(q->list, data);
}

// enqueues data into our queue, put in back
void b_enqueue(Queue *q, Process *data)
{
    if (q == NULL || q->list == NULL)
        return;

    q->size++;
    tail_insert(q->list, data);
}

// dequeues
Process* dequeue(Queue *q)
{
    if (isEmpty(q))
        return NULL;
    
    q->size--;
    return head_delete(q->list);
}

// peeks at head of queue
Process* peek(Queue *q)
{
    if (isEmpty(q))
        return NULL;

    return q->list->head->data;
}

// processes a queue (decrements the head)
Process* process_q(Queue *q)
{
    if (q == NULL || q->list == NULL || isEmpty(q))
        return NULL;
    
    q->list->head->data->tleft--;

    return peek(q);
}

// incremenets the turnaround of all things in a queue
void q_increment_turnaround(Queue *q)
{
    if (q == NULL || q->list == NULL)
        return;

    l_increment_turnaround(q->list);

    return;    
}

void print_q(Queue *q)
{
    printf("list: ");
    node* t = q->list->head;
    while (t != NULL)
    {
        printf("%s -> ", t->data->name);
        t = t->next;
    }
    printf("\n");
}

#endif