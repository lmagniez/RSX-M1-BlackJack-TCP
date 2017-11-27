package Jeu;

import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JPanel;

import Constante.Constante;
import Model.Joueur;

public class Information extends JPanel implements Constante{

	Jeu jeu;
	
	public Information(Jeu jeu) {
		jeu = jeu;
		this.setOpaque(false);
		this.setLayout(null);
	}

	public void addBoutonMiseDisplay(Joueur joueur, int num) {
		if(!joueur.isJoueurPrincipal() && joueur.getMise_actuelle() != 0) {
			int[] pos = positionXYBoutonMise(num-1);
			JButtonJoueur Jbouton = new JButtonJoueur(joueur,true);
			JButton bouton = Jbouton.getButton();
			bouton.setBounds(pos[0],pos[1],60,30);
			this.add(bouton);
			repaint();
		}else if(joueur.getMise_actuelle() != 0){
			JButtonJoueur Jbouton = new JButtonJoueur(joueur,true);
			JButton bouton = Jbouton.getButton();
			bouton.setBounds(440,370,60,30);
			this.add(bouton);
			repaint();
		}
	}

	public void addBoutonJeuDisplay(Joueur joueur, int num) {
		if(!joueur.isJoueurPrincipal() && joueur.getJeux().size()>1) {
			int[] pos = positionXYBoutonJeu(num-1);
			
			JButtonJoueur Jbouton = new JButtonJoueur(joueur,false);
			JButton bouton = Jbouton.getButton();
			
			bouton.setBounds(pos[0],pos[1],60,30);
			this.add(bouton);
			repaint();
		}
	}

	private int[] positionXYBoutonMise(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {20,160};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {137,230};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {283,310};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {598,310};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {744,230};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {860,130};
			return tab;
		}
		return null;
	}
	
	private int[] positionXYBoutonJeu(int numJoueur) {		
		if(numJoueur==1){
			int[] tab = {20,130};
			return tab;
		}
		else if(numJoueur==2) {
			int[] tab = {137,200};
			return tab;
		}
		else if(numJoueur==3) {
			int[] tab = {283,280};
			return tab;
		}
		else if(numJoueur==4) {
			int[] tab = {598,280};
			return tab;
		}
		else if(numJoueur==5) {
			int[] tab = {744,200};
			return tab;
		}
		else if(numJoueur==6) {
			int[] tab = {860,130};
			return tab;
		}
		return null;
	}
	
	
	
}
