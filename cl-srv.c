// CSE531 Distributed and Multiprocessor Operating Systems
// Project 4: Client-Server Communication
/*
 *************************************************************
 * Team: 
 *	        (1)Ganesh Zilpe(1207578251)	
 *          (2)Rajesh Surana(1207633202)
 *          (3)Vishnu Priya Chandra Sekar(1207848859)
 *************************************************************/
#include "msgs.h"
#include <stdlib.h>

threadControlBlock RunQ;

void client1(){
	int i,j,k;	
	Message sentMessage;
	Message recievedMessage;
	char oprDescription[3][10];
	int id=1;
	int clientPort=1;	// Fixed for client
	int serverPort=0;
	char string[100];
	char temp = '$';
	int opr;
	int strNumber;
	char preCoded[5][100];
	int preCodedIndex;
	time_t t;
	char modifyWords[5][10];
	int modifyIndex;

	// modify stub strings
	strcpy(modifyWords[0], " grape.");
	strcpy(modifyWords[1], " banana.");
	strcpy(modifyWords[2], " apple.");
	strcpy(modifyWords[3], " peach.");
	strcpy(modifyWords[4], " orange.");

	// Operation lookup	
	strcpy(oprDescription[0], "ADD");
	strcpy(oprDescription[1], "MODIFY");
	strcpy(oprDescription[2], "DELETE");

	// precoded strings
	strcpy(preCoded[0], "Work hard. Dream big.");
	strcpy(preCoded[1], "Life is short. Live passionately.");
	strcpy(preCoded[2], "Life is a one time offer, use it well.");
	strcpy(preCoded[3], "The trouble is you think you have time.");
	strcpy(preCoded[4], "Whatever you are, be a good one.");

	// Initialize random number generator
	srand((unsigned) time(&t));

	while(1){
		opr = rand()%3;
		strNumber = rand()%10;
		sentMessage.port = clientPort;
		sentMessage.data[0] = opr;
		sentMessage.data[1] = strNumber;
		sentMessage.data[2] = 0;
		switch(opr){

			case 0: // ADD
				printf("\nClient: %02d sending request to ADD string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				preCodedIndex = rand()%5;
				for(i=0,k=0; i<strlen(preCoded[preCodedIndex]);i++,k++){

					sentMessage.data[k] = preCoded[preCodedIndex][i];
						
					if(k==9){
						send_msg(serverPort,sentMessage);
						k=-1;
					}						
				}
				if(k==-1){k=0;}
				sentMessage.data[k%10]='\0';
				send_msg(serverPort,sentMessage);
				// Check for server response
				recievedMessage = rcv_msg(clientPort);
				if(recievedMessage.data[0] == 1){
					printf("\nClient: %02d received success response for ADD request.", id);
				}
				break;

			case 1: // MODIFY
				printf("\nClient: %02d sending LOOKUP request for string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				// Read original string sent by server
				printf("\nClient: %02d reading the original string to be modified from server.", id);
				j=0;
				temp = '$';
				while(temp != '\0'){
					recievedMessage = rcv_msg(clientPort);
					for(k=0;k<10;k++){
						temp = recievedMessage.data[k];
						string[j] = temp;
						j++;
						if(temp=='\0'){
							break;					
						}
					}	
				}

				printf("\nclient: %02d modifying the string.", id);
				// Modify string
				modifyIndex = rand()%5;
				if(j>2){
					j = j-2;
				}else{
					j=0;
				}
				if(j>50){
					j = rand()%50;
				}
				for(k=0; k < strlen(modifyWords[modifyIndex]); k++,j++){
					string[j] = modifyWords[modifyIndex][k];
				}
				string[j] = '\0';

				// Send the modified string back to server 
				printf("\nClient: %02d sending the modified string to server", id);
				sentMessage.port = clientPort;
				sentMessage.data[0] = 0;
				sentMessage.data[1] = strNumber;
				sentMessage.data[2] = 1;
				send_msg(serverPort,sentMessage);
				for(j=0,k=0;j<strlen(string);j++,k++){
					sentMessage.data[k] = string[j];
					
					if(k==9){
						send_msg(serverPort,sentMessage);
						k=-1;
					}						
				}
				if(k==-1){k=0;}
				sentMessage.data[k%10]='\0';
				send_msg(serverPort,sentMessage);
				break;

			case 2: // DELETE
				printf("\nClient: %02d sending request to DELETE string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				// Check for server response
				recievedMessage = rcv_msg(clientPort);
				if(recievedMessage.data[0] == 1){
					printf("\nClient: %02d received success response for DELETE request.", id);
				}
				break;
		}		
		sleep(1);
		yield();
	}
	
}

void client2(){
	int i,j,k;	
	Message sentMessage;
	Message recievedMessage;
	char oprDescription[3][10];
	int id=2;
	int clientPort=2;	// Fixed for client
	int serverPort=0;
	char string[100];
	char temp = '$';
	int opr;
	int strNumber;
	char preCoded[5][100];
	int preCodedIndex;
	time_t t;
	char modifyWords[5][10];
	int modifyIndex;

	// modify stub strings
	strcpy(modifyWords[0], " berry.");
	strcpy(modifyWords[1], " cherry.");
	strcpy(modifyWords[2], " citron.");
	strcpy(modifyWords[3], " mango.");
	strcpy(modifyWords[4], " lemon.");

	// Operation lookup	
	strcpy(oprDescription[0], "ADD");
	strcpy(oprDescription[1], "MODIFY");
	strcpy(oprDescription[2], "DELETE");

	// precoded strings
	strcpy(preCoded[0], "A chnage is as good as rest.");
	strcpy(preCoded[1], "A bad penny always turns up.");
	strcpy(preCoded[2], "A house is not a home.");
	strcpy(preCoded[3], "A rolling stone gathers no moss.");
	strcpy(preCoded[4], "A stich in time saves nine.");

	while(1){
		opr = rand()%3;
		strNumber = rand()%10;
		sentMessage.port = clientPort;
		sentMessage.data[0] = opr;
		sentMessage.data[1] = strNumber;
		sentMessage.data[2] = 0;
		switch(opr){

			case 0: // ADD
				printf("\nClient: %02d sending request to ADD string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				preCodedIndex = rand()%5;
				for(i=0,k=0; i<strlen(preCoded[preCodedIndex]);i++,k++){

					sentMessage.data[k] = preCoded[preCodedIndex][i];
						
					if(k==9){
						send_msg(serverPort,sentMessage);
						k=-1;
					}						
				}
				if(k==-1){k=0;}
				sentMessage.data[k%10]='\0';
				send_msg(serverPort,sentMessage);
				// Check for server response
				recievedMessage = rcv_msg(clientPort);
				if(recievedMessage.data[0] == 1){
					printf("\nClient: %02d received success response for ADD request.", id);
				}
				break;

			case 1: // MODIFY
				printf("\nClient: %02d sending LOOKUP request for string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				// Read original string sent by server
				printf("\nClient: %02d reading the original string to be modified from server.", id);
				j=0;
				temp = '$';
				while(temp != '\0'){
					recievedMessage = rcv_msg(clientPort);
					for(k=0;k<10;k++){
						temp = recievedMessage.data[k];
						string[j] = temp;
						j++;
						if(temp=='\0'){
							break;					
						}
					}	
				}

				printf("\nclient: %02d modifying the string.", id);
				// Modify string
				modifyIndex = rand()%5;
				if(j>2){
					j = j-2;
				}else{
					j=0;
				}
				if(j>50){
					j = rand()%50;
				}
				for(k=0; k < strlen(modifyWords[modifyIndex]); k++,j++){
					string[j] = modifyWords[modifyIndex][k];
				}
				string[j] = '\0';

				// Send the modified string back to server 
				printf("\nClient: %02d sending the modified string to server", id);
				sentMessage.port = clientPort;
				sentMessage.data[0] = 0;
				sentMessage.data[1] = strNumber;
				sentMessage.data[2] = 1;
				send_msg(serverPort,sentMessage);
				for(j=0,k=0;j<strlen(string);j++,k++){
					sentMessage.data[k] = string[j];
					
					if(k==9){
						send_msg(serverPort,sentMessage);
						k=-1;
					}						
				}
				if(k==-1){k=0;}
				sentMessage.data[k%10]='\0';
				send_msg(serverPort,sentMessage);
				break;

			case 2: // DELETE
				printf("\nClient: %02d sending request to DELETE string at position: %02d", id, strNumber+1);
				send_msg(serverPort,sentMessage);
				// Check for server response
				recievedMessage = rcv_msg(clientPort);
				if(recievedMessage.data[0] == 1){
					printf("\nClient: %02d received success response for DELETE request.", id);
				}
				break;
		}		
		sleep(1);
		yield();
	}
	
}

void client3(){
	int i,j,k;	
	Message sentMessage;
	Message recievedMessage;
	int id=3;
	int clientPort=3;	// Fixed for client
	int serverPort=0;
	char tableCopy[10][100];
	char temp = '$';
	
	while(1){

		i=0;
		while(i<25){
			yield();
			i++;
		}

		sentMessage.port=clientPort;
		printf("\nClient: %02d is sending LOOKUP request for TABLE at server port: %02d", id, serverPort);
		sleep(1);
		send_msg(serverPort,sentMessage);
		
		for(i=0; i<10; i++){
			j=0;
			temp = '$';
			while(temp != '\0'){
				recievedMessage = rcv_msg(clientPort);
				for(k=0;k<10;k++){
					temp = recievedMessage.data[k];
					tableCopy[i][j] = temp;
					j++;
					if(temp=='\0'){
						break;					
					}
				}	
			}
		}
		printf("\nClient: %02d is printing data-", id);
		printf("\n******************************************");
		for(i=0; i<10; i++){
			printf("\nString %02d: %s", i+1, tableCopy[i]);	
		}
		printf("\n******************************************");
				
		sleep(1);
		i=0;
		while(i<25){
			yield();
			i++;
		}
	}
	
}


void server(){
	int i,j,k,opr,strNumber;
	char oprDescription[3][10];
	Message sentMessage;
	Message recievedMessage;
	int clientPort;
	int serverPort=0;	// Fixed for server
	char table[10][100];	// Local server table
	char string[100];
	char temp = '$';
	int modify = 0;

	// Operation lookup	
	strcpy(oprDescription[0], "ADD");
	strcpy(oprDescription[1], "LOOKUP");	// MODIFY = LOOKUP + ADD
	strcpy(oprDescription[2], "DELETE");

	//Initialize dummy values in the table
	strcpy(table[0],"Do not dream your life, live your dream.");
	strcpy(table[1],"A good man is hard to find.");
	strcpy(table[2],"God couldn't be everywhere, so he created mothers.");
	strcpy(table[3],"Learn from yesterday, live for today, hope for tomorrow.");
	strcpy(table[4],"In teaching others we teach ourselves.");
	strcpy(table[5],"A hungry man is an angry man.");
	strcpy(table[6],"Will will find the way.");
	strcpy(table[7],"A good beginning makes a good ending.");
	strcpy(table[8],"A man is known by his friends.");
	strcpy(table[9],"New broom sweeps clean.");
	
	while(1){

		recievedMessage=rcv_msg(serverPort);
		//printf("\n\tServer received process request at server port: %02d", serverPort);
			
		clientPort = recievedMessage.port;
		switch(clientPort){

			case 1:	// Client 1

			case 2: // Client 2

				opr = recievedMessage.data[0];
				strNumber = recievedMessage.data[1];
				modify = recievedMessage.data[2];
				if(modify != 1)
				printf("\n\tServer: Client %02d has requested %s operation on string %02d", clientPort, oprDescription[opr], strNumber+1);

				switch(opr){
					case 0: // ADD
						table[strNumber][0] = '\0';
						k =0;
						temp = '$';
						while(temp != '\0'){
							recievedMessage=rcv_msg(serverPort);
							for(i=0; i< 10; i++){

								temp = recievedMessage.data[i];
								string[k] = temp;
								k++;
								if(temp == '\0'){
									break;
								}
							}	
						}
						strcpy(table[strNumber], string);
						if(modify){
							printf("\n\tServer has successfully placed modified string: \"%s\" at position: %02d (for client %02d)", string, strNumber+1, clientPort);
						}else{
							printf("\n\tServer added/replaced string: \"%s\" at position: %02d (for client %02d)", string, strNumber+1, clientPort);
							// Send operation complete response
							sentMessage.data[0] = 1;
							send_msg(clientPort,sentMessage);
						}						
						break;

					case 1: // MODIFY
						// send the string to be modified to client
						printf("\n\tServer is sending original string to client: %d", clientPort);
						for(j=0,k=0;j<strlen(table[strNumber]);j++,k++){
							sentMessage.data[k] = table[strNumber][j];
							
							if(k==9){
								send_msg(clientPort,sentMessage);
								k=-1;
							}						
						}
						if(k==-1){k=0;}
						sentMessage.data[k%10]='\0';
						send_msg(clientPort,sentMessage);
						break;

					case 2: //DELETE
						table[strNumber][0] = '\0';
						printf("\n\tServer deleted the string at position: %02d (for client %02d)", strNumber+1, clientPort);
						// Send operation complete response
						sentMessage.data[0] = 1;
						send_msg(clientPort,sentMessage);
						break;
				}
				break;

			case 3: // Client 3
				printf("\n\tServer: Client 3 has requested table data.");	
				for(i=0; i<10; i++){
					for(j=0,k=0;j<strlen(table[i]);j++,k++){
						sentMessage.data[k] = table[i][j];
						
						if(k==9){
							send_msg(clientPort,sentMessage);
							k=-1;
						}						
					}
					if(k==-1){k=0;}
					sentMessage.data[k%10]='\0';
					send_msg(clientPort,sentMessage);			
					
				}
				printf("\n\tServer sent table data to client port: %02d", clientPort);
				break;
		}
		
		sleep(1);
		yield();
	}	
}

int main(){
	int i;	
	// Initialize 0 to 3 ports
	printf("\n********************************************************************************************");
	printf("\nOperation Description:");
	printf("\nServer table already has 10 strings.");
	printf("\nThree Operations are possible: ");
	printf("\n\tADD: As table is alreary filled, for ADD operation client sends the position of string in table\n\t\t and string to be added. If any string already present at that position, then it is simply replaced with new string.");
	printf("\n\tMODIFY: First client does LOOKUP for a string on Server by sending the position of string that it wants to modify \n\t\tto server, server sends back the string at that position to Client. Client receives that string, modifies it and sends back \n\t\tto server. Server updates the previous string with newly modified string.");
	printf("\n\tDELETE: Client sends the position of string to be deleted to server and server on receive request delete\n\t\tthe string at that position. It is assumed that client already knows the string.");
	printf("\n********************************************************************************************");
	printf("\nPress Enter to continue.....");
	getchar();
	for(i = 0; i < 4 ; i++){
		Initalize_Port(&port_array[i]);	
	}

	start_thread(&client1);	
	start_thread(&server);
	start_thread(&client2);
	start_thread(&client3);


	run();
	return 0;
}


