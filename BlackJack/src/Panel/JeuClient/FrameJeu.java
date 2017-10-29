package Panel.JeuClient;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Jeu.ControllerJeu;
import Jeu.Jeu;
import Jeu.ModelJeu;
import Reseau.BlackJackClient;

public class FrameJeu extends JFrame{

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
		this.setSize(1000,500);
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
	private void creerJeu(BlackJackClient newJ) {
		modelJeux = new ModelJeu();
		controllerJeu = new ControllerJeu(newJ);
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

	public void ecranFin(String string) {
		// TODO Auto-generated method stub
	}
}
