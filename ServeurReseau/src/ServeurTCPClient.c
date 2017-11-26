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
	rejoindre_partie(&p, 500, "127.000.1.2");
	rejoindre_partie(&p, 500, "127.000.1.3");
	rejoindre_partie(&p, 500, "127.000.1.4");
	rejoindre_partie(&p, 500, "127.000.1.5");
	quitter_partie(&p, 1);
	quitter_partie(&p, 3);
	rejoindre_partie(&p, 1000, "127.000.1.6");

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 1200);
	demander_mise(&p, 2, 200);
	demander_mise(&p, 4, 500);


	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,2);
	demander_tirer(&p,3);
	demander_tirer(&p,4);
	demander_tirer(&p,5);
	demander_tirer(&p,0);
	demander_tirer(&p,1);


	return plateau_to_json(&p);
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
	char * tailleJson = generationTaille(json);

	printf("%s\n",tailleJson);

	send_data_TCP(ecoute,tailleJson);	

	printf("coucou\n");

	send_data_TCP(ecoute,json);	

}

void * threadServeurTCPClient(void * arg){
	int ecoute = socketGeneral;
	printf("%d\n",ecoute);

	while(receiveTCPClient){
		char * msg = receive_data_TCP(ecoute);	

		//ICI ON PARSE POUR VOIR CREATION DU TRHEAD DEDIE AU CLIENT 

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
