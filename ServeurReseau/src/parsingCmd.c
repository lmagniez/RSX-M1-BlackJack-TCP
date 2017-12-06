#include "../lib/parsingCmd.h"
#include "../../ServeurBlackJack/lib/plateau.h"


	char *parseur_REST(char *cmd, plateau *p, int *reinit, int num_socket, int id_joueur){
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

		int id_co = -1;
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
			return NULL;
		}

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
			return NULL;
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
			id_co = rejoindre_partie(p, CREDIT, adr, num_socket);
			printf("connecté en tant que joueur %d!\n",id_co);

			char *str=malloc(sizeof(char)*15);
			sprintf(str, "CONNECT OK %d", id_co);
			return str;
		}

		cmd = cmd + cpt;

		//mise d'un joueur (POST)
		if(is_mise){
			printf("mise!\n");

			if(!is_post){
				perror("erreur! Mise doit etre POST!\n");
				return NULL;
			}
			mise = atoi(cmd);
			if(mise <= 0){
				perror("mise incorrecte !\n");
				return NULL;
			}
			if(demander_mise(p, id_joueur, mise) == -1){
				printf("Ne peux pas miser!\n");
				return NULL;
			}

			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d a misé %d crédits ", id_joueur, mise);
			return res;
		}

		//tirage d'une carte (GET)
		else if(is_tirer){
			printf("tirer!\n");
			if(!is_get){
				perror("erreur! Tirer doit etre GET!\n");
				return NULL;
			}
			int fin_tour = demander_tirer(p, id_joueur);
			if(fin_tour == -1){
				printf("Ne peux pas tirer\n");
				return NULL;
			}
			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d a tiré une carte ", id_joueur);
			if(fin_tour == 1){
				*reinit = 1;
			}
			return res;
		}

		//split jeu (GET)
		else if(is_split){
			printf("split!\n");
			if(!is_get){
				perror("erreur! Split doit etre GET!\n");
				return NULL;
			}
			if(demander_split(p, id_joueur) == -1){
				printf("Ne peux pas split\n");
				return "SPLIT KO";
			}
			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d a split son jeu ", id_joueur);
			return res;
		}

		//leave jeu (GET)
		else if(is_leave){
			printf("leave!\n");
			if(!is_get){
				perror("erreur! Leave doit etre GET!\n");
				return NULL;
			}
			int fin_tour = demander_abandon(p, id_joueur);
			if(fin_tour == -1){
				printf("Ne peux pas leave\n");
				return NULL;
			}
			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d a abandonné son jeu courant ", id_joueur);
			if(fin_tour == 1){
				*reinit = 1;
			}
			return res;
		}

		//doubler jeu (GET)
		else if(is_doubler){
			printf("doubler!\n");
			if(!is_get){
				perror("erreur! Doubler doit etre GET!\n");
				return NULL;
			}
			int fin_tour = demander_double(p, id_joueur);
			if(fin_tour == -1){
				printf("Ne peux pas doubler\n");
				return "DOUBLER KO";
			}
			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d a doublé sa mise et tire une carte ", id_joueur);
			if(fin_tour == 1){
				*reinit = 1;
			}
			return res;

		}

		//rester jeu (GET)
		else if(is_rester){
			printf("rester!\n");
			if(!is_get){
				perror("erreur! Rester doit etre GET!\n");
				return NULL;
			}
			int fin_tour = demander_rester(p, id_joueur);
			if(fin_tour == -1){
				printf("Ne peux pas rester\n");
				return NULL;
			}

			//char *dialogue = malloc(sizeof(char)*DIALOGUE_SIZE);
			char *res = malloc(sizeof(char)*CMD_SIZE);
			sprintf(res, "Le joueur %d est satisfait de son jeu courant ", id_joueur);
			//strcpy(dialogue, res);
			if(fin_tour == 1){
				/*char *result_tour = tour_croupier(p);
				strcat(dialogue,result_tour);
				free(result_tour);*/
				*reinit = 1;
			}
			//free(res);
			//return dialogue;
			return res;

		}
		return NULL;

	}
