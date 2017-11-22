#ifndef NETWORK_TOOLBOX
#define NETWORK_TOOLBOX

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>

struct client{
	char host[15];
	int port;
};


/*#####
UDP
######*/


int socket_UDP();
void close_UDP(int fd);
void send_UDP(int sock, char* host, int port, char* msg);
void UDP_bind_server(int sock, int port);
struct client recv_UDP(int sock, int port);

/*#####
TCP
######*/

int socket_TCP();
int wait_connection_TCP(int sock);
void close_TCP(int fd);
void TCP_bind_server(int sock, int port);
char * receive_data_TCP(int sock);
void handler_tcp(int arg);
void send_data_TCP(int sock, char* msg);
void connect_TCP(int sock, char *host, int port);

#endif
