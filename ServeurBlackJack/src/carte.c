
#include "../lib/carte.h"

int getValueFromCarte(face_carte c){
	switch(c){
		case AS:
			return 11;
			break;
		case DEUX:
			return 2;
			break;
		case TROIS:
			return 3;
			break;
		case QUATRE:
			return 4;
			break;
		case CINQ:
			return 5;
			break;
		case SIX:
			return 6;
			break;
		case SEPT:
			return 7;
			break;
		case HUIT:
			return 8;
			break;
		case NEUF:
			return 9;
			break;
		case DIX:
			return 10;
			break;
		case VALET:
			return 10;
			break;
		case REINE:
			return 10;
			break;
		case ROI:
			return 10;
			break;
	}
	return -1;
}

char* getTextFromCarte(face_carte c){
	switch(c){
		case AS:
			return "as";
			break;
		case DEUX:
			return "deux";
			break;
		case TROIS:
			return "trois";
			break;
		case QUATRE:
			return "quatre";
			break;
		case CINQ:
			return "cinq";
			break;
		case SIX:
			return "six";
			break;
		case SEPT:
			return "sept";
			break;
		case HUIT:
			return "huit";
			break;
		case NEUF:
			return "neuf";
			break;
		case DIX:
			return "dix";
			break;
		case VALET:
			return "valet";
			break;
		case REINE:
			return "reine";
			break;
		case ROI:
			return "roi";
			break;
	}
	return "error";
}

char* getTextFromCouleurCarte(couleur_carte c){
	switch(c){
		case COEUR:
			return "coeur";
			break;
		case CARREAU:
			return "carreau";
			break;
		case PIQUE:
			return "pique";
			break;
		case TREFLE:
			return "trefle";
			break;
	}
	return "error";
}


void afficher_carte(carte *c){
	printf("%s:%s\n",getTextFromCarte(c->face),getTextFromCouleurCarte(c->couleur));
}

/*
int main(){
	carte c = AS;
	int res = getValueFromCarte(c);
	char* title = getTextFromCarte(c);
	
	
	printf("res: %d (%s)\n",res, title);
}
*/
