package Panel.Menu;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;

import Constante.Constante;


public class Bouton extends JButton implements Constante{

	/**
	 * Constructeur d'un Bouton
	 * @param j JPanel
	 * @param Commande String 
	 */
	public Bouton(JPanel j, String Commande) {
		setBorderPainted(false);
		setOpaque(true);
		
		this.setBorder(BorderFactory.createEmptyBorder());
		this.setOpaque(false);
		this.setFont(new Font("Purisa",Font.BOLD,40));
		this.setText(Commande);
		
		this.setBackground(transparent);
		this.setForeground(Color.white);
		
		this.setActionCommand(Commande);
		this.addActionListener((ActionListener) j);
		this.setAlignmentX(Component.CENTER_ALIGNMENT);
	}
	
	public Bouton(JPanel j, String commande,Color c) {
		this(j,commande);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
}
