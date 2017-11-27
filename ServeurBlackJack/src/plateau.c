
#include "../lib/plateau.h"

/*
typedef struct{
	tas pioche;
	jeu jeu_croupier;
	joueur joueurs*;
	int nb_joueur;
	int tour_id_joueur;
	int tour_id_jeu;
} plateau;

typedef enum {OFF, WAITING, PLAYING, FINISHED, LOSE} etat;
typedef enum {JOUE, SATISFAIT, PERDU} etat_jeu;


typedef struct{
	int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_actuelle;
	etat e;
} joueur;
*/

/*
void generer_joueur(joueur *j, int id_joueur, int credit);
int proposer_mise(joueur *j, int mise);
int peut_splitter(joueur *j);
int splitter_jeu(joueur *j);
void modifier_credit(joueur *j, int credit);
*/

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
	printf("JSON: \n%s\n",plateau_to_json(p));
}


//id si le joueur peut rejoindre
//-1 si plein
int rejoindre_partie(plateau *p, int credit, char *adresse){
	if(p->nb_joueur == NB_JOUEUR_MAX){
		return -1;
	}
	else {
		for(int i=0; i<NB_JOUEUR_MAX; i++){
			if(p->joueurs[i].e==OFF){
				start_joueur(&(p->joueurs[i]),credit, adresse, p->tour_started);
				p->nb_joueur++;
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

	return 1;
}

//distribue 2 cartes à chaque joueurs, 1 au croupier
void init_tour(plateau *p){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e == PLAYING){
			//demander_tirer(p, i);
			carte c = get_next_carte(&(p->pioche));
			add_carte(&(p->joueurs[i].jeux[0]),c);
			carte c = get_next_carte(&(p->pioche));
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

//nouveau tour: passe les joueurs en attente 
/*
void demarre_tour(plateau *p){
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		if(p->joueurs[i].e == WAITING)
			p->joueurs[i].e = BETTING;
	}
	p->tour_started = 1;
}*/

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
			tour_croupier(p);
			return 0;
		}
		p->tour_id_joueur= (p->tour_id_joueur+1)%NB_JOUEUR_MAX;
	}
	p->tour_id_jeu = 0;
	//nouveau tour
	if(p->tour_id_joueur<=old_tour_id_joueur){
		//action_croupier(p);
		for(int i=0; i<NB_JOUEUR_MAX; i++){
			if(p->joueurs[i].e==WAITING)
				p->joueurs[i].e=BETTING;
		}
		return 1;
	}

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
		p->jeu_croupier.e_jeu=PERDU;
	}
	else{
		p->jeu_croupier.e_jeu=SATISFAIT;
	}

	for(int i=0; i<NB_JOUEUR_MAX; i++){

		//que les joueurs qui ont joués
		if(p->joueurs[i].e==FINISHED){
			int mise_par_jeu = p->joueurs[i].mise_totale/p->joueurs[i].nb_jeux;
			for(int j=0; j<p->joueurs[i].nb_jeux; j++){
				//joueur gagne: Gagne la mise *1.5 (Blackjack: 2)
				if(p->joueurs[i].jeux[j].e_jeu==SATISFAIT&&p->jeu_croupier.e_jeu==PERDU){
					if(has_blackjack(&(p->joueurs[i].jeux[j]))){
						printf("BLACKJACK AU JOUEUR %d POUR LE JEU %d! GAIN: %d \n", i, j, mise_par_jeu*2);
						p->joueurs[i].credit += mise_par_jeu * 2;
					}
					else{
						printf("VICTOIRE AU JOUEUR %d POUR LE JEU %d! GAIN: %f \n", i, j, mise_par_jeu*1.5);
						p->joueurs[i].credit += mise_par_jeu * 1.5;
					}
				}
				//test qui a la plus petite valeur + Blackjack
				if(p->joueurs[i].jeux[j].e_jeu==SATISFAIT&&p->jeu_croupier.e_jeu==SATISFAIT){
					if(has_blackjack(&(p->jeu_croupier))){
						printf("BLACKJACK AU CROUPIER! PERTE DES GAINS POUR LE JOUEUR %d (JEU %d) (%d CREDITS)\n", i, j, mise_par_jeu);
					}
					else if(has_blackjack(&(p->joueurs[i].jeux[j]))){
						printf("BLACKJACK AU JOUEUR %d POUR LE JEU %d! GAIN: %d \n", i, j, (mise_par_jeu*2));
						p->joueurs[i].credit += mise_par_jeu * 2;
					}
					else if(p->joueurs[i].jeux[j].valeur > p->jeu_croupier.valeur){
						printf("VICTOIRE AU JOUEUR %d POUR LE JEU %d! GAIN: %f \n", i, j, (mise_par_jeu*1.5));
						p->joueurs[i].credit += mise_par_jeu * 1.5;
					}
					else{
						printf("VICTOIRE AU CROUPIER! PERTE DES GAINS POUR LE JOUEUR %d (JEU %d) (%d CREDITS)\n", i, j, mise_par_jeu);
					}

				}
				reinit_jeu(&(p->joueurs[i].jeux[j]));
				init_tour(p);
			}
			p->joueurs[i].mise_actuelle = 0;
			p->joueurs[i].mise_totale = 0;
			if(p->joueurs[i].credit <= 0){
				printf("JOUEUR %d N'A PLUS DE CREDIT! HORS-JEU \n",i);
				p->joueurs[i].e = LOSE;
			}
			else{
				p->joueurs[i].e = PLAYING;
			}
		}
	}

}

