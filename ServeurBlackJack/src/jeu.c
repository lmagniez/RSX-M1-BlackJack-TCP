#include "../lib/jeu.h"

/*
typedef struct{
	carte *main;
	int nb_carte;
	int valeur;
} jeu;
*/

void generer_jeu(jeu *j){
	j->cartes = malloc(sizeof(carte)*MAX_CARTE);
	j->nb_carte = 0;
	j->valeur = 0;
	j->e_jeu = JOUE;
}

void start_jeu(jeu *j){
	j->nb_carte = 0;
	j->valeur = 0;
	j->e_jeu = JOUE;
}

void stop_jeu(jeu *j){
	j->nb_carte = 0;
	j->valeur = 0;
	j->e_jeu = PERDU;
}


void add_carte(jeu *j, carte new){
	printf("ok\n");
	j->cartes[j->nb_carte++]=new;
	printf("ok\n");
	update_valeur_totale(j);
}

carte remove_carte(jeu *j){
	if(j->nb_carte > 0){
		j->nb_carte--;
		update_valeur_totale(j);
		return j->cartes[j->nb_carte];
	}
	else 
		return -1;
}


void update_valeur_totale(jeu *j){
	int nb_as = 0;
	j->valeur=0;
	for(int i=0; i<j->nb_carte; i++){
		int val = getValueFromCarte(j->cartes[i]);
		if(val==11)
			nb_as++;
		j->valeur+=val;
	}
	//ajuste si il y a des as
	while(j->valeur>21&&nb_as>0){
		j->valeur += -10;
		nb_as--; 
	}
}

int get_valeur_totale(jeu *j){
	return j->valeur;
}

int has_blackjack(jeu *j){
	return (j->nb_carte==2&&j->valeur==21);
}

void destroy_jeu(jeu *j){
	free(j->cartes);
}

void afficher_jeu(jeu *j){
	for(int i=0; i<j->nb_carte; i++){
		int val = getValueFromCarte(j->cartes[i]);
		char *title = getTextFromCarte(j->cartes[i]);
		printf("carte %d-> %s val: %d\n", i, title, val);
		
	}
	printf("Etat: %d Score total: %d\n",j->e_jeu, j->valeur);
}
