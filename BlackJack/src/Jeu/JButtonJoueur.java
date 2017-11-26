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
		
		button = new JButton(mise ? jetonIcon : jeuxIcon);

		button.setBorderPainted(false); 
		button.setContentAreaFilled(false); 
		button.setFocusPainted(false); 
		button.setOpaque(false);
		
		if(mise)button.setToolTipText("<html>" + "<p style=\"text-align: center;\">"+joueur.getNom()+"</p> <br>"+"Mise: "+joueur.getMise_actuelle() + "</html>");
		else {
			String texte = "<html>"+ "<p style=\"text-align: center;\">"+ joueur.getNom()+"</p> <br>";
			for(int i = 0 ; i < joueur.getJeux().size();i++) {
				texte += "coucou \n";
			}
			texte += "</html>";
			button.setToolTipText(texte);
		}
		j = joueur;
	}

	public JButton getButton() {
		return button;
	}

	public void setButton(JButton button) {
		this.button = button;
	}
	
	

}
