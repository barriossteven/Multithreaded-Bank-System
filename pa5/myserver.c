#include <stdio.h>
#include <string.h>    
#include <stdlib.h>  
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>   
#include <pthread.h>
#include "bank.h"
#include "myserver.h" 

void *timedPrint(){
	while(1){
		sleep(20);
		pthread_mutex_lock(&mutex);
		int i = 0;
		if(1){ //while there are accounts
			while(i <= 19){
				if(1){ //go through all accounts and print them
					// printf("%d <Account: %s, Balance: %f, Currently Active: %s >" , i,  ACCOUNTS->accounts[i]->name, ACCOUNTS->accounts[i]->balance, ACCOUNTS->accounts[i]->active);
				}
				i++;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}


void createSessionAcceptorThread(int sockfd){

	int socket_fd , client_fd , c;
	struct sockaddr_in server , client;

	socket_fd = socket(AF_INET , SOCK_STREAM , 0);

	puts("Socket created");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 5560 );

	if( bind(socket_fd,(struct sockaddr *)&server , sizeof(server)) < 0){
		perror("ERROR BIND FAILED");
		return ;
	}

	puts("BIND COMPLETED");

	int connectionsnum = 0;

	while(connectionsnum < 20){
			listen(socket_fd , 20); //max number of connections is 20 (i think this is what this means, second argument is backlog)

			puts("Waiting for incoming connections...");
			c = sizeof(struct sockaddr_in);
			pthread_t thread_id;

			while( (client_fd = accept(socket_fd, (struct sockaddr *)&client, (socklen_t*)&c)) ){
			puts("CONNECTION ACCEPTED");
			connectionsnum++;
			if( pthread_create( &thread_id , NULL ,  createSessionHandler , (void*) &client_fd) < 0){
			perror("COULD NOT CREATE THREAD");
			return ;
			}

			puts("CONNECTION ASSIGNED A HANDLER");
			}
			}
			}
			/*
			 * This will handle connection for each client
			 * */
void *createSessionHandler(void *socket_fd)
{
	//Get the socket descriptor
	int toclient = *(int*)socket_fd;
	int read_size;
	char *message , client_message[2000], *t, *s, *command, *f, *a;

	s = "You wish to create an account.\n";
	f = "Not valid command\n";
	a = "You wish to delete an account\n";
	message = "==========================\n =  Welcome to Your Bank  =\n ==========================\n Welcome to Bank. Please enter a command to begin.\n Would you like to create an account, delete an account, withrdraw from an account, or deposit to an account?\n";
	write(toclient , message , strlen(message));
	fflush(stdin);
	//Receive a message from client
	while((read_size = recv(toclient , client_message , 2000 , 0)) > 0 )
	{

		client_message[read_size] = '\0';    
		command = strtok(client_message, " ");    
		if(strcmp(command, "open") == 0){
			write(toclient, s, strlen(s));
			write(toclient, "Please enter your name\n", 22);
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "start") == 0){
			write(toclient, a, strlen(a));
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "credit") == 0){
			write(toclient, "How much would you like to withdraw?\n", 37);
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "debit") == 0){
			write(toclient, "How much would like to deposit\n", 36);
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "balance") == 0){
			write(toclient, "How much would like to deposit\n", 36);
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "finish") == 0){
			write(toclient, "How much would like to deposit\n", 36);
			memset(client_message, 0, 2000);
		}
		if(strcmp(command, "exit") == 0){
			write(toclient, "How much would like to deposit\n", 36);
			memset(client_message, 0, 2000);
		}else{
			write(toclient," ", 1);
		}
		memset(client_message, 0, 2000);
	}

	if(read_size == 0)
	{
		puts("Client Disconnected");
		fflush(stdout);
		exit(1);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	return 0;
}


int main(int argc , char **argv){
	int timer_thread_tid, i;
	i = 0;
	pthread_t timer_thread;
	timer_thread_tid = pthread_create(&timer_thread, NULL, (void*(*)(void*))timedPrint, NULL);
	pthread_t newth;
	i = pthread_create(&newth, NULL, (void*)createSessionAcceptorThread, NULL);
	if( i != 0){
		printf("pthread_create HAS FAILED\n");
		return 0;
	}
	return 0;
}

