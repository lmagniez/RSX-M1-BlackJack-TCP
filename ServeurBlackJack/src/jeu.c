#include "../lib/jeu.h"

char * str_from_etat_jeu(etat_jeu e){
	switch(e){
		case JOUE:
			return "JOUE";
			break;
		case SATISFAIT:
			return "SATISFAIT";
			break;
		case PERDU:
			return "PERDU";
			break;
	}
	return NULL;
}

void generer_jeu(jeu *j){
	j->cartes = malloc(sizeof(face_carte)*MAX_CARTE);
	j->nb_carte = 0;
	j->valeur = 0;
	j->e_jeu = JOUE;
}

void reinit_jeu(jeu *j){
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


//renvoie l'etat du jeu après l'ajout de carte (detecte les PERDU)
etat_jeu add_carte(jeu *j, carte new){
	j->cartes[j->nb_carte++]=new;
	update_valeur_totale(j);
	if(j->valeur>21){
		j->e_jeu = PERDU;
	}
	return j->e_jeu;

}

void add_carte_croupier(jeu *j, carte new){
	j->cartes[j->nb_carte++]=new;
	update_valeur_totale(j);

}

carte remove_carte(jeu *j){
	if(j->nb_carte > 0){
		j->nb_carte--;
		update_valeur_totale(j);
		return j->cartes[j->nb_carte];
	}
	else{
		carte c;
		c.face=-1;
		return c;
	}
}


void update_valeur_totale(jeu *j){
	int nb_as = 0;
	j->valeur=0;
	for(int i=0; i<j->nb_carte; i++){
		int val = getValueFromCarte(j->cartes[i].face);
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
		afficher_carte(&(j->cartes[i]));

	}
	printf("Etat: %s Score total: %d\n",str_from_etat_jeu(j->e_jeu), j->valeur);

}

char * jeu_to_json(jeu *j){
	char *buf = malloc(sizeof(char)*MAX_BUF_JEU);
	char str[12];
	int cur_size = 0;
	buf[cur_size++] = '{';
	buf[cur_size++] = '\n';
	buf[cur_size] = '\0';
	strcat(buf,"\"cartes\": [");
	for(int i=0; i< j->nb_carte; i++){
		if(i>0){
			strcat(buf, ",");
		}
		strcat(buf, "\"");
		strcat(buf, getTextFromCarte(j->cartes[i].face));
		strcat(buf, "\"");
	}
	strcat(buf,"],\n");
	strcat(buf,"\"couleur_cartes\": [");
	for(int i=0; i< j->nb_carte; i++){
		if(i>0){
			strcat(buf, ",");
		}
		strcat(buf, "\"");
		strcat(buf, getTextFromCouleurCarte(j->cartes[i].couleur));
		strcat(buf, "\"");
	}
	strcat(buf,"],\n");


	strcat(buf,"\"etat_jeu\": \"");
	strcat(buf,str_from_etat_jeu(j->e_jeu));
	strcat(buf,"\",\n");
	strcat(buf,"\"value\": \"");
	sprintf(str, "%d", j->valeur);
	strcat(buf, str);
	strcat(buf,"\"\n}");

	return buf;

}


