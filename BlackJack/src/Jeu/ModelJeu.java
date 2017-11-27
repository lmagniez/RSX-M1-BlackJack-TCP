package Jeu;

import java.util.ArrayList;

import Model.Joueur;
import Model.Plateau;

public class ModelJeu {

	private Jeu jeu;
	private Plateau plateau;
	
	public void addObserverGrille(Jeu j) {
		jeu = j;
	}
	
	public boolean verifAssezArgent(int mise) {
		for(Joueur j : plateau.getListJoueur()) {
			if(j.isJoueurPrincipal())
				return plateau.getListJoueur().get(plateau.getId_joueur()).getsomme() >= mise;
		}
		return false;
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
		gestionBouton();
		afficheErreurMessage(plateau.getDialogue());
	}

	private void gestionBouton() {
		for(int i = 0;i<plateau.getListJoueur().size();i++) {
			if(plateau.getListJoueur().get(i).getid() == plateau.getId_joueur()) {
				Joueur j = plateau.getListJoueur().get(i);
				switch(j.getEtat()) {
				case WAITING:
				case FINISHED: 
				case LOSE:
					jeu.desactiveAllBouton();
					break;
				case PLAYING:
					if(plateau.getTour_id_joueur() != plateau.getId_joueur()) {
						jeu.activeBouton();
						return;
					}
					jeu.activeBouton();
					break;
				case BETTING :
					jeu.activeMise();
					break;
				}
			}
		}
	}

	private void majNom() {
		for(int i  = 0 ; i < plateau.getListJoueur().size();i++) {
			if(plateau.getListJoueur().get(i).getid() == plateau.getId_joueur()) {
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
		jeu.donneJeuCroupier(plateau.getJeu_croupier());
	}

	public void desactiveAllBoutons() {
		jeu.desactiveAllBouton();
	}

}
