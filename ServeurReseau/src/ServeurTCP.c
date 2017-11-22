#include "../lib/ServeurTCP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCP = 1;

void * threadServeurTCPConnection(void * arg){
	int tcp_socket = socket_TCP();
	TCP_bind_server(tcp_socket,9090);

	while(receiveTCP){
		int ecoute = wait_connection_TCP(tcp_socket);	
		char * msg = receive_data_TCP(ecoute);

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0){ 
			printf("Fin connection \n");
			free(msg);
			//GERER DECONNECTION CLIENT SERVEUR ICI

			break;
		}

		printf("%s\n",msg); 
		msg = msg+25;
		msg[strlen(msg)-1] = '\0';

		int tcp_sock_send = socket_TCP();
		connect_TCP(tcp_sock_send,msg,9090);
		send_data_TCP(tcp_sock_send,"C'est bon");
		close_TCP(tcp_sock_send);


		free(msg);
	}
	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurTCPConnection(){
	pthread_t threadServeur;
	if(pthread_create(&threadServeur, NULL, threadServeurTCPConnection, NULL) == -1) {
		perror("pthread_create()\n");
		exit(0);
    }
    return threadServeur;
}
