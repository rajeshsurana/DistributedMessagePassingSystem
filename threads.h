#ifndef Threads_Included					// C include guard
#define Threads_Included

#include "q.h"
#define stackSize 8192
extern threadControlBlock RunQ;

void start_thread(void *function)
{
	void *stack = malloc(stackSize);
	TCB_t *tcb = NewItem();
	init_TCB(function, stack, stackSize, tcb);		// create thread
	AddQueue(&RunQ,tcb);					// place it in run queue
}

void run(void)
{	

	ucontext_t parent;					// get a place to store the main context, for faking
	getcontext(&parent);					// magic sauce
	swapcontext(&parent, &(RunQ->context));			// start the first thread
}

void yield(void)
{
	RotateQ(&RunQ);
	swapcontext(&(RunQ->prev->context),&(RunQ->context));	// switch to next thread
}

#endif
