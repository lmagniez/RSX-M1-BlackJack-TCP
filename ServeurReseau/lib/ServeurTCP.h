#ifndef SERVER_TCP
#define SERVER_TCP

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
#include "./ServeurTCPClient.h"

void * threadServeurTCPConnection(void * arg);
pthread_t startServeurTCPConnection();

#endif
