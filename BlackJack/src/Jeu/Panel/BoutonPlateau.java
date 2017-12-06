package Jeu.Panel;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;

import Constante.Constante;


public class BoutonPlateau extends JButton implements Constante{
	
	/**
	 * Constructeur d'un Bouton
	 * @param j JPanel
	 * @param Commande String 
	 */
	public BoutonPlateau(JPanel j, String Commande) {
		setBorderPainted(false);
		setOpaque(true);
		
		this.setBorder(BorderFactory.createEmptyBorder());
		this.setOpaque(false);
		this.setFont(new Font("Purisa",Font.BOLD,30));
		this.setText(Commande);
		
		this.setBackground(transparent);
		this.setForeground(Color.white);
		
		this.setActionCommand(Commande);
		this.addActionListener((ActionListener) j);
		this.setAlignmentX(Component.CENTER_ALIGNMENT);
	}
	
	public BoutonPlateau(JPanel j, String commande,Color c) {
		this(j,commande);
		this.setForeground(c);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
}
