package Panel.Erreur;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;

import Constante.Constante;
import Panel.Menu.FrameJeuMenu;

public class PanelErreurBig extends JPanel implements Constante {

	private FrameJeuMenu f;
	private String erreur;
	
	public PanelErreurBig(String erreur) {
		this.erreur = erreur;
		this.repaint();
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondDeco, -80, -20, 1366,768, this);
		g.setColor(Color.white);
		g.setFont(new Font("Purisa", Font.BOLD, 60));
		g.drawString(erreur, 180, 600);
	}

	public void setErreur(String s) {
		erreur = s==null ? "Erreur Connection Serveur" : "Une personne c'est connectée avant vous";
	}
}
