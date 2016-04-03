void *createSessionHandler(void *);
static pthread_mutex_t mutex;  
void createSessionAcceptorThread(int sockfd);
/*
 * This will handle connection for each client
 * */
void *timedPrint();
void *createSessionHandler(void *socket_fd);
