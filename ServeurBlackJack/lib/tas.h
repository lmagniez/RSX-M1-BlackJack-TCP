#ifndef TAS_H
#define TAS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../lib/carte.h"


#define TAILLE_JEU 52
#define NB_JEUX 6
#define NB_TOTAL_CARTE TAILLE_JEU*NB_JEUX

#define TAUX_MELANGE 500

typedef struct{
	carte *cartes;
	int nb_carte;
	int sommet_pile;
} tas;


void generer_tas(tas* t);
void melanger_tas(tas* t);
void afficher_tas(tas* t);
carte get_next_carte(tas *t);

#endif
