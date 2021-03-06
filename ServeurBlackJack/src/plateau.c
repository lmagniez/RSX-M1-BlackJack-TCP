
#include "../lib/plateau.h"

void init_plateau(plateau *p){
	generer_tas(&(p->pioche));
	generer_jeu(&(p->jeu_croupier));
	p->joueurs = malloc(sizeof(joueur)*NB_JOUEUR_MAX);
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		generer_joueur(&(p->joueurs[i]),i);
	}
	p->nb_joueur = 0;
	p->tour_id_joueur = -1;
	p->tour_id_jeu = -1;
	p->tour_started = 0;
}

void reinit_plateau(plateau *p){
	p->nb_joueur = 0;
	p->tour_id_joueur = -1;
	p->tour_id_jeu = -1;
	p->tour_started = 0;
}


void afficher_plateau(plateau *p){
	printf("===Plateau:===\n");
	printf("--Tour-- id_joueur: %d id_jeu: %d started: %d\n",p->tour_id_joueur, p->tour_id_jeu, p->tour_started);
	printf("Croupier: \n");
	afficher_jeu(&(p->jeu_croupier));
	printf("Joueurs: \n");
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		printf("\n");
		afficher_joueur(&(p->joueurs[i]));
	}
	printf("JSON: \n%s\n",plateau_to_json(p, 0, "null"));
}


//id si le joueur peut rejoindre
//-1 si plein
int rejoindre_partie(plateau *p, int credit, char *adresse, int num_socket){
	if(p->nb_joueur == NB_JOUEUR_MAX){
		return -1;
	}
	else {
		for(int i=0; i<NB_JOUEUR_MAX; i++){
			if(p->joueurs[i].e==OFF){
				start_joueur(&(p->joueurs[i]),credit, adresse, p->tour_started, num_socket);
				p->nb_joueur++;
				int found = 0;
				for(int j=0; j<NB_JOUEUR_MAX; j++){
					if(p->joueurs[j].e == BETTING){
						found = 1;
					}
				}
				if(!found){
					p->joueurs[i].e = BETTING;
				}


				/*if(p->nb_joueur==1){
					p->tour_id_joueur = i;
					p->tour_id_jeu = 0;
				}*/

				return i;
			}
		}
	}
	return -1;
}

//id si le joueur a quitté
//-1 si existe pas
int quitter_partie(plateau *p, int id_joueur){
	if(p->joueurs[id_joueur].e==OFF){
		return -1;
	}
	stop_joueur(&(p->joueurs[id_joueur]));
	p->nb_joueur--;


	int i = id_joueur;
	if(p->nb_joueur==0){
		reinit_plateau(p);
		reinit_jeu(&(p->jeu_croupier));
	}
	else{
		if(p->tour_id_joueur==id_joueur){
			while(p->joueurs[i].e==OFF){
				i=(i+1)%(NB_JOUEUR_MAX-1);
			}
			p->tour_id_joueur = i;
			p->tour_id_jeu = 0;
		}
	}

	return 1;
}

//distribue 2 cartes à chaque joueurs, 1 au croupier
void init_tour(plateau *p){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e == PLAYING){
			carte c = get_next_carte(&(p->pioche));
			add_carte(&(p->joueurs[i].jeux[0]),c);
			c = get_next_carte(&(p->pioche));
			add_carte(&(p->joueurs[i].jeux[0]),c);
		}
	}
	carte c = get_next_carte(&(p->pioche));
	add_carte(&(p->jeu_croupier),c);

	p->tour_started = 1;
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e==PLAYING){
			p->tour_id_joueur = i;
			p->tour_id_jeu = 0;
			return;
		}
	}

}


//si un joueur n'a pas encore misé, faux
int tour_est_demarre(plateau *p){
	if(p->nb_joueur == 0){
		return 0;
	}
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e == BETTING)
			return 0;
	}
	return 1;
}


