#include "../lib/ServeurTCPClient.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCPClient = 1;
int socketGeneral;

char * jsonTest(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 1000, "127.000.1.2");
	rejoindre_partie(&p, 600, "127.000.1.3");
	rejoindre_partie(&p, 300, "127.000.1.4");
	rejoindre_partie(&p, 2000, "127.000.1.5");
	rejoindre_partie(&p, 500, "127.000.1.6");
	rejoindre_partie(&p, 500, "127.000.1.7");

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 400);
	demander_mise(&p, 2, 400);
	demander_mise(&p, 3, 100);
	demander_mise(&p, 4, 200);
	demander_mise(&p, 5, 200);
	demander_mise(&p, 6, 200);



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

	while(receiveTCPClient){
		char * msg = receive_data_TCP(ecoute);

		//ICI ON PARSE POUR VOIR CREATION DU TRHEAD DEDIE AU CLIENT
		//EN FONCTION RESULTAT, ENVOIE A TOUT LE MONDE

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0){
			free(msg);
			//GERER DECONNECTION CLIENT SERVEUR ICI
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
