#include "../lib/ServeurTCPClient.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCPClient = 1;
int socketGeneral;

plateau p;

void init_plateau_test(){
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	demander_mise(&p, 0, 10);
}

char * jsonTest(){
	char * json = plateau_to_json(&p);
	return json;
}

char * generationTaille(char * json){
	int size = strlen(json);
	char * buf = malloc(sizeof(char)*50);
	char str[12];

	strcpy(buf,"{ \"taille\" : ");

	sprintf(str, "\"%d\"", size);
	strcat(buf,str);

	strcat(buf,"}\n");

	return buf;
}

void sendPlateau(int ecoute){

	char * json = jsonTest();
	//json variable externe
	//recup plateau
	char * tailleJson = generationTaille(json);

	//idJoueur:"changeant"
	//dialogue:"mess"
	//quand créé joueur, renvoie id joueur 
	//dans thread une valeur id_joueur
	//génération json associer message

	//printf("%s\n",tailleJson);

	send_data_TCP(ecoute,tailleJson);
	send_data_TCP(ecoute,json);

}

void * threadServeurTCPClient(void * arg){
	int ecoute = socketGeneral;
	printf("%d\n",ecoute);

	init_plateau_test();
	//Connection
	char * msg = receive_data_TCP(ecoute);
	printf("init : %s\n",msg );
	sendPlateau(ecoute);


	while(receiveTCPClient){
		char * msg = receive_data_TCP(ecoute);
		printf("%s\n",msg );
		
		//ICI ON PARSE POUR VOIR CREATION DU TRHEAD DEDIE AU CLIENT
		//EN FONCTION RESULTAT, ENVOIE A TOUT LE MONDE

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0){
			free(msg);
			continue;
		}

		sendPlateau(ecoute);

		free(msg);
	}
	(void) arg;
	close_TCP(ecoute);
    pthread_exit(NULL);
}


pthread_t startServeurTCPClient(int socket){
	pthread_t threadServeur;
 	socketGeneral = socket;
	if(pthread_create(&threadServeur, NULL, threadServeurTCPClient, NULL) == -1) {
		perror("pthread_create_client()\n");
		exit(0);
    }
    return threadServeur;
}