//1 si nouveau tour (lancer le croupier)
int change_tour(plateau *p){

	//si plusieurs jeux actifs, accede au prochain jeu du joueur
	int old_tour_id_joueur = p->tour_id_joueur;
	int old_tour_id_jeu = p->tour_id_jeu;

	if(p->tour_id_jeu < p->joueurs[p->tour_id_joueur].nb_jeux-1){
		//tant que le prochain jeu est PERDU
		p->tour_id_jeu = (p->tour_id_jeu + 1)%p->joueurs[p->tour_id_joueur].nb_jeux;
		while(p->joueurs[p->tour_id_joueur].jeux[p->tour_id_jeu].e_jeu==PERDU
		||p->joueurs[p->tour_id_joueur].jeux[p->tour_id_jeu].e_jeu==SATISFAIT){
			if(p->tour_id_jeu==old_tour_id_jeu){
				break;
			}
			p->tour_id_jeu = (p->tour_id_jeu + 1)%p->joueurs[p->tour_id_joueur].nb_jeux;
		}
		//cherche pas de joueurs si encore des jeux
		if(p->tour_id_jeu>old_tour_id_jeu)
			return 0;
	}

	//chercher le prochain joueur
	p->tour_id_joueur= (p->tour_id_joueur+1)%NB_JOUEUR_MAX;
	while(p->joueurs[p->tour_id_joueur].e!=PLAYING){
		if(p->tour_id_joueur == old_tour_id_joueur){
			printf("PLUS DE JOUEURS !!! \n");
			p->tour_id_joueur = -1;
			p->tour_id_jeu = -1;
			//tour_croupier(p);
			return 1;
		}
		p->tour_id_joueur= (p->tour_id_joueur+1)%NB_JOUEUR_MAX;
	}
	p->tour_id_jeu = 0;

	return 0;
}



void destroy_plateau(plateau *p){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		destroy_joueur(&(p->joueurs[i]));
	}
}

void tour_croupier(plateau *p){
	if(p->tour_id_jeu!=-1||p->tour_id_joueur!=-1){
		perror("IL Y A ENCORE DES JOUEURS QUI DOIVENT JOUER\n");
		return;
	}

	while (p->jeu_croupier.valeur<17){
		printf("LE CROUPIER TIRE UNE CARTE\n");
		carte c = get_next_carte(&(p->pioche));
		add_carte_croupier(&(p->jeu_croupier), c);
	}
	if(p->jeu_croupier.valeur>21){
		printf("LE CROUPIER PERD LE JEU\n");
		p->jeu_croupier.e_jeu=PERDU;
	}
	else if(p->jeu_croupier.valeur == 21){
		printf("LE CROUPIER A UN BLACKJACK!\n");
		p->jeu_croupier.e_jeu=SATISFAIT;
	}
	else{
		printf("LE CROUPIER EST SATISFAIT DE SON JEU\n");
		p->jeu_croupier.e_jeu=SATISFAIT;
	}

}

char* get_results(plateau *p){

	if(p->jeu_croupier.e_jeu!=PERDU&&p->jeu_croupier.e_jeu!=SATISFAIT){
		perror("LE CROUPIER N'A PAS FINI DE JOUER!\n");
		return NULL;
	}
	char *msg = malloc(sizeof(char)*MAX_MSG);
	strcpy(msg,"Fin du tour;");

	for(int i=0; i<NB_JOUEUR_MAX; i++){

		printf("joueur %d\n",i);
		//que les joueurs qui ont joués
		if(p->joueurs[i].e==FINISHED){
			int mise_par_jeu = p->joueurs[i].mise_totale/p->joueurs[i].nb_jeux;
			for(int j=0; j<p->joueurs[i].nb_jeux; j++){
				printf("jeu %d\n",j);
				//joueur gagne: Gagne la mise *1.5 (Blackjack: 2)
				if(p->joueurs[i].jeux[j].e_jeu==SATISFAIT&&p->jeu_croupier.e_jeu==PERDU){
					if(has_blackjack(&(p->joueurs[i].jeux[j]))){
						char str[100];
						sprintf(str,"BLACKJACK au joueur %d! Gain -> %d;", i, mise_par_jeu*2);
						strcat(msg,str);
						printf("BLACKJACK au joueur %d! Gain -> %d;", i, mise_par_jeu*2);
						p->joueurs[i].credit += mise_par_jeu * 2;
					}
					else{
						char str[100];
						sprintf(str,"Victoire du joueur %d! Gain -> %f;", i, mise_par_jeu*1.5);
						strcat(msg,str);
						printf("Victoire du joueur %d! Gain -> %f;", i, mise_par_jeu*1.5);
						p->joueurs[i].credit += mise_par_jeu * 1.5;
					}
				}
				//test qui a la plus petite valeur + Blackjack
				if(p->joueurs[i].jeux[j].e_jeu==SATISFAIT&&p->jeu_croupier.e_jeu==SATISFAIT){
					printf("SATISFAITFAIT\n");
					if(has_blackjack(&(p->jeu_croupier))){
						char str[100];
						sprintf(str,"BLACKJACK du croupier! Perte pour le joueur %d (%d$);", i, mise_par_jeu);
						strcat(msg,str);
						printf("BLACKJACK du croupier! Perte pour le joueur %d (%d$);", i, mise_par_jeu);
					}
					else if(has_blackjack(&(p->joueurs[i].jeux[j]))){
						char str[100];
						sprintf(str,"BLACKJACK du joueur %d (jeu %d)! Gain -> %d$;", i, j, (mise_par_jeu*2));
						strcat(msg,str);
						printf("BLACKJACK du joueur %d (jeu %d)! Gain -> %d$;", i, j, (mise_par_jeu*2));
						p->joueurs[i].credit += mise_par_jeu * 2;
					}
					else if(p->joueurs[i].jeux[j].valeur > p->jeu_croupier.valeur){
						char str[100];
						sprintf(str,"Victoire du joueur %d (jeu %d)! Gain -> %f$;", i, j, (mise_par_jeu*1.5));
						strcat(msg,str);
						printf("Victoire du joueur %d (jeu %d)! Gain -> %f$;", i, j, (mise_par_jeu*1.5));
						p->joueurs[i].credit += mise_par_jeu * 1.5;
					}
					else{
						char str[100];
						sprintf(str,"Victoire du croupier! Perte pour le joueur %d (%d$);", i, mise_par_jeu);
						strcat(msg,str);
						printf("Victoire du croupier! Perte pour le joueur %d (%d$);", i, mise_par_jeu);
					}

				}
				if(p->joueurs[i].jeux[j].e_jeu==PERDU&&p->jeu_croupier.e_jeu==SATISFAIT){
					char str[100];
					sprintf(str,"Victoire du croupier! Perte pour le joueur  %d (%d$);", i, mise_par_jeu);
					strcat(msg,str);

				}
				reinit_jeu(&(p->joueurs[i].jeux[j]));
				//init_tour(p);
			}

			p->joueurs[i].mise_actuelle = 0;
			p->joueurs[i].mise_totale = 0;
			if(p->joueurs[i].credit <= 0){
				char str[50];
				sprintf(str,"JOUEUR %d N'A PLUS DE CREDIT! HORS-JEU;",i);
				strcat(msg,str);
				//printf("JOUEUR %d N'A PLUS DE CREDIT! HORS-JEU \n",i);
				p->joueurs[i].e = LOSE;
			}
			else{
				p->joueurs[i].e = BETTING;
			}
			p->joueurs[i].nb_jeux = 1;
		}
	}
	reinit_jeu(&(p->jeu_croupier));
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e == WAITING){
			p->joueurs[i].e = BETTING;
		}
	}

	return msg;
}

