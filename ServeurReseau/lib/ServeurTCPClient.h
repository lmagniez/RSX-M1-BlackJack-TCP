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

#define SIZE_MSG 500

void * threadServeurTCPClient(void * arg);
pthread_t startServeurTCPClient(int socket);


char * get_json(int id_joueur, char *msg);
//Générer un JSON contenant la taille d'un autre JSON
char * generationTaille(char * json);
//Générer un JSON contenant un message
char * generationMsg(char * msg);
//Envoyer un message sur le socket
void sendMsg(int ecoute, char *msg);
//envoyer un plateau sur le socket
void sendPlateau(int ecoute, int id_joueur, char *msg);
void sendMsgAll(char *msg);
void sendPlateauAll(int id_joueur, char *msg);

#endif
