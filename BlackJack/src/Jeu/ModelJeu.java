package Jeu;

import java.util.ArrayList;

import Model.Joueur;

public class ModelJeu {

	private Jeu jeu;
	public ArrayList<Joueur> listeJoueur = new ArrayList<Joueur>();
	
	public void addObserverGrille(Jeu j) {
		jeu = j;
		
		listeJoueur.add(new Joueur(0,"YOU",1000));
		addJoueur();
		
		listeJoueur.add(new Joueur(1,12000));
		addJoueur();
		
		listeJoueur.add(new Joueur(2,12000));
		addJoueur();
		
		listeJoueur.add(new Joueur(3,12000));
		addJoueur();
		
		listeJoueur.add(new Joueur(4,12000));
		addJoueur();
		
		listeJoueur.add(new Joueur(5,12000));
		addJoueur();
		
		listeJoueur.add(new Joueur(6,12000));
		addJoueur();
	}
	
	public void addJoueur() {
		jeu.addJoueur(listeJoueur.get(listeJoueur.size()-1));
	}

	public boolean verifAssezArgent(int mise) {
		return listeJoueur.get(0).getsomme() >= mise;
	}

	public void afficheErreurMessage() {
		jeu.afficheMessageErreur();
	}

	public void afficheBoutonAction() {
		jeu.afficheBoutonAction();
	}
	
	

}