// Le joueur doit avoir deux paires pour splitter
int demander_split(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur&&
		p->joueurs[id_joueur].e==PLAYING){
		int id_jeu;
		if((id_jeu=splitter_jeu(&(p->joueurs[id_joueur])))!=-1){;
			printf("JOUEUR %d SPLITTE SON JEU %d \n",id_joueur, p->tour_id_jeu);
			//int fin_tour = change_tour(p);
			//return fin_tour;
			return 0;
		}
	}
	return -1;
}

// Le joueur doit avoir une mise > 0 pour tirer
int demander_tirer(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur
		&&p->joueurs[id_joueur].mise_totale>0
		&&p->joueurs[id_joueur].e==PLAYING){
		carte c = get_next_carte(&(p->pioche));
		if(add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c)==PERDU){

			printf("JOUEUR %d PERD SON JEU %d \n",id_joueur, p->tour_id_jeu);
			check_joueur_actif(p, id_joueur);

			int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);
			p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
				- montant_perdu;
		}

		if(p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu!=JOUE){
			int fin_tour = change_tour(p);
			return fin_tour;

		}
		return 0;
	}


	return -1;
}

// passe le jeu a satisfait verifie si le joueur a fini de jouer ses paquets
int demander_rester(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur
		&&p->joueurs[id_joueur].e==PLAYING){
		p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;

		printf("JOUEUR %d EST SATISFAIT DE SON JEU %d \n",id_joueur, p->tour_id_jeu);
		check_joueur_actif(p, id_joueur);

		int fin_tour = change_tour(p);
		if(fin_tour)
			return 1;
		else{
			return 0;
		}
	}
	return -1;
}

// double la mise si possible, passe en satisfait le jeu et vérifie si le joueur a fini de jouer tous ses paquets
int demander_double(plateau *p, int id_joueur){

	if(p->tour_id_joueur==id_joueur
		&&p->joueurs[id_joueur].e==PLAYING){
		if(p->joueurs[id_joueur].credit > p->joueurs[id_joueur].mise_totale){
			int mise = p->joueurs[id_joueur].mise_totale;
			p->joueurs[id_joueur].mise_actuelle += mise;
			p->joueurs[id_joueur].mise_totale += mise;
			p->joueurs[id_joueur].credit += -mise;
			carte c = get_next_carte(&(p->pioche));

			printf("JOUEUR %d EST SATISFAIT DE SON JEU ET DOUBLE %d \n",id_joueur, p->tour_id_jeu);
			if(add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c)==PERDU){

				printf("MAIS JOUEUR %d PERD SON JEU %d \n",id_joueur, p->tour_id_jeu);

				int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);
				p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
					- montant_perdu;
			}
			else{
				p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;
			}

			check_joueur_actif(p, id_joueur);

			int fin_tour = change_tour(p);
			return fin_tour;

		}
	}
	return -1;
}


