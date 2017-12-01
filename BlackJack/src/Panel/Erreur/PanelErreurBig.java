package Panel.Erreur;

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
		g.drawImage(fond, 0, -100, 1224,1000, this);
	}
}
