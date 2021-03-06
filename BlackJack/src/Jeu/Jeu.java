package Jeu;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;

import javax.swing.JLabel;
import javax.swing.JPanel;

import Constante.Constante;
import Jeu.Panel.Dialogue;
import Jeu.Panel.ListeJoueur;
import Jeu.Panel.Plateau;
import Model.EtatJeu;
import Model.Joueur;

public class Jeu extends JPanel implements Constante {

	private int idJeu = 0;
	private boolean tourJoueurPrincipal = false;

	private FrameJeu frameJeu;
	
	private Model.Jeu jeuCroupier;
	
	public ControllerJeu controllerJeu;
	private Dialogue dialogue = new Dialogue();

	public Plateau plateau = new Plateau(this);
	public ListeJoueur listeJoueur = new ListeJoueur(this);

	public Information info = new Information(this);
	
	private JLabel loaderLabel = new JLabel(loader) ;
	
	public Jeu(FrameJeu frameJeu, ControllerJeu controllerJeu) {
		this.frameJeu = frameJeu;
		this.controllerJeu = controllerJeu;
	}

	public void init() {
		setLayout(null);

		
		plateau.setBounds(135, 35, 940, 472);
		listeJoueur.setBounds(130, 530, 480, 200);
		dialogue.setBounds(630, 530, 450, 200);
		info.setBounds(135, 35, 940, 472);
		
		this.add(plateau);
		this.add(dialogue);
		this.add(listeJoueur);
		this.add(info);
		
	}
	
	public void afficherLoader() {
		loaderLabel.setBounds(500, 370, 200, 200);
		this.add(loaderLabel);
		this.repaint();
	}
	
	public void eneleverLoader() {
		if(this.getComponentCount()>4) {
			this.remove(this.getComponentCount()-1);
			this.repaint();
		}
	}

	public void afficheErreur(String msg) {
		dialogue.setText(msg);
	}

	public void afficheBoutonAction() {
		plateau.afficheBoutonAction();
	}

	public void voidRenitPos() {
		info.reinitPosJoueur();
	}
	
	public void addJoueur(Joueur joueur) {
		listeJoueur.addJoueur(joueur);
		info.addBoutonMiseDisplay(joueur,listeJoueur.getListeJoueur().size());
		info.addBoutonJeuDisplay(joueur,listeJoueur.getListeJoueur().size());
		repaint();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondGeneral, 0, 0, 1224, 768, this);
		//g.drawImage(cadre, 100, 20, 1000, 500, this);
		//g.drawImage(cadre, 115, 530, 480, 200, this);
		//g.drawImage(cadre, 610, 530, 480, 200, this);
		g.drawImage(fondPlateau, 135, 35, 940, 610, this);
		
