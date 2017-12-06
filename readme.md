Magniez Loïck
Valembois Vincent

# Execution du projet
## Côté serveur
```
cd ServeurReseau
make
./server
```
## Côté client 
```
cd BlackJack/Rendu
java -jar BlackJack.jar
```

# Ce qui a été réalisé 

## Client
Envoie un message sur le broadcast en UDP "I WANT TO PLAY BLACKJACK !".
L'ensemble des serveurs répondront "COME HERE TO HAVE FUN{nombre de joueurs)".
Le client devra choisir parmi la liste des serveurs proposés et enverra un message GET/CONNECT au serveur en question.

Par la suite, le client enverra un ensemble de commande en REST au serveur et celui-ci renverra le modèle du plateau en JSON

## Serveur
Ecoute sur le port 8080 avec le protocole UDP. Lorsqu'un client envoie le message "I WANT TO PLAY BLACKJACK !". Le serveur créé une connection TCP (Un thread par client). Cette communication se fera sur le port 9090.

## Commandes en REST
GET /action/connect
POST /action/mise <mise>
GET /action/tirer
GET /action/split
GET LEAVE /action/leave
GET DOUBLER /action/doubler
GET RESTER /action/rester

## Modèle du Jeu

### Carte
Carte d'un jeu
```
typedef struct {
	face_carte face;
	couleur_carte couleur;
} carte;
```

### Tas
Pioche pour un jeu
```
typedef struct{
	carte* cartes;
	int nb_carte;
	int sommet_pile;
} tas;
```


### Jeu
Main d'un joueur
Etats d'un jeu: 
- JOUE: Jeu en cours.
- SATISFAIT: Jeu terminé, on l'a validé.
- PERDU: Jeu perdu, on ne le joue plus.
```
typedef struct{
	carte *cartes;
	int nb_carte;
	int valeur;
	etat_jeu e_jeu;
} jeu;

typedef enum {JOUE, SATISFAIT, PERDU} etat_jeu;
```

### Joueur
Etats d'un joueur:
- OFF: pas de joueur
- WAITING: vient de rejoindre la partie, attend le prochain tour
- BETTING: joue une partie, pas encore misé
- PLAYING: joue une partie
- FINISHED: attend les autres joueurs (satisfait de son résultat)
- LOSE: game over mais reste sur le plateau pour observer
```
typedef enum {OFF, WAITING, BETTING, PLAYING, FINISHED, LOSE} etat;

typedef struct{
	int id_joueur;
	jeu *jeux;
	char *adresse;
	int num_socket;
	int nb_jeux;
	int credit;
	int mise_totale;
	int mise_actuelle;
	etat e;
} joueur;
```

### Plateau


## Exemple de modèle JSON
```
{
	"id_joueur_plateau": "2",
	"dialogue": "Le joueur 1 a tiré une carte ",
	"nb_joueur": "2",
	"tour_id_joueur": "1",
	"tour_id_jeu": "0",
	"tour_started": "1",
	"jeu_croupier": {
		"cartes": ["huit"],
		"couleur_cartes": ["coeur"],
		"etat_jeu": "JOUE",
		"value": "8"
	},
	"joueurs": [{
			"id_joueur": "1",
			"credit": "490",
			"mise_totale": "5",
			"mise_actuelle": "5",
			"etat": "PLAYING",
			"jeux": [{
				"cartes": ["deux", "neuf", "huit"],
				"couleur_cartes": ["pique", "carreau", "trefle"],
				"etat_jeu": "JOUE",
				"value": "19"
			}]

		},
		{
			"id_joueur": "2",
			"credit": "492",
			"mise_totale": "5",
			"mise_actuelle": "5",
			"etat": "PLAYING",
			"jeux": [{
				"cartes": ["quatre", "dix"],
				"couleur_cartes": ["pique", "coeur"],
				"etat_jeu": "JOUE",
				"value": "14"
			}]

		}
	]

}
```

# Répartition des tâches
- Vincent : 
    + Interface graphique (java)
    + Réseau (java & c)
    + Parser json (java)
- Loïck : 
    + Petite partie en réseau(adaptation)
    + Jeu et logique du jeu ( c ) 
    + Parser Rest ( c )

# Petit plus 
- Mode spectateur quand le joueur n'a plus d'argent 

# Problèmes non résolus
- Lors d'une déconnexion durant le tour du croupier, celle-ci est prise en compte mais fait bloquer le jeu.
- Robustesse UDP (flooding serveur)

# Améliorations non faites
- IA
- Déconnection pour inactivité
- Pseudo pour les joueurs 

