#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carte.h"

#define MAX_CARTE 10

typedef struct{
	carte *cartes;
	int nb_carte;
	int valeur;
} jeu;

void generer_jeu(jeu *j);
void add_carte(jeu *j, carte new);
void update_valeur_totale(jeu *j);
int get_valeur_totale(jeu *j);
int has_blackjack(jeu *j);
void afficher_jeu(jeu *j);

