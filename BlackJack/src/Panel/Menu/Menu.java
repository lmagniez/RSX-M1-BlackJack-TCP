package Panel.Menu;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GraphicsEnvironment;
import java.awt.List;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;

import Constante.Constante;
import Jeu.FrameJeu;
import Reseau.Connection;

public class Menu extends JPanel implements ActionListener,Constante{

	private FrameJeuMenu frame;
	private Bouton jouer=new Bouton(this,"Jouer");
	private Bouton quitter=new Bouton(this,"Quitter");
	
	/**
	 * Constructeur de Menu
	 * @param j FrameJeuMenu
	 */
	public Menu(FrameJeuMenu j){
		frame=j;
		this.setPreferredSize(new Dimension(frame.getHeight(), frame.getWidth()));
		creerlayout();
	
	}
	
	/**
	 * Creer le layout du serveur
	 */
	private void creerlayout() {
		setLayout(null);
		jouer.setBounds(30, 400, 140, 50);
		quitter.setBounds(200, 400, 200, 50);
		this.add(jouer);
		this.add(quitter);
	}

	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawImage(fond,0, 0, 400, 500,this);
	}

	
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("Quitter")) 
			frame.dispose();
		else if (e.getActionCommand().equals("Jouer")) {
			frame.choosePort();			
		}		
	}
}
