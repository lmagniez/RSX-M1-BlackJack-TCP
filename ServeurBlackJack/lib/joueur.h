#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carte.h"
#include "jeu.h"

#define MAX_JEUX 3

//OFF: pas de joueur
//WAITING: vient de rejoindre la partie, attend le prochain tour
//PLAYING: joue une partie
//FINISHED: attend les autres joueurs (satisfait de son résultat)
//LOSE: game over mais reste sur le plateau pour observer
typedef enum {OFF, WAITING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_totale;
	int mise_actuelle;
	etat e;
} joueur;

void afficher_joueur(joueur *j);
void generer_joueur(joueur *j, int id_joueur);
void destroy_joueur(joueur *j);
void start_joueur(joueur *j, int credit);
void stop_joueur(joueur *j);

int proposer_mise(joueur *j, int mise);
int peut_splitter(joueur *j);
int splitter_jeu(joueur *j);
int modifier_credit(joueur *j, int credit);

#endif

