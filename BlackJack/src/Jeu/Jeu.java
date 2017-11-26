package Jeu;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;

import javax.swing.JPanel;

import Constante.Constante;
import Jeu.Panel.Dialogue;
import Jeu.Panel.ListeJoueur;
import Jeu.Panel.Plateau;
import Model.Joueur;

public class Jeu extends JPanel implements Constante {

	private FrameJeu frameJeu;
	
	private Model.Jeu jeuCroupier;
	
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

		plateau.setBounds(135, 35, 940, 472);
		listeJoueur.setBounds(130, 530, 480, 200);
		dialogue.setBounds(630, 538, 480, 200);

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
		repaint();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondGeneral, 0, 0, 1224, 768, this);
		g.drawImage(cadre, 100, 20, 1000, 500, this);
		g.drawImage(cadre, 115, 530, 480, 200, this);
		g.drawImage(cadre, 610, 530, 480, 200, this);
		g.drawImage(fondPlateau, 135, 35, 940, 483, this);
		
		dessinerCarteJoueur(g);
		dessinerConnectionRouge(g);
		dessinerConnectionVert(g);
	}

	
	private void dessinerCarteJoueur(Graphics g) {
		for (int i = 0; i < listeJoueur.getListeJoueur().size(); i++) {
			if (listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				for (int j = 0; j < listeJoueur.getListeJoueur().get(i).getJeux().size(); j++) {
					Model.Jeu jeu = listeJoueur.getListeJoueur().get(i).getJeux().get(j);
					for(int c = 0 ; c < jeu.getJeuCartes().size();c++) {
						g.drawImage(cartes[jeu.getJeuCouleurs().get(c).getValue()-1][jeu.getJeuCartes().get(c).getValue()-1],540 + 30*c, 340 - 60 * j, 40, 60, this);
					}
				}
			}
		}
		
		if(jeuCroupier != null && jeuCroupier.getJeuCartes().isEmpty())
			for (int j = 0; j < 5; j++)
				g.drawImage(carteRecto,480 + 60*j, 83, 40, 60, this);
		else if(jeuCroupier != null){
			for (int j = 0; j < 5; j++)
				g.drawImage(cartes[jeuCroupier.getJeuCouleurs().get(j).getValue()-1][jeuCroupier.getJeuCartes().get(j).getValue()-1],600 + 20*j, 90 , 40, 60, this);
		}
	}

	private void dessinerConnectionVert(Graphics g) {
		g.setColor(Color.GREEN);
		g.fillOval(620, 440, 20, 20);
        
		for (int i = 0; i < listeJoueur.getListeJoueur().size(); i++) {
			if (!listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				if(i==1) {
					g.fillOval(200, 215, 20, 20);
				}
				else if(i==2) {
					g.fillOval(315, 290, 20, 20);
				}
				else if(i==3) {
					g.fillOval(460, 370, 20, 20);
				}
				else if(i==4) {
					g.fillOval(780, 365, 20, 20);
				}
				else if(i==5) {
					g.fillOval(925, 290, 20, 20);
				}
				else if(i==6) {
					g.fillOval(1040, 215, 20, 20);
				}
			}
		}
	}

	private void dessinerConnectionRouge(Graphics g) {
		g.setColor(Color.RED);
		g.fillOval(200, 215, 20, 20);
		g.fillOval(315, 290, 20, 20);
		g.fillOval(460, 370, 20, 20);
		g.fillOval(780, 365, 20, 20);
		g.fillOval(925, 290, 20, 20);
		g.fillOval(1040, 215, 20, 20);
	}

	
	public void reset() {
		listeJoueur.removeJoueurs();
	}

	public void donneJeuCroupier(Model.Jeu jeu_croupier) {
		jeuCroupier = jeu_croupier;
	}
}
