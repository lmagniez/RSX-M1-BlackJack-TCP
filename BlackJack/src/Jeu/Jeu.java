package Jeu;

import javax.swing.JPanel;

import Panel.Jeu.ListeJoueur;
import Panel.Jeu.Plateau;
import Panel.JeuClient.FrameJeu;

public class Jeu extends JPanel{

	private FrameJeu frameJeu;
	private ControllerJeu controllerJeu;
	
	Plateau plateau = new Plateau(this);
	ListeJoueur listeJoueur = new ListeJoueur(this);
	
	public Jeu(FrameJeu frameJeu, ControllerJeu controllerJeu) {
		this.frameJeu = frameJeu;
		this.controllerJeu = controllerJeu;	
	}

	public void init() {
		setLayout(null);

		plateau.setBounds(0, 0, 700, 500);
		listeJoueur.setBounds(700, 0, 300, 500);
		
		this.add(plateau);
		this.add(listeJoueur);
	}
}
