package Jeu;

import java.util.ArrayList;

import Model.EtatJoueur;
import Model.Joueur;
import Model.Plateau;

public class ModelJeu {

	private Jeu jeu;
	private Plateau plateau = new Plateau();
	
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
		if(msg!=null && (msg.contains("pas splitter") || msg.contains("pas doubler")))jeu.activeBouton();
		jeu.afficheErreur(msg);
	}

	public void afficheBoutonAction() {
		jeu.afficheBoutonAction();
	}

	public void setPlateau(Plateau p) {
		jeu.reset();
		plateau.setId_joueur(p.getId_joueur());
		plateau.setDialogue(p.getDialogue());
		plateau.setNb_joueur(p.getNb_joueur());
		plateau.setTour_id_jeu(p.getTour_id_jeu());
		plateau.setTour_id_joueur(p.getTour_id_joueur());
		plateau.setTour_started(p.getTour_started());
		plateau.setJeu_croupier(p.getJeu_croupier());
		plateau.setListJoueur(p.getListJoueur());
		
		jeu.voidRenitPos();
		jeu.reinitBoutonInformation();

		jeu.tourAndIDJeu(plateau.getTour_id_jeu(),plateau.getId_joueur()==plateau.getTour_id_joueur());
		
		majNom();
		miseAjourInterface();
		gestionBouton();
		afficheErreurMessage(plateau.getDialogue());
		gestionLoader();
	}

	private int recupPositionArrayList() {
		for(int i = 0;i<plateau.getListJoueur().size();i++) {
			if(plateau.getListJoueur().get(i).getId_joueur() == plateau.getId_joueur() )
				return i;
		}
		return -1;
	}
	
	private void gestionLoader() {
		if(plateau.getListJoueur().get(recupPositionArrayList()).getEtat() == EtatJoueur.BETTING) {
			jeu.eneleverLoader();
		}
		else if(plateau.getListJoueur().get(recupPositionArrayList()).getEtat() != EtatJoueur.BETTING) {
			if(plateau.getTour_id_joueur() == plateau.getId_joueur())
				jeu.eneleverLoader();
			else {
				jeu.desactiveAllBouton();
				jeu.afficherLoader();
			}
		}
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
					if(plateau.getTour_id_joueur() == plateau.getId_joueur()) {
						jeu.activeBouton();
						return;
					}
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
