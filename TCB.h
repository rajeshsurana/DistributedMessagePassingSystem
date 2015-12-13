#ifndef TCB_Included					// C include guard
#define TCB_Included

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>


typedef struct TCB_t					// Thread Control Block structure
{
	struct TCB_t *next;
	struct TCB_t *prev;
	ucontext_t context;
}TCB_t;

void init_TCB(void *function, void *stack, int stack_size, TCB_t *tcb)
{
	memset(tcb, '\0', sizeof(TCB_t));
	getcontext(&tcb->context);              		// initialize context
	tcb->context.uc_stack.ss_sp = stack;
	tcb->context.uc_stack.ss_size = (size_t)stack_size;
	makecontext(&tcb->context, function, 0);		// assign function to context
}

#endif