// Le joueur doit avoir deux paires pour splitter
int demander_split(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur&&
		p->joueurs[id_joueur].e==PLAYING){
		int id_jeu;
		if((id_jeu=splitter_jeu(&(p->joueurs[id_joueur])))!=-1){;
			printf("JOUEUR %d SPLITTE SON JEU %d\n",id_joueur, p->tour_id_jeu);
			change_tour(p);
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

			printf("JOUEUR %d PERD SON JEU %d\n",id_joueur, p->tour_id_jeu);
			check_joueur_actif(p, id_joueur);

			int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);
			p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
				- montant_perdu;
		}
		change_tour(p);
		return c.face;
	}


	return -1;
}

// passe le jeu a satisfait verifie si le joueur a fini de jouer ses paquets
int demander_rester(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur
		&&p->joueurs[id_joueur].e==PLAYING){
		p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;

		printf("JOUEUR %d EST SATISFAIT DE SON JEU %d\n",id_joueur, p->tour_id_jeu);
		check_joueur_actif(p, id_joueur);

		change_tour(p);
		return 1;
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

			printf("JOUEUR %d EST SATISFAIT DE SON JEU ET DOUBLE %d\n",id_joueur, p->tour_id_jeu);
			//add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c);
			if(add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c)==PERDU){

				printf("MAIS JOUEUR %d PERD SON JEU %d\n",id_joueur, p->tour_id_jeu);

				int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);
				p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
					- montant_perdu;
			}
			else{
				p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;
			}

			check_joueur_actif(p, id_joueur);

			change_tour(p);
			return c.face;

		}
	}
	return -1;
}


//abandon d'un paquet de carte
int demander_abandon(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur){
		int num_jeu = p->tour_id_jeu;

		printf("JOUEUR %d ABANDONNE SON JEU %d\n",id_joueur, p->tour_id_jeu);
		p->joueurs[id_joueur].jeux[num_jeu].e_jeu = PERDU;
		check_joueur_actif(p, id_joueur);

		int montant_perdu = (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);

		p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle
			- montant_perdu;
		//le joueur ne perd que la moitié de la somme
		p->joueurs[id_joueur].credit += montant_perdu / 2;

		change_tour(p);

		return 0;

	}
	return -1;
}

//en debut de tour
//place la mise
int demander_mise(plateau *p, int id_joueur, int mise){
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


char * plateau_to_json(plateau *p){

	char *buf = malloc(sizeof(char)*MAX_BUF_PLATEAU);
	char *str = malloc(sizeof(char)*12);
	int cur_size = 0;
	buf[cur_size++] = '{';
	buf[cur_size++] = '\n';
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
			cpt++;
		}
	}
	strcat(buf,"\n]\n");

	strcat(buf,"\n}\n");

	return buf;

}




