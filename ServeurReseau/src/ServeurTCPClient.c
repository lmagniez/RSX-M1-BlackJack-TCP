#include "../lib/ServeurTCPClient.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCPClient = 1;
int socketGeneral;

plateau p;

/*
void init_plateau_test(){
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	demander_mise(&p, 0, 10);
}
*/
char * get_json(int id_joueur, char *msg){
	
	char * json = plateau_to_json(&p, id_joueur, msg);
	
	return json;
}

char * generationTaille(char * json){
	int size = strlen(json)+1;
	char * buf = malloc(sizeof(char)*SIZE_MSG);
	char str[12];

	strcpy(buf,"{ \"taille\" : ");
	sprintf(str, "\"%d\"", size);
	strcat(buf,str);
	strcat(buf,"}\n");

	return buf;
}

char * generationMsg(char * msg){
	int size = strlen(msg)+1;
	char * buf = malloc(sizeof(char)*SIZE_MSG);
	char str[12];
	
	printf("strlen !! %d \n",strlen(msg));

	strcpy(buf,"{ \"message\" : ");
	sprintf(str, "\"%s\"", msg);
	strcat(buf,str);
	strcat(buf,"}\n");

	return buf;
}

void sendMsg(int ecoute, int id_joueur, char *msg){

	char * json = generationMsg(msg);
	char * tailleJson = generationTaille(json);

	send_data_TCP(ecoute,tailleJson);
	send_data_TCP(ecoute,json);

}

void sendPlateau(int ecoute, int id_joueur, char *msg){

	char * json = get_json(id_joueur, msg);
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
	int id_joueur; 
	printf("%d\n",ecoute);

	//init_plateau_test();
	//Connection
	char * msg = receive_data_TCP(ecoute);
	//remplace par parseur check co
	printf("init : %s\n",msg );

	// if !co
	// pthread_exit(NULL);
	char *res = parseur_REST(msg, &p);
	printf("res >>%s\n",res);
	if (strstr(res,"CONNECT OK")==NULL){
		printf("pb co\n");
		//créé json
		pthread_exit(NULL);
	}
	printf(">> ok\n");
	char c = res[strlen("CONNECT OK ")];
	id_joueur = c - '0';
	
	free(res);
	printf(">> ok2\n");
	
	//rejoindre_partie(&p, MISE_VALUE, "127.000.1.1");
	sendPlateau(ecoute, id_joueur, "Le joueur vient de se connecter\n");

	printf(">> ok3\n");

	while(receiveTCPClient){
		char * msg = receive_data_TCP(ecoute);
		printf("%s\n",msg );

		//ICI ON PARSE POUR VOIR CREATION DU TRHEAD DEDIE AU CLIENT
		//EN FONCTION RESULTAT, ENVOIE A TOUT LE MONDE
		if (strstr("SPLIT KO", res)){
			sendMsg(ecoute, id_joueur, "Vous ne pouvez pas splitter votre jeu!\n");
		}

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0 || strcmp(msg,"@")==0){
			free(msg);
			continue;
		}
		char *res = parseur_REST(msg, &p);
		sendPlateau(ecoute, id_joueur, res);

		free(msg);
		free(res);
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
