
#include <stdio.h>
#include <stdlib.h>

#include "../lib/tas.h"
#include "../lib/jeu.h"


int main(){
	
	carte c = AS;
	int res = getValueFromCarte(c);
	char* title = getTextFromCarte(c);
	
	
	printf("res: %d (%s)\n",res, title);

	tas t; 
	generer_tas(&t);
	melanger_tas(&t);
	afficher_tas(&t);
	
	jeu j; 
	generer_jeu(&j);
	add_carte(&j, get_next_carte(&t));
	add_carte(&j, get_next_carte(&t));
	add_carte(&j, get_next_carte(&t));
	add_carte(&j, get_next_carte(&t));
	
	afficher_jeu(&j);
	
	free(t.cartes);
	free(j.cartes);

}
