#include "../lib/ServeurUDP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

#define COMEHERE "COME HERE TO HAVE FUN"

int receiveUDP = 1;

char * verificationPartie(){
	return COMEHERE;
}

void sendBackBroadcast(struct client c){
	int sock = socket_UDP();

	char * message = verificationPartie();

	send_UDP(sock,c.host,c.port,message);
}

void * threadServeurUDP(void * arg){
	int udp_sock = socket_UDP();
	int port = atoi("8080");
	UDP_bind_server(udp_sock,port);
	while(receiveUDP){
		struct client client = recv_UDP(udp_sock,port);
		sendBackBroadcast(client);	
	}
	close_UDP(udp_sock);
	
	(void) arg;
    pthread_exit(NULL);
}


pthread_t startServeurUDP(){
	pthread_t threadServeur;
	if(pthread_create(&threadServeur, NULL, threadServeurUDP, NULL) == -1) {
		perror("pthread_create()\n");
		exit(0);
    }

    if (pthread_join(threadServeur, NULL)) {
		perror("pthread_join");
		exit(0);
    }
    
    return threadServeur;
}
