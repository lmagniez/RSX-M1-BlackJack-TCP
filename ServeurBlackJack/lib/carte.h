
#ifndef CARTE_H
#define CARTE_H

#include <stdio.h>
#include <stdlib.h>

#define NB_TYPE_CARTE 13

typedef enum {AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,REINE,ROI} carte;

int getValueFromCarte(carte c);
char* getTextFromCarte(carte c);

#endif
