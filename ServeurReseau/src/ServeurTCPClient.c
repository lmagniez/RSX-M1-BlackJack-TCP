#include <semaphore.h>
#include "../lib/ServeurTCPClient.h"
#include "../../ServeurBlackJack/lib/plateau.h"
#define MAX_LENGTH 1024
#define BUFF_SIZE 20
#define MAX_BACKLOG 9

int receiveTCPClient = 1;
int socketGeneral;

sem_t mutexConnection;
sem_t mutexReseau;

plateau p;

//Retourne le json du plateau avec l'id du joueur actuel et le message associé
char * get_json(int id_joueur, char *msg){
	char * json = plateau_to_json(&p, id_joueur, msg);
	return json;
}

char * add_enete_json(char * message){
	char str[12];
	char * entete = malloc(sizeof(char)*strlen(message)+301);
	strcpy(entete,"HTTP/1.1\n");
	strcat(entete,"Contente-Length: ");
	sprintf(str, "\"%d\"\n", strlen(message)+1);
	strcat(entete,str);
	strcat(entete,message);
	return entete;
}

//Générer un JSON contenant un message
char * generationMsg(char * msg){
	char * buf = malloc(sizeof(char)*SIZE_MSG);
	
	strcpy(buf,"{ \"message\" : ");
	strcat(buf,msg);
	strcat(buf,"}\n");

	return buf;
}

//Envoyer un message sur le socket
void sendMsg(int ecoute, char *msg){
	char * json = generationMsg(msg);
	char * jsonEntete = add_enete_json(json);
	send_data_TCP(ecoute,jsonEntete);
}

//envoyer un plateau sur le socket
void sendPlateau(int ecoute, int id_joueur, char *msg){
	char * json = get_json(id_joueur, msg);
	char * jsonEntete = add_enete_json(json);
	send_data_TCP(ecoute,jsonEntete);
}

void sendMsgAll(char *msg){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p.joueurs[i].e != OFF){
			sendMsg(p.joueurs[i].num_socket, msg);
		}
	}
}

void sendMsgAllLessSize(char *msg){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p.joueurs[i].e != OFF){
			sendMsg(p.joueurs[i].num_socket, msg);
		}
	}
}

void sendPlateauAll(int id_joueur, char *msg){
	(void) id_joueur;
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p.joueurs[i].e != OFF){
			sendPlateau(p.joueurs[i].num_socket, p.joueurs[i].id_joueur, msg);
		}
	}
}


//thread d'un client
void * threadServeurTCPClient(void * arg){
	int ecoute = socketGeneral;
	int id_joueur; 
	int nb;
	int reception = 1;

	//Connection
	char * msg = receive_data_TCP(ecoute);
	sem_wait(&mutexConnection);
	
	char *res = parseur_REST(msg, &p, &nb, ecoute, id_joueur);

	if (strstr(res,"CONNECT OK")==NULL){
		sendMsg(ecoute, "CONNECT KO");
		pthread_exit(NULL);
	}

	char c = res[strlen("CONNECT OK ")];
	id_joueur = c - '0';
	sem_wait(&mutexReseau);
	
	printf("ID JOUEUR CONNECTE : %d\n", id_joueur);
	sendPlateauAll(id_joueur, "Le joueur vient de se connecter");
	
	sem_post(&mutexReseau);
	sem_post(&mutexConnection);
	
	while(reception){
		char * msg = receive_data_TCP(ecoute);
		sem_wait(&mutexReseau);
		// EN CAS DE DECONNECTION DU CLIENT le socket est close cote recv et le message est vide
		if(strcmp(msg,"DECO")==0){
			reception = 0;	
			continue;
		}else if(strcmp(msg,"")==0){
			//free(msg);
			sem_post(&mutexReseau);	
			continue;
		}

		int reinit = 0;

		char *res_joueur = parseur_REST(msg, &p, &reinit, ecoute, id_joueur);

		//si fin de tour
		if(reinit == 1){
			tour_croupier(&p);
			//on envoie le plateau avec que le croupier ai joué
			sendPlateauAll(id_joueur, res_joueur);

			sleep(3);

			//récupère les lignes à renvoyer et réinitialise le jeu
			char *res_croupier = get_results(&p);

			//on envoie les étapes du croupier (sans mettre à jour le plateau)
			sendMsgAllLessSize(res_croupier);

			//attend que les joueurs voient le résultat avant de réinitialiser
			sleep(3);
			strcpy(res_joueur, "Réinitialisation des jeux");
			sendPlateauAll(id_joueur, res_joueur);
			sem_post(&mutexReseau);	
			continue;		
		}
		
		if(res_joueur == NULL){
			sem_post(&mutexReseau);	
			continue;
		}else if (strstr("SPLIT KO", res_joueur)){
			printf("split\n");
			sendMsg(ecoute, "Vous ne pouvez pas splitter votre jeu!");
			sem_post(&mutexReseau);	
			continue;
		}
		else if (strstr("DOUBLER KO", res_joueur)){
			printf("doubler\n");
			sendMsg(ecoute, "Vous ne pouvez pas doubler votre jeu!");
			sem_post(&mutexReseau);	
			continue;
		}

		//ENVOIE A TOUT LE MONDE
		//met à jour le plateau
		sendPlateauAll(id_joueur, res_joueur);
		sem_post(&mutexReseau);

	}
	quitter_partie(&p, id_joueur);
	
	sendPlateauAll(id_joueur, "Un joueur s'est deconnecté");
	sem_post(&mutexReseau);
	(void) arg;
	printf("Joueur %d deconnecte\n",id_joueur);
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
