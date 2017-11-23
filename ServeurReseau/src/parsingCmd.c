#include "../lib/parsingCmd.h"
#include "../../ServeurBlackJack/lib/plateau.h"

#define CREDIT 500
/*
GET action/connect
host: 

POST /action/mise
host: 
200
*/
	/*
	public String get = "GET ";
	public String post = "POST ";
	*/
	
	/*
	char* mise = "/action/mise";
	char* tirer = "/action/tirer";
	char* split = "/action/split";

	char* leave = "/action/leave";
	char* doubler = "/action/doubler";
	char* rester = "/action/rester";
	
	char* connect = "action/connect";
	*/
	
	void parseur_REST(char *cmd, plateau *p){
		char adr[15];
		int is_post = 0;
		int is_get = 0;
		int is_mise = 0;
		int is_tirer = 0;
		int is_split = 0;
		int is_leave = 0;
		int is_doubler = 0;
		int is_rester = 0;
		int is_connect = 0;
		int cpt_cmd = 0;
		
		int id_joueur = -1;
		int mise = 0;
		
		printf("\nCMD -> %s\n",cmd);
		
		char *cmd_tmp = cmd;
		
		//GET/POST
		cmd_tmp = strstr(cmd, POST);
		if(cmd_tmp != NULL){
			is_post = 1;
			cmd = cmd_tmp+strlen(POST)+1;
		}
		cmd_tmp = strstr(cmd, GET);
		if(cmd_tmp != NULL){
			is_get = 1;
			cmd = cmd_tmp+strlen(GET)+1;
		}
		if((!is_post&&!is_get)||(is_post&&is_get)){
			printf("erreur parsing POST GET!!\n");
			return;
		}
		
		//printf("cmd a partir de maintenant \n -> %s\n", cmd);
		
		//MISE, TIRER, SPLIT, DOUBLER, RESTER, CONNECT
		cmd_tmp = strstr(cmd, MISE);
		if(cmd_tmp != NULL){
			is_mise = 1;
			cmd = cmd_tmp+strlen(MISE)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, TIRER);
		if(cmd_tmp != NULL){
			is_tirer = 1;
			cmd = cmd_tmp+strlen(TIRER)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, SPLIT);
		if(cmd_tmp != NULL){
			is_split = 1;
			cmd = cmd_tmp+strlen(SPLIT)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, LEAVE);
		if(cmd_tmp != NULL){
			is_leave = 1;
			cmd = cmd_tmp+strlen(LEAVE)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, DOUBLER);
		if(cmd_tmp != NULL){
			is_doubler = 1;
			cmd = cmd_tmp+strlen(DOUBLER)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, RESTER);
		if(cmd_tmp != NULL){
			is_rester = 1;
			cmd = cmd_tmp+strlen(RESTER)+1;
			cpt_cmd++;
		}
		cmd_tmp = strstr(cmd, CONNECT);
		if(cmd_tmp != NULL){
			is_connect = 1;
			cmd = cmd_tmp+strlen(CONNECT)+1;
			cpt_cmd++;
		}
		if(cpt_cmd != 1){
			perror("erreur parsing commande!!\n");
			return;
		}
		
		//passer le host:
		cmd_tmp = strstr(cmd, "host: ");
		if(cmd_tmp != NULL){
			cmd = cmd_tmp+strlen("host: ");
			cpt_cmd++;
		}
		
		//get adresse
		adr[0] = '\0';
		int cpt = 0;
		while(cmd[cpt]!='\n'&&cmd[cpt]!='\0'){
			adr[cpt] = cmd[cpt];
			cpt++;
		}
		adr[cpt++]='\0';
		printf("adr -> %s\n", adr);
		
		if(is_connect){
			printf("connect!\n");
			id_joueur = rejoindre_partie(p, CREDIT, adr);
			printf("connecté en tant que joueur %d!\n",id_joueur);
			
			return;
		}
		
		//get id_joueur
		id_joueur = get_id_from_adresse(p, adr);
		if(id_joueur < 0){
			perror("l'adresse ne correspond pas au joueur!\n");
			return;
		}
		
		cmd = cmd + cpt;
		//printf("cmd a partir de maintenant \n -> %s\n", cmd);
		
		
		//mise d'un joueur (POST)
		if(is_mise){
			printf("mise!\n");
			if(!is_post){
				perror("erreur! Mise doit etre POST!\n");
				return;
			}
			mise = atoi(cmd);
			if(mise <= 0){
				perror("mise incorrecte !\n");
				return;
			}
			if(demander_mise(p, id_joueur, mise) == -1){
				printf("Ne peux pas miser!\n");
				return;
			}
			
			printf("mise -> %d\n",mise);
			return;
		}
		
		//tirage d'une carte (GET)
		else if(is_tirer){
			printf("tirer!\n");
			if(!is_get){
				perror("erreur! Tirer doit etre GET!\n");
				return;
			}
			if(demander_tirer(p, id_joueur) == -1){
				printf("Ne peux pas tirer\n");
				return;
			}
		}
		
		//split jeu (GET)
		else if(is_split){
			printf("split!\n");
			if(!is_get){
				perror("erreur! Split doit etre GET!\n");
				return;
			}
			if(demander_split(p, id_joueur) == -1){
				printf("Ne peux pas split\n");
				return;
			}
		}
		
		//leave jeu (GET)
		else if(is_leave){
			printf("leave!\n");
			if(!is_get){
				perror("erreur! Leave doit etre GET!\n");
				return;
			}
			if(demander_abandon(p, id_joueur) == -1){
				printf("Ne peux pas leave\n");
				return;
			}
		}
		
		//doubler jeu (GET)
		else if(is_doubler){
			printf("doubler!\n");
			if(!is_get){
				perror("erreur! Doubler doit etre GET!\n");
				return;
			}
			if(demander_double(p, id_joueur) == -1){
				printf("Ne peux pas doubler\n");
				return;
			}
		}
		
		//rester jeu (GET)
		else if(is_rester){
			printf("rester!\n");
			if(!is_get){
				perror("erreur! Rester doit etre GET!\n");
				return;
			}
			if(demander_rester(p, id_joueur) == -1){
				printf("Ne peux pas rester\n");
				return;
			}
		}
		
	}
