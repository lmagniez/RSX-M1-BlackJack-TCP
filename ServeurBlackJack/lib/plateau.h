#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include "tas.h"
#include "jeu.h"
#include "joueur.h"


#define NB_JOUEUR_MAX 7
#define MAX_BUF_PLATEAU 2500

typedef struct{
	tas pioche;
	jeu jeu_croupier;
	joueur *joueurs;
	int nb_joueur;
	int tour_started;
	int tour_id_joueur;
	int tour_id_jeu;
} plateau;

void init_plateau(plateau *p);
void destroy_plateau(plateau *p);
void distribuer_carte(plateau *p, jeu *j);
void afficher_plateau(plateau *p);

int rejoindre_partie(plateau *p, int credit, char *adresse);
int quitter_partie(plateau *p, int id_joueur);

int peut_commencer_tour(plateau *p);
int action_croupier(plateau *p);

void tour_croupier(plateau *p);

int demander_mise(plateau *p, int id_joueur, int mise);
int demander_split(plateau *p, int id_joueur);
int demander_tirer(plateau *p, int id_joueur);
int demander_rester(plateau *p, int id_joueur);
int demander_double(plateau *p, int id_joueur);
int demander_abandon(plateau *p, int id_joueur);
int check_joueur_actif(plateau *p, int id_joueur);
char * plateau_to_json(plateau *p, int id_joueur, char *msg);
int get_id_from_adresse(plateau *p, char *adresse);

void init_tour(plateau *p);
void demarre_tour(plateau *p);
int tour_est_demarre(plateau *p);

#endif
