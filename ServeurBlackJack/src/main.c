
#include <stdio.h>
#include <stdlib.h>

#include "../lib/tas.h"
#include "../lib/jeu.h"
#include "../lib/joueur.h"
#include "../lib/plateau.h"

void test_carte(){

	face_carte c = AS;
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

void test_double(){
	plateau p;
	init_plateau(&p);

	//afficher_tas(&(p.pioche));

	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 1000, "127.000.1.2");

	demander_mise(&p, 0, 200);
	demander_mise(&p, 1, 500);

	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_double(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,1);



	/*
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	*/

	afficher_plateau(&p);
}


void test_split(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");

	demander_mise(&p, 0, 500);

	p.joueurs[0].jeux[0].cartes[0].face = ROI;
	p.joueurs[0].jeux[0].cartes[0].couleur = TREFLE;
	p.joueurs[0].jeux[0].cartes[1].face = ROI;
	p.joueurs[0].jeux[0].cartes[1].couleur = COEUR;
	p.joueurs[0].jeux[0].nb_carte = 2;
	update_valeur_totale(&(p.joueurs[0].jeux[0]));

	demander_split(&p, 0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);


	/*
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	*/

	afficher_plateau(&p);
}

void test_split2(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");

	demander_mise(&p, 0, 500);

	p.joueurs[0].nb_jeux = 2;
	p.joueurs[0].jeux[0].cartes[0].face = ROI;
	p.joueurs[0].jeux[0].cartes[0].couleur = TREFLE;
	p.joueurs[0].jeux[0].cartes[1].face = ROI;
	p.joueurs[0].jeux[0].cartes[1].couleur = COEUR;
	p.joueurs[0].jeux[0].nb_carte = 2;

	p.joueurs[0].jeux[1].cartes[0].face = DEUX;
	p.joueurs[0].jeux[1].cartes[0].couleur = COEUR;
	p.joueurs[0].jeux[1].cartes[1].face = ROI;
	p.joueurs[0].jeux[1].cartes[1].couleur = PIQUE;
	p.joueurs[0].jeux[1].nb_carte = 2;
	update_valeur_totale(&(p.joueurs[0].jeux[0]));
	update_valeur_totale(&(p.joueurs[0].jeux[1]));

	demander_split(&p, 0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);


	/*
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	*/

	afficher_plateau(&p);
}

void test_general(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 500, "127.000.1.2");
	rejoindre_partie(&p, 500, "127.000.1.3");
	rejoindre_partie(&p, 500, "127.000.1.4");
	rejoindre_partie(&p, 500, "127.000.1.5");
	quitter_partie(&p, 1);
	quitter_partie(&p, 3);
	rejoindre_partie(&p, 1000, "127.000.1.6");

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 1200);
	demander_mise(&p, 2, 200);
	demander_mise(&p, 4, 500);


	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,2);
	demander_tirer(&p,3);
	demander_tirer(&p,4);
	demander_tirer(&p,5);
	demander_tirer(&p,0);
	demander_tirer(&p,1);


	afficher_plateau(&p);

}

void test_abandon(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 1000, "127.000.1.2");

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 400);


	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,0);
	demander_tirer(&p,1);

	demander_abandon(&p, 0);

	afficher_plateau(&p);
}

void test_abandon2(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	demander_mise(&p, 0, 500);

	p.joueurs[0].jeux[0].cartes[0].face = ROI;
	p.joueurs[0].jeux[0].cartes[0].couleur = TREFLE;
	p.joueurs[0].jeux[0].cartes[1].face = ROI;
	p.joueurs[0].jeux[0].cartes[1].couleur = COEUR;
	p.joueurs[0].jeux[0].nb_carte = 2;
	update_valeur_totale(&(p.joueurs[0].jeux[0]));

	demander_split(&p, 0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_abandon(&p, 0);

	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);


	afficher_plateau(&p);

}

void test_reste(){

	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 1000, "127.000.1.2");

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 400);


	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,0);
	demander_tirer(&p,1);
	demander_tirer(&p,0);

	demander_rester(&p, 1);

	demander_tirer(&p,0);
	demander_tirer(&p,0);
	demander_tirer(&p,0);

	afficher_plateau(&p);

}

void big_test(){
	plateau p;
	init_plateau(&p);
	rejoindre_partie(&p, 500, "127.000.1.1");
	rejoindre_partie(&p, 1000, "127.000.1.2");
	rejoindre_partie(&p, 600, "127.000.1.3");
	rejoindre_partie(&p, 300, "127.000.1.4");
	rejoindre_partie(&p, 2000, "127.000.1.5");
	rejoindre_partie(&p, 1000, "127.000.1.6");
	//quitter_partie(&p, 3);

	demander_mise(&p, 0, 100);
	demander_mise(&p, 1, 400);
	demander_mise(&p, 2, 400);
	demander_mise(&p, 3, 100);
	demander_mise(&p, 4, 200);
	demander_mise(&p, 5, 500);
	
	rejoindre_partie(&p, 2500, "127.000.1.7");
	demander_mise(&p, 6, 600);


	afficher_plateau(&p);
	printf("%s",plateau_to_json(&p));
	/*
	for(int i=0; i<7; i++){
		demander_tirer(&p,i);
	}
	for(int i=0; i<7; i++){
		demander_tirer(&p,i);
	}

	demander_rester(&p, 0);
	demander_abandon(&p, 1);
	*/
}

int main(){



	//test_general();
	//test_split();
	//test_split2();
	//test_double();
	//test_abandon();
	//test_abandon2();
	//test_reste();

	big_test();

}
