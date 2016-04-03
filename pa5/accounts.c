#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>


int createAccount(char* userName, float balance){
	struct node* newnode;
	newnode = malloc(sizeof(struct node));
	newnode->name = userName;
	newnode->balance = balance; 
	while(ptr->next != NULL){
		if(ptr->name == userName){
			printf("ERROR: USER ALREADY HAS ACCOUNT");
			return 0;
		}else{
		ptr = ptr->next;
		}
	}
	ptr->next = newnode;
	return 1;
} //zero means failure, 1 means success

int deleteAccount(char* userName){
	while(ptr->next != NULL){
		if(ptr->name == userName){
			ptr->prev = ptr->next;
			free(ptr);
			return 1;
		}else{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	printf("ERROR: ACCOUNT NOT FOUND");
	return 0;
}

int credit(char* userName; float balance, float amount){ 
	while(ptr->next != NULL){
		if(ptr->name == userName){
			ptr->balance = balance + amount;
			if(ptr->balance < 0){
				printf("Transaction Complete. You have overdrawn your account\n");
				return balance;
			}else{
				printf("Transaction Completed\n");
				return balance;
			}
		}
	  ptr = ptr->next;
	}
	printf("ERROR:USER NOT FOUND");
	return 0;

}

int debit(char* userName; float balance, float amount){ 
	while(ptr->next != NULL){
		if(ptr->name == userName){
			if((balance + amount) < 0){
				printf("Can not complete transaction. Insufficient Funds\n");
				return balance;
			}else{
				ptr->balance = balance + amount;
				printf("Transaction Completed\n");
				return balance;
			}
		}
		ptr = ptr->next;
	}
	printf("ERROR:USER NOT FOUND");
	return 0;
}


