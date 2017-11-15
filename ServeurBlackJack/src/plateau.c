
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
}


void afficher_plateau(plateau *p){
	printf("===Plateau:===\n");
	printf("--Tour-- id_joueur: %d id_jeu: %d\n",p->tour_id_joueur, p->tour_id_jeu);
	printf("Croupier: \n");
	afficher_jeu(&(p->jeu_croupier));
	printf("Joueurs: \n");
	for(int i=0; i<NB_JOUEUR_MAX; i++){
		printf("\n");
		afficher_joueur(&(p->joueurs[i]));
	}
}


//id si le joueur peut rejoindre
//-1 si plein
int rejoindre_partie(plateau *p, int credit){
	if(p->nb_joueur == NB_JOUEUR_MAX){
		return -1;
	} 
	else {
		for(int i=0; i<NB_JOUEUR_MAX; i++){
			if(p->joueurs[i].e==OFF){
				start_joueur(&(p->joueurs[i]),credit);
				p->nb_joueur++;
				if(p->nb_joueur==1){
					p->tour_id_joueur = i;
					p->tour_id_jeu = 0;
				}
				
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
	
	return 1;
}

//1 si nouveau tour (lancer le croupier)
int change_tour(plateau *p){
	
	//si plusieurs jeux actifs, accede au prochain jeu du joueur
	int old_tour_id_joueur = p->tour_id_joueur;
	int old_tour_id_jeu = p->tour_id_jeu;
	
	if(p->tour_id_jeu < p->joueurs[p->tour_id_joueur].nb_jeux-1){
		//tant que le prochain jeu n'es
		p->tour_id_jeu = (p->tour_id_jeu + 1)%p->joueurs[p->tour_id_joueur].nb_jeux;
		while(p->joueurs[p->tour_id_joueur].jeux[p->tour_id_jeu].e_jeu==PERDU
		||p->joueurs[p->tour_id_joueur].jeux[p->tour_id_jeu].e_jeu==SATISFAIT){
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
			printf("PLUS DE JOUEURS !!! \n\n");
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
				p->joueurs[i].e=PLAYING;
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

int demander_split(plateau *p, int id_joueur){
	if(p->joueurs[id_joueur].e==PLAYING){
		if(splitter_jeu(&(p->joueurs[id_joueur]))!=-1){;
			printf("change tour\n");
			change_tour(p);
			return 0;
		}
	}
	return -1;
}

int demander_tirer(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur){
		carte c = get_next_carte(&(p->pioche));
		add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c);
		change_tour(p);
		return c;
	}
	return -1;
}

// passe le jeu a satisfait verifie si le joueur a fini de jouer ses paquets
int demander_rester(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur){
		p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;
		check_joueur_actif(p, id_joueur);
		change_tour(p);
		return 1;
	}
	return -1;
}

// double la mise si possible, passe en satisfait le jeu et vérifie si le joueur a fini de jouer tous ses paquets
int demander_double(plateau *p, int id_joueur){
	
	if(p->tour_id_joueur==id_joueur){
		if(p->joueurs[id_joueur].credit > p->joueurs[id_joueur].mise_totale){
			int mise = p->joueurs[id_joueur].mise_totale;
			p->joueurs[id_joueur].mise_actuelle += mise; 
			p->joueurs[id_joueur].mise_totale += mise;
			p->joueurs[id_joueur].credit += -mise;
			carte c = get_next_carte(&(p->pioche));
			add_carte(&(p->joueurs[id_joueur].jeux[p->tour_id_jeu]),c);
			
			
			p->joueurs[id_joueur].jeux[p->tour_id_jeu].e_jeu=SATISFAIT;
			check_joueur_actif(p, id_joueur);
			change_tour(p);
			return c;
			
		}
	}
	return -1;
}


//abandon d'un paquet de carte
int demander_abandon(plateau *p, int id_joueur){
	if(p->tour_id_joueur==id_joueur){
		int num_jeu = p->tour_id_jeu;
		p->joueurs[id_joueur].jeux[num_jeu].e_jeu = PERDU;
		check_joueur_actif(p, id_joueur);
		
		p->joueurs[id_joueur].mise_actuelle = p->joueurs[id_joueur].mise_actuelle 
			- (p->joueurs[id_joueur].mise_totale/p->joueurs[id_joueur].nb_jeux);
		
		change_tour(p);
		
		return 0;
		
	}
	return -1;
}

//en debut de tour
//place la mise
int demander_mise(plateau *p, int id_joueur, int mise){
	if(p->joueurs[id_joueur].e==WAITING && p->joueurs[id_joueur].credit >= mise){
		p->joueurs[id_joueur].e = PLAYING;
		p->joueurs[id_joueur].mise_actuelle = mise;
		p->joueurs[id_joueur].mise_totale = mise;
		p->joueurs[id_joueur].credit += -mise;
		return 0;
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
	p->joueurs[id_joueur].e = FINISHED;
	return 1;
}


