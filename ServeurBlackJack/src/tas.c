#include "../lib/tas.h"

void generer_tas(tas* t){
	
	t->cartes = malloc(sizeof(carte)*NB_TOTAL_CARTE);
	t->nb_carte = NB_TOTAL_CARTE;
	t->sommet_pile = 5; //brûle les 5 premières cartes 
	
	int cpt_carte=0;
	for(int i=0; i<NB_JEUX; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<NB_TYPE_CARTE; k++){
				t->cartes[cpt_carte++] = k;
			}
		}
	}
	melanger_tas(t);
}

void swap(tas *t, int i, int j){
	carte tmp = t->cartes[i];
	t->cartes[i] = t->cartes[j];
	t->cartes[j] = tmp;
}

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

void melanger_tas(tas* t){
	srand(time(NULL));

	for(int i=0; i<TAUX_MELANGE; i++){
		int elt_a = rand_a_b(0, NB_TOTAL_CARTE-1);
		int elt_b = rand_a_b(0, NB_TOTAL_CARTE-1);
		swap(t, elt_a, elt_b);
	}
	
}

void afficher_tas(tas* t){
	for(int i=0; i<NB_TOTAL_CARTE; i++){
		int value = getValueFromCarte(t->cartes[i]);
		char* title = getTextFromCarte(t->cartes[i]);
		printf("carte %d: %d (%s)\n", i, value, title);
	}
}

carte get_next_carte(tas *t){
	if(t->sommet_pile<t->nb_carte){
		t->sommet_pile++;
		return t->cartes[t->sommet_pile-1];
	}
	return -1;
}

