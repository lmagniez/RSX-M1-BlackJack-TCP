package Panel.Erreur;

import java.awt.Graphics;

import javax.swing.JPanel;

import Constante.Constante;
import Panel.Menu.FrameJeuMenu;

public class PanelErreur extends JPanel implements Constante {

	private FrameJeuMenu f;
	private String erreur;
	
	public PanelErreur(String erreur) {
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
}
