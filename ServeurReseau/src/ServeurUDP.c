#include "../lib/Network_Toolbox.h"
#include "../lib/ServeurUDP.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

#define COMEHERE "COME HERE TO HAVE FUN"

void sendBackBroadcast(struct client c){
	int sock = socket_UDP();
	send_UDP(sock,c.host,c.port,COMEHERE);
}

void startServeurUDP(){
int udp_sock = socket_UDP();
	int port = atoi("8080");
	UDP_bind_server(udp_sock,port);
	for(;;){
		struct client client = recv_UDP(udp_sock,port);
		sendBackBroadcast(client);	
	}
	close_UDP(udp_sock);

}
