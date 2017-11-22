#include "../lib/ServeurTCP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCP = 1;

void * threadServeurTCP(void * arg){

	int tcp_socket = socket_TCP();
	TCP_bind_server(tcp_socket,9090);
	int ecoute = wait_connection_TCP(tcp_socket);	
	
	while(receiveTCP){
		receive_data_TCP(ecoute);
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
