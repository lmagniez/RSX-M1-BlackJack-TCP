package Base;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import Panel.Menu.FrameJeuMenu;
import Reseau.Parser;

public class BlackJack {

	static String json1 = "{\n" + 
			"	\"nb_joueur\": \"7\",\n" + 
			"	\"tour_id_joueur\": \"2\",\n" + 
			"	\"tour_id_jeu\": \"0\",\n" + 
			"	\"jeu_croupier\": {\n" + 
			"				\"cartes\": [\"reine\", \"cinq\"],\n" + 
			"				\"couleur_cartes\": [\"carreau\", \"coeur\"],\n" + 
			"		\"etat_jeu\": \"JOUE\",\n" + 
			"		\"value\": \"0\"\n" + 
			"	},\n" + 
			"	\"joueurs\": [{\n" + 
			"			\"id_joueur\": \"0\",\n" + 
			"			\"credit\": \"400\",\n" + 
			"			\"mise_totale\": \"100\",\n" + 
			"			\"mise_actuelle\": \"100\",\n" + 
			"			\"etat\": \"FINISHED\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"reine\", \"cinq\"],\n" + 
			"				\"couleur_cartes\": [\"carreau\", \"coeur\"],\n" + 
			"				\"etat_jeu\": \"SATISFAIT\",\n" + 
			"				\"value\": \"15\"\n" + 
			"			}, {\n" + 
			"				\"cartes\": [\"reine\", \"cinq\"],\n" + 
			"				\"couleur_cartes\": [\"carreau\", \"coeur\"],\n" + 
			"				\"etat_jeu\": \"SATISFAIT\",\n" + 
			"				\"value\": \"15\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"1\",\n" + 
			"			\"credit\": \"800\",\n" + 
			"			\"mise_totale\": \"400\",\n" + 
			"			\"mise_actuelle\": \"0\",\n" + 
			"			\"etat\": \"FINISHED\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [],\n" + 
			"				\"couleur_cartes\": [],\n" + 
			"				\"etat_jeu\": \"PERDU\",\n" + 
			"				\"value\": \"0\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"2\",\n" + 
			"			\"credit\": \"200\",\n" + 
			"			\"mise_totale\": \"400\",\n" + 
			"			\"mise_actuelle\": \"400\",\n" + 
			"			\"etat\": \"PLAYING\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"quatre\", \"neuf\"],\n" + 
			"				\"couleur_cartes\": [\"trefle\", \"coeur\"],\n" + 
			"				\"etat_jeu\": \"JOUE\",\n" + 
			"				\"value\": \"13\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"3\",\n" + 
			"			\"credit\": \"200\",\n" + 
			"			\"mise_totale\": \"100\",\n" + 
			"			\"mise_actuelle\": \"100\",\n" + 
			"			\"etat\": \"PLAYING\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"deux\", \"dix\"],\n" + 
			"				\"couleur_cartes\": [\"trefle\", \"carreau\"],\n" + 
			"				\"etat_jeu\": \"JOUE\",\n" + 
			"				\"value\": \"12\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"4\",\n" + 
			"			\"credit\": \"1800\",\n" + 
			"			\"mise_totale\": \"200\",\n" + 
			"			\"mise_actuelle\": \"200\",\n" + 
			"			\"etat\": \"PLAYING\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"roi\", \"trois\"],\n" + 
			"				\"couleur_cartes\": [\"trefle\", \"trefle\"],\n" + 
			"				\"etat_jeu\": \"JOUE\",\n" + 
			"				\"value\": \"13\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"5\",\n" + 
			"			\"credit\": \"500\",\n" + 
			"			\"mise_totale\": \"500\",\n" + 
			"			\"mise_actuelle\": \"500\",\n" + 
			"			\"etat\": \"PLAYING\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"dix\", \"reine\"],\n" + 
			"				\"couleur_cartes\": [\"trefle\", \"coeur\"],\n" + 
			"				\"etat_jeu\": \"JOUE\",\n" + 
			"				\"value\": \"20\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		},\n" + 
			"		{\n" + 
			"			\"id_joueur\": \"6\",\n" + 
			"			\"credit\": \"1900\",\n" + 
			"			\"mise_totale\": \"600\",\n" + 
			"			\"mise_actuelle\": \"600\",\n" + 
			"			\"etat\": \"PLAYING\",\n" + 
			"			\"jeux\": [{\n" + 
			"				\"cartes\": [\"valet\", \"sept\"],\n" + 
			"				\"couleur_cartes\": [\"coeur\", \"carreau\"],\n" + 
			"				\"etat_jeu\": \"JOUE\",\n" + 
			"				\"value\": \"17\"\n" + 
			"			}]\n" + 
			"\n" + 
			"		}\n" + 
			"	]\n" + 
			"\n" + 
			"}";
	
	
	public static void main(String [] args) {
		//FrameJeuMenu fen1=new FrameJeuMenu();
		Parser.parseJson(json1);
	}
}
