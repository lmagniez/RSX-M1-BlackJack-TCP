package Reseau;

import java.util.ArrayList;

import Constante.ConstanteParser;
import Model.CarteCouleur;
import Model.CarteValue;
import Model.EtatJeu;
import Model.EtatJoueur;
import Model.Jeu;
import Model.Joueur;
import Model.Plateau;
import Panel.Menu.FrameJeuMenu;

public class Parser implements ConstanteParser{

		public static Parser share = new Parser();
		public String[] jsonArrayGeneral;
		public String[] jsonJoueurs;
		public String[] ligneSplit;
		public String joueursJSON="";
		
		public String ligneReplace;
		
		
		public Plateau parseJsonData(String json) {
			return share.parseData(json);
		}
		
		public String parseJsonMessage(String json) {
			return share.parseMessage(json);
		}

		private Plateau parseData(String json) {
			Plateau plateau = new Plateau();
			jsonArrayGeneral = json.split("\n");
			for(int i=0 ; i< jsonArrayGeneral.length;i++) {
				if(jsonArrayGeneral[i].contains(jeu_croupier)) {
					plateau.setJeu_croupier(parseJeu(i,jsonArrayGeneral,size_jeu_croupier));
				}
				if(jsonArrayGeneral[i].contains(joueurs)) {
					for(int a=i ; a< jsonArrayGeneral.length;a++) {
						joueursJSON += jsonArrayGeneral[a]+"\n";
					}
					parseJoueur(plateau);
					break;
				}else{
					parseSimpleChampPlateau(plateau,jsonArrayGeneral[i]);
				}
			}
			return plateau;
		}

		private void parseJoueur(Plateau plateau) {
			jsonArrayGeneral = joueursJSON.split("},\n");
			for(int i = 0 ; i< jsonArrayGeneral.length;i++) {
				plateau.getListJoueur().add(parseUnJoueur(jsonArrayGeneral[i]));
			}
			System.out.print(plateau);
		}

		private Joueur parseUnJoueur(String joueurJson) {
			jsonJoueurs = joueurJson.split("\n");
			Joueur newJ = new Joueur();

			System.out.println(joueurJson+"\n");
			for(int i = 0 ; i< jsonJoueurs.length;i++) {
				if(jsonJoueurs[i].contains(jeux)) {
					recupAllJeuPlayer(newJ,i,true);
					break;
				}else {
					parseSimpleChampJoueur(newJ,jsonJoueurs[i]);
				}
			}
			return newJ;
		}

		private void recupAllJeuPlayer(Joueur newJ,int numLigne,boolean premier) {
			if(!jsonJoueurs[numLigne].contains("}, {") && !premier) {
				return;
			}
			newJ.getJeux().add(parseJeu(numLigne,jsonJoueurs,size_jeu_croupier+1));
			recupAllJeuPlayer(newJ,numLigne+size_jeu_croupier+1,false);
		}

		//-------------------------------------
		//---------------PLATEAU---------------
		//-------------------------------------
		private void parseSimpleChampPlateau(Plateau plateau, String ligne) {
			ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
			if(ligne.contains(nb_joueur)) {
				plateau.setNb_joueur(Integer.parseInt(ligneReplace));
				return;
			}
			else if(ligne.contains(tour_id_joueur)) {
				plateau.setTour_id_joueur(Integer.parseInt(ligneReplace));
				return;
			}
			else if(ligne.contains(tour_id_jeu)) {
				plateau.setTour_id_jeu(Integer.parseInt(ligneReplace));
				return;
			}
		}
		
		
		//-------------------------------------
		//---------------JOUEUR----------------
		//-------------------------------------
		private void parseSimpleChampJoueur(Joueur joueur, String ligne) {
			if(ligne.contains(id_joueur)) {
				ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
				joueur.setId_joueur(Integer.parseInt(ligneReplace));
				return;
			}
			if(ligne.contains(credit)) {
				ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
				joueur.setCredit(Integer.parseInt(ligneReplace));
				return;
			}
			if(ligne.contains(mise_totale)) {
				ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
				joueur.setMise_totale(Integer.parseInt(ligneReplace));
				return;
			}
			if(ligne.contains(mise_actuelle)) {
				ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
				joueur.setMise_actuelle(Integer.parseInt(ligneReplace));
				return;
			}
			if(ligne.contains(etat)) {
				ligneSplit = ligne.split(":");
				ligneSplit[1] = ligneSplit[1].replaceAll("[-:{}_,\"\t ]", "");
				joueur.setEtat(EtatJoueur.valueOf(ligneSplit[1]));
				return;
			}
		}

		//---------------------------------
		//-------------GENERIQUE-----------
		//---------------------------------
		
		private Jeu parseJeu(int i,String [] jsonArray,int sizeJeu) {
			Jeu jeu = new Jeu();
			for(int a = i+1 ; a < i+sizeJeu ;a++) {
				ligneSplit = jsonArray[a].split(":");
				if(ligneSplit.length == 1)continue;
				ligneReplace = ligneSplit[1].replaceAll("[-:{}_\"\t \r ]", "");
				
				if(ligneSplit[0].contains(couleurs)) {
					ligneSplit = ligneReplace.split(",");
					for(int b = 0 ; b < ligneSplit.length ;b++) {
						ligneReplace = ligneSplit[b].replaceAll("[-:{} \\[ \\]_\"\t \r ]", "");
						if(!ligneReplace.isEmpty())jeu.getJeuCouleurs().add(CarteCouleur.valueOf(ligneReplace));
					}
				}else if(ligneSplit[0].contains(cartes)) {
					ligneSplit = ligneReplace.split(",");
					for(int b = 0 ; b < ligneSplit.length ;b++) {
						ligneReplace = ligneSplit[b].replaceAll("[-:{} \\[ \\]_\"\t \r ]", "");
						if(!ligneReplace.isEmpty())jeu.getJeuCartes().add(CarteValue.valueOf(ligneReplace));
					}
				}
				else if(ligneSplit[0].contains(etat_jeu)){
					ligneReplace = ligneReplace.replaceAll("[,]", "");
					jeu.setEtat(EtatJeu.valueOf(ligneReplace));
				}
				else{
					jeu.setValue(Integer.parseInt(ligneReplace));
				}
			}
			return jeu;
		}
	
		
		//---------------------------------
		//------------MESSAGE--------------
		//---------------------------------
		private String parseMessage(String ligne) {
			if(ligne.contains(taille)) {
				ligneReplace = ligne.replaceAll("[a-zA-Z-:{}_,\"\t ]", "");
				return ligneReplace;
			}
			
			return "";
		}
		
}
