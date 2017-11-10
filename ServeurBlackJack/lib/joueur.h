#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carte.h"
#define MAX_JEUX 3

//WAITING: vient de rejoindre la partie, attend le prochain tour
//PLAYING: joue une partie
//FINISHED: attend les autres joueurs (satisfait de son résultat)
//LOSE: game over mais reste sur le plateau pour observer
typedef enum {WAITING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_actuelle;
	etat e;
} joueur;

void generer_joueur(joueur *j, int id_joueur, int credit);
int proposer_mise(joueur *j, int mise);
int peut_splitter(joueur *j);
void splitter_jeu(joueur *j, int id_jeu);
void modifier_credit(joueur *j, int credit);

void demander_split(joueur *j, plateau *p);
void demander_tirer(joueur *j, plateau *p);
void demander_rester(joueur *j, plateau *p);
void demander_double(joueur *j, plateau *p);
void demander_abandon(joueur *j, plateau *p);



