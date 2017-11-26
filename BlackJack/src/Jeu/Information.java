package Jeu;

import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JPanel;

import Model.Joueur;

public class Information extends JPanel{

	Jeu jeu;
	
	public Information(Jeu jeu) {
		jeu = jeu;
		this.setOpaque(false);
		this.setLayout(null);
	}

	public void addBoutonMiseDisplay(Joueur joueur, int num) {
		if(joueur.isJoueurPrincipal()) {
			int[] pos = positionXYBoutonMise(num);
			
			JButton bouton = new JButton();
			bouton.setBackground(Color.BLUE);
			bouton.setText("M"+num);
			bouton.setBounds(pos[0],pos[1],50,30);
			this.add(bouton);
		}
	}

	public void addBoutonJeuDisplay(Joueur joueur, int num) {
		if(!joueur.isJoueurPrincipal()) {
			int[] pos = positionXYBoutonJeu(num);
			
			JButton bouton = new JButton();
			bouton.setBackground(Color.YELLOW);

			bouton.setText("C"+num);
			bouton.setBounds(pos[0],pos[1],50,30);
			this.add(bouton);
		}
	}

	private int[] positionXYBoutonMise(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {160,150};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {275,240};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {420,225};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {740,300};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {885,240};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {1000,150};
			return tab;
		}
		return null;
	}
	
	private int[] positionXYBoutonJeu(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {160,180};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {275,270};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {420,255};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {740,330};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {885,270};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {1000,180};
			return tab;
		}
		return null;
	}
	
	
	
}
