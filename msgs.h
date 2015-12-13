#ifndef msg_Included					// C include guard
#define msg_Included

#include "sem.h"

/* Strategy 2: mutex per port and a producer semaphore and a consumer semaphore - per port  0.06 to 0.194ms */

// Structure for  message
typedef struct msg_struct{
	int port;	
	int data[10];
}Message;

//Structure for port
typedef struct port_struct{
	Message msg[10];
	int read_index;
	int write_index;
	Semaphore_t *empty;
	Semaphore_t *full;
	Semaphore_t *mutex;  
}Port;

// set of ports , numbered from 0 to 99
Port port_array[100];


void Initalize_Port(Port *port){
	int i;	
	port->read_index=0;
	port->write_index=0;
	port->empty=CreateSem(10);
	port->full=CreateSem(0);
	port->mutex=CreateSem(1);
	for(i=0;i<10;i++)
	   (port->msg)->data[i]='0';
}

// Send the msg through the corresponding port no
void send_msg(int port_no,Message message){
		Port *p=&port_array[port_no];
	
		P(p->empty);
			P(p->mutex);
				p->msg[p->write_index]=message;
				p->write_index=(p->write_index+1)%10;
			V(p->mutex);	
		V(p->full);
			
}

// Receive the message from the specified port no
Message rcv_msg(int port_no){
		Message rcv_msg;
		Port *p=&port_array[port_no];
		P(p->full);
			P(p->mutex);	
		     		 rcv_msg=p->msg[p->read_index];
		     		 p->read_index=(p->read_index+1)%10;
			V(p->mutex);	
		V(p->empty);
	
return rcv_msg;
}
#endif
