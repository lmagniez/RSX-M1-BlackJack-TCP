package Jeu;

import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;

import Constante.Constante;
import Jeu.Panel.Dialogue;
import Jeu.Panel.ListeJoueur;
import Jeu.Panel.Plateau;
import Model.Joueur;

public class Jeu extends JPanel implements Constante{

	private FrameJeu frameJeu;
	public ControllerJeu controllerJeu;
	private Dialogue dialogue = new Dialogue();
	
	public Plateau plateau = new Plateau(this);
	public ListeJoueur listeJoueur = new ListeJoueur(this);
	
	public Jeu(FrameJeu frameJeu, ControllerJeu controllerJeu) {
		this.frameJeu = frameJeu;
		this.controllerJeu = controllerJeu;	
	}

	public void init() {
		setLayout(null);

		plateau.setBounds(135,35,940,472);
		listeJoueur.setBounds(130,530, 480,200);
		dialogue.setBounds(630,538, 480,200);
		
		
		this.add(plateau);
		this.add(dialogue);
		this.add(listeJoueur);
	}

	public void afficheErreur(String msg) {
		dialogue.setText(msg);
	}

	public void afficheBoutonAction() {
		plateau.afficheBoutonAction();
	}

	public void addJoueur(Joueur joueur) {
		listeJoueur.addJoueur(joueur);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondGeneral,0,0, 1224,768, this);
		g.drawImage(cadre,100,20, 1000,500, this);
		g.drawImage(cadre,115,530, 480,200, this);
		g.drawImage(cadre,610,530, 480,200, this);
		g.drawImage(fondPlateau,135,35,940,472, this);
	}
}
