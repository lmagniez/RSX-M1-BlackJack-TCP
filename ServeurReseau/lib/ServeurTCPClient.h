#ifndef SERVER_TCP_CLIENT
#define SERVER_TCP_CLIENT

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
#include "./parsingCmd.h"


void * threadServeurTCPClient(void * arg);
pthread_t startServeurTCPClient(int socket);

#endif
