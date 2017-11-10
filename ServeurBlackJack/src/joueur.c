
#include "../lib/joueur.h"

/*
typedef enum {WAITING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_actuelle;
	etat e;
} joueur;
*/

void generer_joueur(joueur *j, int id_joueur, int credit){
	j->id_joueur = id_joueur;
	j->credit = credit;
	j->mise_actuelle = -1;
	j->e = WAITING;
	j->nb_jeux = 1;
	jeux->jeux = malloc(sizeof(jeu)*MAX_JEUX);
	generer_jeu(j->jeux[0]);
}

//si la mise est possible, passe le joueur en état PLAYING
//sinon retourne -1
int proposer_mise(joueur *j, int mise){
	if(j->credit>mise){
		j->credit += -mise; 
		j->e = PLAYING;
		return 1;
	}
	return -1;
}

//retourne l'indice du jeu pouvant être splitté
//sinon retourne -1 
int peut_splitter(joueur *j){
	if(j->nb_jeux==3)
		return -1;
	for(int i=0; i<j->nb_jeux; i++){
		if(j->jeux[i]->nb_carte==2){
			int val1 = getValueFromCarte(j->jeux[i]->cartes[0]);
			int val2 = getValueFromCarte(j->jeux[i]->cartes[0]);
			if(val1 == val2)
				return i;
		}
	}
	return -1;
}

//DOIT VERIFIER SI LE SPLIT EST POSSIBLE
//splitte le jeu
void splitter_jeu(joueur *j, int id_jeu){
	
}
void modifier_credit(joueur *j, int credit);

void demander_split(joueur *j, plateau *p);
void demander_tirer(joueur *j, plateau *p);
void demander_rester(joueur *j, plateau *p);
void demander_double(joueur *j, plateau *p);
void demander_abandon(joueur *j, plateau *p);
