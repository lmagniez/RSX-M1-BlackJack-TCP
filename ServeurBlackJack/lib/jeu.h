#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "carte.h"

#define MAX_CARTE 10
#define MAX_BUF_JEU 500


typedef enum {JOUE, SATISFAIT, PERDU} etat_jeu;


typedef struct{
	carte *cartes;
	int nb_carte;
	int valeur;
	etat_jeu e_jeu;
} jeu;

void generer_jeu(jeu *j);
etat_jeu add_carte(jeu *j, carte new);
carte remove_carte(jeu *j);
void update_valeur_totale(jeu *j);
int get_valeur_totale(jeu *j);
int has_blackjack(jeu *j);
void afficher_jeu(jeu *j);
void add_carte_croupier(jeu *j, carte new);
void reinit_jeu(jeu *j);

void start_jeu(jeu *j);
void stop_jeu(jeu *j);
void destroy_jeu(jeu *j);

char * jeu_to_json(jeu *j);

#endif
