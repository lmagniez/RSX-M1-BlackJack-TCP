package Jeu.Panel;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JPanel;

import Constante.Constante;
import Jeu.FrameJeu;
import Jeu.Jeu;
import Panel.Menu.Bouton;
import Reseau.Connection;

public class Plateau extends JPanel implements ActionListener, Constante{

	Jeu jeu;
	
	private BoutonPlateau mise = new BoutonPlateau(this, "Mise");
	private BoutonPlateau tirer = new BoutonPlateau(this, "Tirer");
	private BoutonPlateau rester = new BoutonPlateau(this, "Rester");
	private BoutonPlateau doubler = new BoutonPlateau(this, "Doubler");
	private BoutonPlateau splitter = new BoutonPlateau(this, "Split");
	private BoutonPlateau abandonner = new BoutonPlateau(this, "Stop");

	private String errorMsg = "";
	private String[] miseStrings = {"1000","500","100","50","25","10","5"};
	private JComboBox miseList = new JComboBox(miseStrings);
	
	public Plateau(Jeu jeu) {
		this.jeu = jeu;
		this.setOpaque(false);
		miseList.setSelectedIndex(miseStrings.length-1);
		miseList.addActionListener(this);
		
		init();
		activeeMise();
	}
	
	public Plateau() {
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
		
		miseList.setBounds(10, 420, 100, 30);
		
		mise.setBounds(100+20, 420, 90, 25);
		
		tirer.setBounds(570, 380, 100, 30);
		splitter.setBounds(550, 420, 150, 30);
		
		doubler.setBounds(680, 380, 150, 30);
		rester.setBounds(700, 420, 120, 30);
		
		abandonner.setBounds(820, 420, 120, 30);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("Mise")) {
			jeu.controllerJeu.mise(Integer.parseInt(miseStrings[miseList.getSelectedIndex()]));
		}else if(e.getActionCommand().equals("Tirer")) {
			jeu.controllerJeu.demandeCarte();
		}else if(e.getActionCommand().equals("Rester")) {
			jeu.controllerJeu.rester();
		}else if(e.getActionCommand().equals("Doubler")) {
			jeu.controllerJeu.demandeDouble();
		}else if(e.getActionCommand().equals("Split")) {
			jeu.controllerJeu.demandeSplit();
		}else if(e.getActionCommand().equals("Stop")) {
			jeu.controllerJeu.demandeQuitter();
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

	public void afficheBoutonAction() {
		errorMsg = "";
		this.repaint();
		this.desactiveMise();
	}
	
}
