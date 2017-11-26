package Jeu;

import java.util.ArrayList;

import Model.Joueur;
import Model.Plateau;

public class ModelJeu {

	private int id = 0;
	private Jeu jeu;
	private Plateau plateau;
	
	public void addObserverGrille(Jeu j) {
		jeu = j;
		
		//AJOUTER JOUEUR
	}
	
	public boolean verifAssezArgent(int mise) {
		return plateau.getListJoueur().get(id).getsomme() >= mise;
	}

	public void afficheErreurMessage(String msg) {
		jeu.afficheErreur(msg);
	}

	public void afficheBoutonAction() {
		jeu.afficheBoutonAction();
	}

	public void setPlateau(Plateau p) {
		jeu.reset();
		plateau = p;
		majNom();
		miseAjourInterface();
	}

	private void majNom() {
		for(int i  = 0 ; i < plateau.getListJoueur().size();i++) {
			if(plateau.getListJoueur().get(i).getid() == id) {
				plateau.getListJoueur().get(i).setNom("YOU");
				plateau.getListJoueur().get(i).setJoueurPrincipal(true);
			}else {
				plateau.getListJoueur().get(i).setNom("Joueur" + plateau.getListJoueur().get(i).getid());
				plateau.getListJoueur().get(i).setJoueurPrincipal(false);
			}
		}
	}

	private void miseAjourInterface() {
		for(int i  = 0 ; i < plateau.getListJoueur().size();i++) {
			jeu.addJoueur(plateau.getListJoueur().get(i));
		}
	}
	
	

}
