package Panel.Jeu;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;

import Constante.Constante;
import Jeu.Jeu;
import Panel.Menu.Bouton;

public class Plateau extends JPanel implements ActionListener, Constante{

	Jeu jeu;

	private BoutonPlateau tirer = new BoutonPlateau(this, "Tirer Une Carte");
	private BoutonPlateau rester = new BoutonPlateau(this, "Rester");
	private BoutonPlateau doubler = new BoutonPlateau(this, "Doubler");
	private BoutonPlateau splitter = new BoutonPlateau(this, "Splitter");
	private BoutonPlateau assurance = new BoutonPlateau(this, "Assurance");
	private BoutonPlateau abandonner = new BoutonPlateau(this, "Abandonner");
	
	
	public Plateau(Jeu jeu) {
		this.jeu = jeu;
		this.setBackground(Color.BLUE);
		init();
	}
	
	public void init() {
		this.setLayout(null);
		
		this.add(tirer);
		this.add(rester);
		this.add(doubler);
		this.add(splitter);
		this.add(assurance);
		this.add(abandonner);
		
		tirer.setBounds(30, 410, 200, 30);
		rester.setBounds(250, 410, 200, 30);
		doubler.setBounds(470, 410, 200, 30);
		
		
		
		splitter.setBounds(30, 445, 200, 30);
		assurance.setBounds(250, 445, 200, 30);
		abandonner.setBounds(470, 445, 200, 30);
		
		
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondPlateau, 0, 0,700, 500, this);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
}
