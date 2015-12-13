#ifndef sem_Included					// C include guard
#define sem_Included

#include "threads.h"


extern threadControlBlock RunQ;
typedef struct{
	int counter;
	threadControlBlock semaphore_q;
} Semaphore_t;

Semaphore_t* CreateSem(int InputValue){
	Semaphore_t *s=(Semaphore_t *)malloc(sizeof(Semaphore_t));
	s->counter=InputValue;
	return s;
}

void P(Semaphore_t *sem){
	
	sem->counter--;
	if(sem->counter<0){
		TCB_t *tmp=DelQueue(&RunQ);	
		AddQueue(&sem->semaphore_q,tmp);
		swapcontext(&(tmp->context),&(RunQ->context));	
	}
}

void V(Semaphore_t *sem){
	
	sem->counter++;
	if(sem->counter<=0)
	{
		AddQueue(&RunQ,DelQueue(&sem->semaphore_q));
		yield();	
	}
}
#endif
