package Panel.Erreur;

import java.awt.Graphics;

import javax.swing.JPanel;

import Constante.Constante;
import Panel.Menu.FrameJeuMenu;

public class PanelErreur extends JPanel implements Constante {

	private FrameJeuMenu f;
	private String erreur;
	
	public PanelErreur(String erreur) {
		this.erreur = erreur;
		this.repaint();
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		//g.drawImage(fond, 0, -50, 400, 550, this);
		//g.setColor(or);
		//g.setFont(new Font("verdana", Font.BOLD, 15));
		//g.drawString(erreur, 50, 250);
	}
}
