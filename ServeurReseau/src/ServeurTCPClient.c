#include "../lib/ServeurTCPClient.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
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
	char * buf = malloc(sizeof(char)*SIZE_MSG);
	
	strcpy(buf,"{ \"message\" : ");
	strcat(buf,msg);
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
	int nb;
	char *res = parseur_REST(msg, &p, &nb);
	printf("res >>%s\n",res);
	if (strstr(res,"CONNECT OK")==NULL){
		printf("pb co\n");
		//créé json
		pthread_exit(NULL);
	}

	char c = res[strlen("CONNECT OK ")];
	id_joueur = c - '0';
	free(res);
	sendPlateau(ecoute, id_joueur, "Le joueur vient de se connecter");

	while(receiveTCPClient){
		char * msg = receive_data_TCP(ecoute);

		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"")==0 || strcmp(msg,"@")==0){
			free(msg);
			continue;
		}

		int reinit = 0;
		//reinit détecte si tous les joueurs ont fini de jouer
		char *res_joueur = parseur_REST(msg, &p, &reinit);
		char *res_croupier;
		//si fin de tour
		if(reinit == 1){
			tour_croupier(&p);
			//on envoie le plateau avec que le croupier ai joué
			sendPlateau(ecoute, id_joueur, res_joueur);
			sleep(2);
			//récupère les lignes à renvoyer et réinitialise le jeu
			res_croupier = get_results(&p);
			//on envoie les étapes du croupier (sans mettre à jour le plateau)
			sendMsg(ecoute, id_joueur, msg);
			//attend que les joueurs voient le résultat avant de réinitialiser
			sleep(2);
			strcpy(res_joueur, "Réinitialisation des jeux");
			
		}
		
		if(res == NULL){
			continue;
		}else if (strstr("SPLIT KO", res_joueur)){
			printf("split\n");
			sendMsg(ecoute, id_joueur, "Vous ne pouvez pas splitter votre jeu!");
			continue;
		}

		//ENVOIE A TOUT LE MONDE
		//met à jour le plateau
		sendPlateau(ecoute, id_joueur, res_joueur);

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
