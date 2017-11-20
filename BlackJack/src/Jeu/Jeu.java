package Jeu;

import javax.swing.JPanel;

import Model.Joueur;
import Panel.Jeu.ListeJoueur;
import Panel.Jeu.Plateau;
import Panel.JeuClient.FrameJeu;

public class Jeu extends JPanel{

	private FrameJeu frameJeu;
	public ControllerJeu controllerJeu;
	
	public Plateau plateau = new Plateau(this);
	public ListeJoueur listeJoueur = new ListeJoueur(this);
	
	public Jeu(FrameJeu frameJeu, ControllerJeu controllerJeu) {
		this.frameJeu = frameJeu;
		this.controllerJeu = controllerJeu;	
	}

	public void init() {
		setLayout(null);

		plateau.setBounds(0, 0, 900, 500);
		listeJoueur.setBounds(900, 0, 300, 500);
		
		this.add(plateau);
		this.add(listeJoueur);
	}

	public void afficheMessageErreur() {
		plateau.setMessageErreur();
	}

	public void afficheBoutonAction() {
		plateau.afficheBoutonAction();
	}

	public void addJoueur(Joueur joueur) {
		listeJoueur.addJoueur(joueur);
	}
}
