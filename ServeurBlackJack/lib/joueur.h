#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carte.h"
#include "jeu.h"

#define MAX_JEUX 3
#define MAX_BUF_JOUEUR 1000


//OFF: pas de joueur
//WAITING: vient de rejoindre la partie, attend le prochain tour
//BETTING: joue une partie, pas encore misé
//PLAYING: joue une partie
//FINISHED: attend les autres joueurs (satisfait de son résultat)
//LOSE: game over mais reste sur le plateau pour observer
typedef enum {OFF, WAITING, BETTING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	char *adresse;
	//thread
	//num socket
	int nb_jeux;
	int credit;
	int mise_totale;
	int mise_actuelle;
	etat e;
} joueur;

void afficher_joueur(joueur *j);
void generer_joueur(joueur *j, int id_joueur);
void destroy_joueur(joueur *j);
void start_joueur(joueur *j, int credit, char *adresse, int tour_started);
void stop_joueur(joueur *j);

int proposer_mise(joueur *j, int mise);
int peut_splitter(joueur *j);
int splitter_jeu(joueur *j);
int modifier_credit(joueur *j, int credit);

char * joueur_to_json(joueur *j);

#endif