		dessinerCarteJoueur(g);
		dessinerConnectionRouge(g);
		dessinerConnectionVert(g);
	}

	int posJoueur = 1;
	
	private void dessinerCarteJoueur(Graphics g) {	
		posJoueur=1;
		g.setColor(Color.WHITE);
		g.setFont(new Font("verdana", Font.BOLD, 10));
		for (int i = 0; i < listeJoueur.getListeJoueur().size(); i++) {
			if (listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				for (int j = 0; j < listeJoueur.getListeJoueur().get(i).getJeux().size(); j++) {
					Model.Jeu jeu = listeJoueur.getListeJoueur().get(i).getJeux().get(j);
					
					if(tourJoueurPrincipal && idJeu == j) {
						g.setFont(new Font("verdana", Font.BOLD, 20));
						g.drawString("⇨", 520, 380 - 60 * j);
						g.setFont(new Font("verdana", Font.BOLD, 10));
					}
					
					for(int c = 0 ; c < jeu.getJeuCartes().size();c++) {
						g.drawImage(cartes[jeu.getJeuCouleurs().get(c).getValue()-1][jeu.getJeuCartes().get(c).getValue()-1],540 + 30*c, 340 - 60 * j, 40, 60, this);
					}
				}
				g.drawString("Value: "+getValueJeux(i), 560, 470);
				
			}else {
				for (int j = 0; j < listeJoueur.getListeJoueur().get(i).getJeux().size(); j++) {
					int [] positionJeu = positionXYJeu(posJoueur);
					
					g.drawString("NBJeux: "+listeJoueur.getListeJoueur().get(i).getJeux().size(), positionJeu[0], positionJeu[1]);
					g.drawString("Value:"+getValueJeux(i), positionJeu[0], positionJeu[1]+30);
					
					if(listeJoueur.getListeJoueur().get(i).getJeux().get(j).getEtat() != EtatJeu.PERDU) {
						Model.Jeu jeu = listeJoueur.getListeJoueur().get(i).getJeux().get(j);
						
						int [] positionCarte = positionXYCarte(posJoueur);
						for(int c = 0 ; c < jeu.getJeuCartes().size();c++) {
							g.drawImage(cartes[jeu.getJeuCouleurs().get(c).getValue()-1][jeu.getJeuCartes().get(c).getValue()-1],positionCarte[0] + 30*c, positionCarte[1] - 60 * j, 40, 60, this);
						}
					}
				}
				 posJoueur++;
			}
		}
		
		if(jeuCroupier != null && jeuCroupier.getJeuCartes().isEmpty())
			for (int j = 0; j < 5; j++)
				g.drawImage(carteRecto,480 + 60*j, 85, 40, 60, this);
		else if(jeuCroupier != null){
			for (int j = 0; j < jeuCroupier.getJeuCouleurs().size(); j++)
				g.drawImage(cartes[jeuCroupier.getJeuCouleurs().get(j).getValue()-1][jeuCroupier.getJeuCartes().get(j).getValue()-1],480 + 60*j, 85, 40, 60, this);
		}
	}

	private String getValueJeux(int numJoueur) {
		String value ="";
		for (int j = 0; j < listeJoueur.getListeJoueur().get(numJoueur).getJeux().size(); j++) {
			value += listeJoueur.getListeJoueur().get(numJoueur).getJeux().get(j).getValue();
			if(j+1 != listeJoueur.getListeJoueur().get(numJoueur).getJeux().size() )
				value+=" - ";
		}
		return value;
	}

	private void dessinerConnectionVert(Graphics g) {
		g.setColor(Color.GREEN);
		g.fillOval(620, 440, 20, 20);

		posJoueur = 1;
		
		for (int i = 0; i < listeJoueur.getListeJoueur().size(); i++) {
			if (!listeJoueur.getListeJoueur().get(i).isJoueurPrincipal()) {
				int [] tab = positionXYCercle(posJoueur);
				g.fillOval(tab[0], tab[1], 20, 20);
				posJoueur++;
			}
		}
	}

	private void dessinerConnectionRouge(Graphics g) {
		g.setColor(Color.RED);
		for (int i = 1; i < 7; i++) {
				int [] tab = positionXYCercle(i);
				g.fillOval(tab[0], tab[1], 20, 20);
		}
	}

	
	public void reset() {
		listeJoueur.removeJoueurs();
	}

	public void donneJeuCroupier(Model.Jeu jeu_croupier) {
		jeuCroupier = jeu_croupier;
	}
	
	private int[] positionXYCercle(int numJoueur) {		
			if(numJoueur==1){
				int[] tab = {200,215};
				return tab;
			}
			else if(numJoueur==2) {
				int[] tab = {315,290};
				return tab;
			}
			else if(numJoueur==3) {
				int[] tab = {460,370};
				return tab;
			}
			else if(numJoueur==4) {
				int[] tab = {780,365};
				return tab;
			}
			else if(numJoueur==5) {
				int[] tab = {925,290};
				return tab;
			}
			else if(numJoueur==6) {
				int[] tab = {1040,215};
				return tab;
			}
			return null;
	}

	private int[] positionXYJeu(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {160,250};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {270,320};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {420,400};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {740,400};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {890,320};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {1020,215};
			return tab;
		}
		return null;
	}
	
	private int[] positionXYCarte(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {120,115};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {235,190};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {380,270};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {700,265};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {845,190};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {960,115};
			return tab;
		}
		return null;
}

	
	public void desactiveAllBouton() {
		plateau.desactiveAll();
	}

	public void activeBouton() {
		plateau.desactiveMise();
	}

	public void activeMise() {
		plateau.activeeMise();
	}

	public void reinitBoutonInformation() {
		info.removeAll();
	}

	
	public void tourAndIDJeu(int tour_id_jeu, boolean b) {
		idJeu = tour_id_jeu;
		tourJoueurPrincipal = b;
		repaint();
	}
	
	
}
