#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "process.h"

typedef struct node
{
    Process *data;
    struct node *next;
} node;

typedef struct LinkedList
{
    node *head;
    node *tail;
} LinkedList;

// creates a node
node *create_node(Process *data)
{
    node *n = malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

// creates a linked list
LinkedList *create_list(void)
{
    return calloc(1, sizeof(LinkedList));
}

// recursively destroys a LinkedList
node *recursive_destroyer(node *head)
{
    if (head == NULL)
        return NULL;
    
    recursive_destroyer(head->next);
    free(head);

    return NULL;
}

// destroys a LinkedList
LinkedList *destroy_list(LinkedList *list)
{
    if (list == NULL)
        return NULL;
    
    recursive_destroyer(list->head);
    free(list);

    return NULL;
}

// inserts data at the tail of our LinkedList
void tail_insert(LinkedList *list, Process *data)
{
    if (list == NULL)
        return;

    if (list->tail == NULL)
    {
        list->head = list->tail = create_node(data);
        return;
    }

    list->tail->next = create_node(data);
    list->tail = list->tail->next;
}

// deletes the head of our LinkedList
Process* head_delete(LinkedList *list)
{
    Process* retval;
    node *temp;

    if (list == NULL || list->head == NULL)
        return NULL;

    retval = list->head->data;

    temp = list->head->next;

    free (list->head);

    list->head = temp;

    if (list->head == NULL)
        list->tail = NULL;

    return retval;
}

// inserts data into our LinkedList, sorted by arrival time
void arrival_insert(LinkedList *list, Process *data)
{
    node* ins = create_node(data);
    ins->next = NULL;

    if (list == NULL)
        return;

    if (list->tail == NULL)
    {
        list->head = list->tail = ins;
        return;
    }

    if (ins->data->arrival < list->head->data->arrival)
    {
        ins->next = list->head;
        list->head = ins;
        return;
    }

    if (ins->data->arrival > list->tail->data->arrival)
    {
        list->tail->next = ins;
        list->tail = ins;
        return;
    }

    node* temp = list->head;
    while (temp->next != NULL && temp->next->data->arrival < ins->data->arrival)
        temp = temp->next;

    ins->next = temp->next;
    temp->next = ins;
}

// inserts data into our LinkedList, sorted by time left
void tleft_insert(LinkedList *list, Process *data)
{
    node* ins = create_node(data);
    ins->next = NULL;

    if (list == NULL)
        return;

    if (list->tail == NULL)
    {
        list->head = list->tail = ins;
        return;
    }

    if (ins->data->tleft < list->head->data->tleft)
    {
        ins->next = list->head;
        list->head = ins;
        return;
    }

    if (ins->data->tleft > list->tail->data->tleft)
    {
        list->tail->next = ins;
        list->tail = ins;
        return;
    }

    node* temp = list->head;
    while (temp->next != NULL && temp->next->data->tleft < ins->data->tleft)
        temp = temp->next;

    ins->next = temp->next;
    temp->next = ins;

    
}

// inserts data into our LinkedList, sorted by process number
void num_insert(LinkedList *list, Process *data)
{
    node* ins = create_node(data);
    ins->next = NULL;

    if (list == NULL)
        return;

    if (list->tail == NULL)
    {
        list->head = list->tail = ins;
        return;
    }

    if (ins->data->num < list->head->data->num)
    {
        ins->next = list->head;
        list->head = ins;
        return;
    }

    if (ins->data->num > list->tail->data->num)
    {
        list->tail->next = ins;
        list->tail = ins;
        return;
    }

    node* temp = list->head;
    while (temp->next != NULL && temp->next->data->num < ins->data->num)
        temp = temp->next;

    ins->next = temp->next;
    temp->next = ins;

    
}

// gets count of items in our LinkedList
int get_count(LinkedList *l)
{
    int count = 0;
    node* curr = l->head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

// increments the turnaround of all processes in our LinkedList
void l_increment_turnaround(LinkedList *l)
{
    node* temp = l->head;
    while (temp != NULL)
    {
        temp->data->turnaround++;
        temp = temp->next;
    }
    
    return;
}



#endif