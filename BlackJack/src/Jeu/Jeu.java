package Jeu;

import java.awt.Color;
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
	
	int nbJoueurCheck = 0;
	
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
		g.drawImage(fondPlateau,135,35,940,483, this);
		dessinerConnection(g);
	}

	private void dessinerConnection(Graphics g) {
		g.setColor(Color.GREEN);
		g.fillOval(620, 440, 20, 20);
		
		for(int i = 0 ; i < listeJoueur.getListeJoueur().size();i++) {
			if(!listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				switch(i) {
				case 1:
					g.fillOval(200, 215, 20, 20);
					break;
				case 2:
					g.fillOval(315, 290, 20, 20);	
					break;
				case 3:
					g.fillOval(460, 370, 20, 20);	
					break;
				case 4:
					g.fillOval(780, 365, 20, 20);
					break;
				case 5:
					g.fillOval(925, 290, 20, 20);	
					break;
				case 6:
					g.fillOval(1040, 215, 20, 20);	
					break;
				}
				nbJoueurCheck++;
			}
		}
		
		g.setColor(Color.RED);
		for(int i = nbJoueurCheck ; i < 7;i++) {
			if(!listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				switch(i) {
				case 1:
					g.fillOval(200, 215, 20, 20);
					break;
				case 2:
					g.fillOval(315, 290, 20, 20);	
					break;
				case 3:
					g.fillOval(460, 370, 20, 20);	
					break;
				case 4:
					g.fillOval(780, 365, 20, 20);
					break;
				case 5:
					g.fillOval(925, 290, 20, 20);	
					break;
				case 6:
					g.fillOval(1040, 215, 20, 20);	
					break;
				}
			}
		}
		nbJoueurCheck = 0;
	}

	public void reset() {
		listeJoueur.removeJoueurs();	
	}
}
