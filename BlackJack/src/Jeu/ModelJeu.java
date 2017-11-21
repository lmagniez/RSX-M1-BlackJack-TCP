package Jeu;

import java.util.ArrayList;

import Model.Joueur;

public class ModelJeu {

	private Jeu jeu;
	public ArrayList<Joueur> listeJoueur = new ArrayList<Joueur>();
	
	public void addObserverGrille(Jeu j) {
		jeu = j;
		
		//AJOUTER JOUEUR
	}
	
	public void addJoueur() {
		jeu.addJoueur(listeJoueur.get(listeJoueur.size()-1));
	}

	public boolean verifAssezArgent(int mise) {
		return listeJoueur.get(0).getsomme() >= mise;
	}

	public void afficheErreurMessage(String msg) {
		jeu.afficheErreur(msg);
	}

	public void afficheBoutonAction() {
		jeu.afficheBoutonAction();
	}
	
	

}
