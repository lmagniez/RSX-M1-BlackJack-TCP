package Panel.Jeu;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JPanel;

import Constante.Constante;
import Jeu.Jeu;
import Panel.JeuClient.FrameJeu;
import Panel.Menu.Bouton;
import Reseau.Connection;

public class Plateau extends JPanel implements ActionListener, Constante{

	Jeu jeu;
	private BoutonPlateau mise = new BoutonPlateau(this, "Mise");
	private BoutonPlateau tirer = new BoutonPlateau(this, "Tirer");
	private BoutonPlateau rester = new BoutonPlateau(this, "Rester");
	private BoutonPlateau doubler = new BoutonPlateau(this, "Doubler");
	private BoutonPlateau splitter = new BoutonPlateau(this, "Split");
	private BoutonPlateau abandonner = new BoutonPlateau(this, "Leave");

	private String errorMsg = "";
	private String[] miseStrings = {"50000","10000", "5000","1000","500","100","50","10"};
	private JComboBox miseList = new JComboBox(miseStrings);
	
	public Plateau(Jeu jeu) {
		this.jeu = jeu;
		this.setBackground(Color.BLUE);
		
		miseList.setSelectedIndex(miseStrings.length-1);
		miseList.addActionListener(this);
		
		init();
		activeeMise();
	}
	
	public void init() {
		this.setLayout(null);
		
		this.add(mise);
		this.add(tirer);
		this.add(rester);
		this.add(doubler);
		this.add(splitter);
		this.add(abandonner);
		this.add(miseList);
		
		miseList.setBounds(10, 445, 100, 30);
		
		mise.setBounds(100+20, 445, 90, 25);
		
		tirer.setBounds(800, 410, 90, 30);
		rester.setBounds(800, 445, 90, 30);
		doubler.setBounds(800 - 90 - 10 , 445, 90, 30);
		splitter.setBounds(800 - 90*2 - 10*2, 445, 90, 30);
		abandonner.setBounds(800 - 90*3 - 10*3, 445, 90, 30);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fondPlateau, 0, 0,900, 610, this);
		
		g.setColor(Color.WHITE);
		g.setFont(new Font("verdana", Font.BOLD, 20));
		g.drawString(errorMsg, 20, 430);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("Mise")) {
			jeu.controllerJeu.mise(Integer.parseInt(miseStrings[miseList.getSelectedIndex()]));
		}else if(e.getActionCommand().equals("Tirer")) {
			activeeMise();
		}else if(e.getActionCommand().equals("Rester")) {
			activeeMise();
		}else if(e.getActionCommand().equals("Doubler")) {
			activeeMise();
		}else if(e.getActionCommand().equals("Split")) {
			activeeMise();
		}else if(e.getActionCommand().equals("Leave")) {
			activeeMise();
		}
	}

	/*
	 * Active et desactive les boutons
	 */
	public void desactiveMise() {
		mise.setEnabled(false);
		
		tirer.setEnabled(true);
		rester.setEnabled(true);
		doubler.setEnabled(true);
		splitter.setEnabled(true);
		abandonner.setEnabled(true);
	}
	
	public void desactiveAll() {
		mise.setEnabled(false);
		tirer.setEnabled(false);
		rester.setEnabled(false);
		doubler.setEnabled(false);
		splitter.setEnabled(false);
		abandonner.setEnabled(false);
	}
	
	public void activeeMise() {
		mise.setEnabled(true);
		
		tirer.setEnabled(false);
		rester.setEnabled(false);
		doubler.setEnabled(false);
		splitter.setEnabled(false);
		abandonner.setEnabled(false);
	}

	
	/*
	 * Message Erreur et retour mise
	 */
	public void setMessageErreur() {
		errorMsg = "Manque d'argent";
		this.repaint();
		this.activeeMise();
	}

	public void afficheBoutonAction() {
		errorMsg = "";
		this.repaint();
		this.desactiveMise();
	}
	
}
