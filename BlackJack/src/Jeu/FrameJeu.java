package Jeu;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Model.Plateau;
import Panel.Erreur.PanelErreurBig;
import Reseau.BlackJackClient;

public class FrameJeu extends JFrame{

	private PanelErreurBig erreurBig = new PanelErreurBig("");
	private Jeu j;
	private ModelJeu modelJeux;
	private ControllerJeu controllerJeu;
	
	/**
	 * Constructeur de la Frame de jeu
	 * @param s
	 * @param newJ
	 */
	public FrameJeu(BlackJackClient newJ){
		this.setTitle("BlackJack");
		this.setSize(1224,768);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		this.setFocusable(false);
		this.creerJeu(newJ);
		this.setVisible(true);
	}
	
	/**
	 * Creer le jeu 
	 * @param newJ
	 */
	private void creerJeu(BlackJackClient joueur) {
		modelJeux = new ModelJeu();
		controllerJeu = new ControllerJeu(joueur,modelJeux);
		j = new Jeu(this,controllerJeu);
		modelJeux.addObserverGrille(j);		
		j.init();
		swapEcran(j);
	}

	public void swapEcran(JPanel j){
		getContentPane().removeAll();
		getContentPane().repaint();
		this.add(j);
		validate();
	}

	public void setPlateau(Plateau p) {
		modelJeux.setPlateau(p);
	}

	public void addDialogue(String message) {
		if(message.length()<4)return;
		modelJeux.afficheErreurMessage(message);
	}

	public void showErreurScreen(String s) {
		erreurBig.setErreur(s);
		swapEcran(erreurBig);
	}
}
