
#include "../lib/joueur.h"

/*
typedef enum {WAITING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_actuelle;
	etat e;
} joueur;
*/

char * str_from_etat(etat e){
	switch(e){
		case OFF:
			return "OFF";
			break;
		case WAITING:
			return "WAITING";
			break;
		case PLAYING:
			return "PLAYING";
			break;
		case FINISHED:
			return "FINISHED";
			break;
		case LOSE:
			return "LOSE";
			break;
			
	}
	return NULL;
}

void generer_joueur(joueur *j, int id_joueur){
	j->id_joueur = id_joueur;
	j->credit = -1;
	j->mise_actuelle = -1;
	j->mise_totale = -1;
	j->e = OFF;
	j->nb_jeux = -1;
	j->jeux = malloc(sizeof(jeu)*MAX_JEUX);
	for(int i=0; i<MAX_JEUX; i++){
		generer_jeu(&(j->jeux[i]));
	}
}

void destroy_joueur(joueur *j){
	for(int i=0; i<MAX_JEUX; i++){
		destroy_jeu(&(j->jeux[0]));
	}
	free(j->jeux);
}

void start_joueur(joueur *j, int credit){
	j->credit = credit;
	j->mise_actuelle = 0;
	j->mise_totale = 0;
	j->e = WAITING;
	j->nb_jeux = 1;
	start_jeu(&(j->jeux[0]));
}

void stop_joueur(joueur *j){
	j->credit = -1;
	j->mise_actuelle = -1;
	j->e = OFF;
	j->nb_jeux = -1;
}



void afficher_joueur(joueur *j){
	printf("--Joueur %d-- Credit: %d Mise: %d (reel: %d) Etat: %s\n", 
		j->id_joueur, j->credit, j->mise_totale, j->mise_actuelle, str_from_etat(j->e));
	for(int i=0; i<j->nb_jeux; i++){
		printf("Jeu %d\n",i);
		afficher_jeu(&(j->jeux[i]));
	}
	//printf("JSON: \n%s\n",joueur_to_json(j));
}

//si la mise est possible, passe le joueur en état PLAYING
//sinon retourne -1
int proposer_mise(joueur *j, int mise){
	if(j->credit>mise){
		j->credit += -mise; 
		return 1;
	}
	return -1;
}

//retourne l'indice du jeu pouvant être splitté
//sinon retourne -1 
int peut_splitter(joueur *j){
	if(j->nb_jeux==3)
		return -1;
	for(int i=0; i<j->nb_jeux; i++){
		if(j->jeux[i].nb_carte==2){
			int val1 = getValueFromCarte(j->jeux[i].cartes[0].face);
			int val2 = getValueFromCarte(j->jeux[i].cartes[1].face);
			if(val1 == val2)
				return i;
		}
	}
	return -1;
}

//VERIFIER SI LE SPLIT EST POSSIBLE
//splitte le jeu
int splitter_jeu(joueur *j){
	int id_jeux=peut_splitter(j);
	
	if(id_jeux!=-1){
		j->nb_jeux++;
		j->jeux[j->nb_jeux-1].e_jeu = JOUE;
		carte c = remove_carte(&(j->jeux[id_jeux]));
		add_carte(&(j->jeux[j->nb_jeux-1]),c);
		return j->nb_jeux;
	}
	return -1;
	
}

int modifier_credit(joueur *j, int credit){
	j->credit = j->credit + credit;
	return j->credit;
}


int id_joueur;
	jeu *jeux;
	int nb_jeux;
	int credit;
	int mise_totale;
	int mise_actuelle;
	etat e;

char * joueur_to_json(joueur *j){
	
	char *buf = malloc(sizeof(char)*MAX_BUF_JOUEUR);
	char str[12];
	int cur_size = 0;
	buf[cur_size++] = '{';
	buf[cur_size++] = '\n';
	strcat(buf,"\"id_joueur\": ");
	sprintf(str, "\"%d\",\n", j->id_joueur);
	strcat(buf,str);
	strcat(buf,"\"credit\": ");
	sprintf(str, "\"%d\",\n", j->credit);
	strcat(buf,str);
	strcat(buf,"\"mise_totale\": ");
	sprintf(str, "\"%d\",\n", j->mise_totale);
	strcat(buf,str);
	strcat(buf,"\"mise_actuelle\": ");
	sprintf(str, "\"%d\",\n", j->mise_actuelle);
	strcat(buf,str);
	strcat(buf,"\"etat\": ");
	sprintf(str, "\"%s\",\n", str_from_etat(j->e));
	strcat(buf,str);
	strcat(buf,"\"jeux\": \n[\n");
	for(int i=0; i< j->nb_jeux; i++){
		if(i>0){
			strcat(buf, ",\n");
		}
		strcat(buf, jeu_to_json(&(j->jeux[i])));
		
	}
	strcat(buf,"\n]\n");
	
	strcat(buf,"\n}");
	
	return buf;
	
}

