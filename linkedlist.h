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

node *create_node(Process *data)
{
	node *n = malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	return n;
}

LinkedList *create_list(void)
{
	return calloc(1, sizeof(LinkedList));
}

node *recursive_destroyer(node *head)
{
	if (head == NULL)
		return NULL;
	
	recursive_destroyer(head->next);
	free(head);

	return NULL;
}

LinkedList *destroy_list(LinkedList *list)
{
	if (list == NULL)
		return NULL;
	
	recursive_destroyer(list->head);
	free(list);

	return NULL;
}

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


void priority_insert(LinkedList *list, Process *data)
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

	if (ins->data->priority < list->head->data->priority)
	{
		ins->next = list->head;
		list->head = ins;
		return;
	}

	if (ins->data->priority > list->tail->data->priority)
	{
		list->tail->next = ins;
		list->tail = ins;
		return;
	}

	node* temp = list->head;
	while (temp->next != NULL && temp->next->data->priority < ins->data->priority)
		temp = temp->next;

	ins->next = temp->next;
	temp->next = ins;

	
}

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

int compare_nodes(const void *a, const void *b)
{
	return ( (*(node**)a)->data->priority - (*(node**)b)->data->priority );
}



#endif