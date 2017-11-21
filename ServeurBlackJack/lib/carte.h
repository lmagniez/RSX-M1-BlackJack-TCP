
#ifndef CARTE_H
#define CARTE_H

#include <stdio.h>
#include <stdlib.h>

#define NB_TYPE_CARTE 13
#define NB_COULEURS 4

typedef enum {AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,REINE,ROI} face_carte;
typedef enum {COEUR, TREFLE, PIQUE, CARREAU} couleur_carte;

typedef struct {
	face_carte face;
	couleur_carte couleur;
} carte;


int getValueFromCarte(face_carte c);
char* getTextFromCarte(face_carte c);
char* getTextFromCouleurCarte(couleur_carte c);
void afficher_carte(carte *c);


#endif