//abandon d'un paquet de carte
int demander_abandon(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur){
		int num_jeu = p->tour_id_jeu;

		printf("JOUEUR %d ABANDONNE SON JEU %d \n",id_joueur, p->tour_id_jeu);
		p->joueurs[id_joueur].jeux[num_jeu].e_jeu = PERDU;
		check_joueur_actif(p, id_joueur);

		int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);

		p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
			- montant_perdu;
		//le joueur ne perd que la moitié de la somme
		p->joueurs[id_joueur].credit += montant_perdu / 2;


		int fin_tour = change_tour(p);
		return fin_tour;

	}
	return -1;
}

//en debut de tour
//place la mise
int demander_mise(plateau *p, int id_joueur, int mise){
	printf("demande mise idj: %d mise: %d \n", id_joueur, mise);
	if(p->joueurs[id_joueur].e==BETTING && p->joueurs[id_joueur].credit >= mise){
		p->joueurs[id_joueur].e = PLAYING;
		p->joueurs[id_joueur].mise_actuelle = mise;
		p->joueurs[id_joueur].mise_totale = mise;
		p->joueurs[id_joueur].credit += -mise;
		printf("JOUEUR %d mise %d\n", id_joueur, mise);

		if(tour_est_demarre(p)){
			printf("TOUS LES JOUEURS ONT MISES, DEBUT PARTIE\n");
			init_tour(p);
		}
		return mise;
	}
	return -1;
}

//check si un joueur a fini de jouer, passe a l'état FINISHED si oui
int check_joueur_actif(plateau *p, int id_joueur){
	int nb_jeux = p->joueurs[id_joueur].nb_jeux;
	for(int i=0; i<nb_jeux; i++){
		if(p->joueurs[id_joueur].jeux[i].e_jeu==JOUE){
			return 0;
		}
	}

	printf("JOUEUR %d A FINI DE JOUER \n",id_joueur);
	p->joueurs[id_joueur].e = FINISHED;
	return 1;
}

int get_id_from_adresse(plateau *p, char *adresse){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(strcmp(p->joueurs[i].adresse, adresse)==0){
			return i;
		}
	}
	return -1;
}


char * plateau_to_json(plateau *p, int id_joueur, char *msg){

	printf("id >>> %d\n", id_joueur);

	char *buf = malloc(sizeof(char)*MAX_BUF_PLATEAU);
	char *str = malloc(sizeof(char)*MAX_MSG+1);
	buf[0] = '\0';
	strcat(buf,"{\n");

	strcat(buf,"\"id_joueur_plateau\": ");
	sprintf(str, "\"%d\",\n", id_joueur);
	strcat(buf,str);
	strcat(buf,"\"dialogue\": ");
	sprintf(str, "\"%s\",\n", msg);
	strcat(buf,str);

	strcat(buf,"\"nb_joueur\": ");
	sprintf(str, "\"%d\",\n", p->nb_joueur);
	strcat(buf,str);
	strcat(buf,"\"tour_id_joueur\": ");
	sprintf(str, "\"%d\",\n", p->tour_id_joueur);
	strcat(buf,str);
	strcat(buf,"\"tour_id_jeu\": ");
	sprintf(str, "\"%d\",\n", p->tour_id_jeu);
	strcat(buf,str);
	strcat(buf,"\"tour_started\": ");
	sprintf(str, "\"%d\",\n", p->tour_started);
	strcat(buf,str);

	strcat(buf,"\"jeu_croupier\": ");
	strcat(buf,jeu_to_json(&(p->jeu_croupier)));
	strcat(buf,",\n");
	strcat(buf,"\"joueurs\": \n[\n");

	int cpt = 0;
	for(int i=0; i< NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e!=OFF){
			if(cpt>0){
				strcat(buf, ",\n");
			}
			char * joueur = joueur_to_json(&(p->joueurs[i]));
			strcat(buf, joueur);
			free(joueur);
			cpt++;
		}
	}
	strcat(buf,"\n]\n");

	strcat(buf,"\n}\n\0");

	return buf;

}




