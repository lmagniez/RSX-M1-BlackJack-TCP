package Jeu;

import java.awt.Image;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;

import Constante.Constante;
import Model.Joueur;

public class JButtonJoueur implements Constante{

	private Joueur j ;
	private JButton button;
	
	public JButtonJoueur(Joueur joueur,boolean mise) {
		
		button = new JButton(mise ? getIconMise(joueur.getMise_actuelle()) : jeuxIcon);

		button.setBorderPainted(false); 
		button.setContentAreaFilled(false); 
		button.setFocusPainted(false); 
		button.setOpaque(false);
		
		if(mise)button.setToolTipText("<html>" + "<p style=\"text-align: center;\">"+joueur.getNom()+"</p> <br>"+"Mise: "+joueur.getMise_actuelle() + "</html>");
		else {
			String texte = "<html>"+ "<p style=\"text-align: center;\">"+ joueur.getNom()+"</p> <br>";
			for(int i = 0 ; i < joueur.getJeux().size();i++) {
				
			}
			texte += "</html>";
			button.setToolTipText(texte);
		}
		j = joueur;
	}

	private ImageIcon getIconMise(int mise) {
		switch(mise) {
			case 5:
				return jeton5;
			case 10:
				return jeton10;
			case 25:
				return jeton25;
			case 50:
				return jeton50;
			case 100:
				return jeton100;
			case 500:
				return jeton500;
			case 1000:
				return jeton1000;
		}
		return null;
	}

	public JButton getButton() {
		return button;
	}

	public void setButton(JButton button) {
		this.button = button;
	}
	
	

}
