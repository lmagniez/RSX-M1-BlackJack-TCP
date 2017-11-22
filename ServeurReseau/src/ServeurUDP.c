#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include "../lib/ServeurUDP.h"

#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

#define COMEHERE "COME HERE TO HAVE FUN"
#define sizeParam 20


int receiveUDP = 1;

char * getIp(){
	int fd;
	struct if_nameindex *curif, *ifs;
	struct ifreq req;

	if((fd = socket(PF_INET, SOCK_DGRAM, 0)) != -1) {
		ifs = if_nameindex();
		if(ifs) {
			for(curif = ifs; curif && curif->if_name; curif++) {
				strncpy(req.ifr_name, curif->if_name, IFNAMSIZ);
				req.ifr_name[IFNAMSIZ] = 0;
				if (ioctl(fd, SIOCGIFADDR, &req) < 0)
					perror("ioctl");
				else{
					if(strstr(curif->if_name,"eno")){
						return inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr);
					}

				}		
			}
		}
	}
	return "";
}

char * messageRetour(int nbJoueur){
	char buffer[2];
	sprintf(buffer, "%d", nbJoueur);

	getIp();

	char * come = malloc(sizeof(COMEHERE)+sizeParam+1);
	
	char * param = malloc(sizeof(char)*sizeParam);
	param = strcat(param,"{");
	param = strcat(param,buffer);
	param = strcat(param,"}");

	strcpy(come,COMEHERE);

	strcat(come , " - ");
	strcat(come, getIp());

	strcat(come,param);

	come[sizeParam] = '\0';

	return come;
}

char * verificationPartie(){
	int nbJoueur = 5;
	return messageRetour(nbJoueur);
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
    
    return threadServeur;
}
