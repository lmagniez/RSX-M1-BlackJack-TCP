package Panel.Connect;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Constante.Constante;
import Jeu.FrameJeu;
import Panel.Erreur.PanelErreur;
import Panel.Menu.Bouton;
import Panel.Menu.FrameJeuMenu;
import Reseau.BlackJackClient;

public class Identification extends JPanel implements Constante {

	private FrameJeuMenu f;
	private ListeServeur listeServeur;
	
	/**
	 * Constructeur de Identification
	 * @param t int
	 * @param fen FrameJeuMenu
	 */
	public Identification(int t,FrameJeuMenu fen) {
		f=fen;
		listeServeur = new ListeServeur(fen);
		creerlayout();
	}
	
	/**
	 * Creer le layout du panel
	 */
	private void creerlayout() {
		setLayout(null);
		listeServeur.setBounds(25, 120, 350, 370);
		this.add(listeServeur);
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondListe, 0, 0, 400, 500, this);
	}

	public ListeServeur getListeServeur() {
		return listeServeur;
	}

	public void afficheEcranErreur(String erreur) {
		PanelErreur afficheErreur = new PanelErreur(erreur);
		f.swapEcran(afficheErreur);
	}
	
	
}
