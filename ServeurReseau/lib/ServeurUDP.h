#ifndef SERVER_UDP
#define SERVER_UDP

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include "./Network_Toolbox.h"

char * verificationPartie();
void sendBackBroadcast(struct client c);

void * threadServeurUDP(void * arg);
pthread_t startServeurUDP();

#endif
