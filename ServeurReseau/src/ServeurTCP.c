#include "../lib/ServeurTCP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCP = 1;

void * threadServeurTCP(void * arg){
	printf("TCP THREAD \n");
	while(receiveTCP){

	}
	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurTCP(){
	pthread_t threadServeur;
	if(pthread_create(&threadServeur, NULL, threadServeurTCP, NULL) == -1) {
		perror("pthread_create()\n");
		exit(0);
    }
    return threadServeur;
}
