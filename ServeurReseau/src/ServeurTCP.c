#include "../lib/ServeurTCP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCP = 1;

void * threadServeurTCP(void * arg){

	while(receiveTCP){
		printf("TCP\n");
	}
	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurTCP(){
	pthread_t threadServeur;
	printf("coucou \n");
	if(pthread_create(&threadServeur, NULL, threadServeurTCP, NULL) == -1) {
		perror("pthread_create()\n");
		exit(0);
    }

    if (pthread_join(threadServeur, NULL)) {
		perror("pthread_join");
		exit(0);
    }
    
    return threadServeur;
}
