#define NB_JOUEUR_MAX 7

typedef struct{
	tas pioche;
	jeu jeu_croupier;
	joueur joueurs*;
	int nb_joueur;
} plateau;

void init_plateau(plateau *p);
void distribuer_carte(plateau *p, jeu *j);

int rejoindre_partie(plateau *p);
void quitter_partie(plateau *p, id_joueur);
