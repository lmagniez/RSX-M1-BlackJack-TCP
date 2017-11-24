#include "../lib/ServeurTCPClient.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCPClient = 1;

void * threadServeurTCPClient(void * arg){

	int * ecoutePointeur = (int *) arg;
	int ecoute = *ecoutePointeur;
	while(receiveTCPClient){
		
		send_data_TCP(ecoute,"coucou\n");	

		char * msg = receive_data_TCP(ecoute);	

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0){ 
			free(msg);
			//GERER DECONNECTION CLIENT SERVEUR ICI
			continue;
		}
		//FUTUR CREATION DU THREAD POUR CLIENT
		printf("%s\n",msg); 
		free(msg);
	}

	close_TCP(ecoute);	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurTCPClient(int socket){
	pthread_t threadServeur;
	if(pthread_create(&threadServeur, NULL, threadServeurTCPClient, &socket) == -1) {
		perror("pthread_create_client()\n");
		exit(0);
    }
    return threadServeur;
}
