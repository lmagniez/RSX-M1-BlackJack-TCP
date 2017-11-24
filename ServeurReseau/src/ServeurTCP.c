#include "../lib/ServeurTCP.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCP = 1;

plateau p;

void * threadServeurTCPConnection(void * arg){
	int tcp_socket = socket_TCP();
	TCP_bind_server(tcp_socket,9090);

	while(receiveTCP){
		int ecoute = wait_connection_TCP(tcp_socket);
		char * msg = receive_data_TCP(ecoute);	

		//ICI ON PARSE POUR VOIR CREATION DU TRHEAD DEDIE AU CLIENT 
		//POUR SAVOIR SI C'EST BIEN UNE DEMANDE DE CONNECTION	

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0){ 
			free(msg);
			//GERER DECONNECTION CLIENT SERVEUR ICI
			continue;
		}

		printf("%s\n",msg);

		//pthread_t client = startServeurTCPClient(ecoute);

		free(msg);
	}

	close_TCP(tcp_socket);	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurTCPConnection(){
	init_plateau(&p);
	pthread_t threadServeur;
	if(pthread_create(&threadServeur, NULL, threadServeurTCPConnection, NULL) == -1) {
		perror("pthread_create()\n");
		exit(0);
    }
    return threadServeur;
}
