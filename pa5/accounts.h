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
//#include "accounts.c"


struct node{
	char* name;
	float balance;
	struct node *next;
	struct node *prev;
};

struct accountlist{
	struct node* root;
	
};

int createAccount(char* userName, float balance);

int deleteAccount(char* userName);

int credit(char* userName, float balance, float amount);

int debit(char* userName, float balance, float amount);
