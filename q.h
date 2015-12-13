#ifndef Q_Functions_Included				// C include guard
#define Q_Functions_Included

#include "TCB.h"


typedef struct TCB_t *threadControlBlock;

threadControlBlock NewItem()					// Create new Queue element
{
	return (threadControlBlock)(malloc(sizeof(TCB_t)));
}

void InitQueue(threadControlBlock *head)			// Create empty queue by initializing its head to NULL
{
	*head = NULL;
}

void AddQueue(threadControlBlock *head, threadControlBlock item)	// Add element to Queue tail
{
	if(item == NULL);				// if item is NULL, do nothing
	else if(*head==NULL)				// if Queue is empty, head = item
	{
		*head = item;
		(*head)->prev = item;
		(*head)->next = item;
	}
	else						// if Queue has 1 or more elements
	{
		(*item).next = *head;
		(*item).prev = (*head)->prev;
		(*head)->prev->next = item;
		(*head)->prev = item;
	}
}

threadControlBlock DelQueue(threadControlBlock *head)			// Delete head element of Queue
{
	if(*head == NULL)				// if Queue is empty, there is nothing to delete
		return NULL;

	threadControlBlock temp = *head;
	if((*head)->next == *head)			// if Queue has only 1 element
		*head = NULL;
	else						// if Queue has 2 or more elements
	{
		*head = (*head)->next;
		temp->prev->next = *head;
		(*head)->prev = temp->prev;
	}
	return temp;
}

void RotateQ(threadControlBlock *head)				// Rotate Queue head to next element
{
	if(*head != NULL)				// if Queue has 1 or more elements
	*head = (*head)->next;				// move the second element into the header
}

#endif
