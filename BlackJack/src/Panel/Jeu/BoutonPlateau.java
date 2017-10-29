package Panel.Jeu;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;


public class BoutonPlateau extends JButton{
	
	/**
	 * Constructeur d'un Bouton
	 * @param j JPanel
	 * @param Commande String 
	 */
	public BoutonPlateau(JPanel j, String Commande) {
		setBorderPainted(false);
		setOpaque(true);
		this.setBorder(BorderFactory.createEmptyBorder());
		this.setOpaque(true);
		this.setFont(new Font("verdana",Font.BOLD,20));
		this.setText(Commande);
		this.setBackground(new Color(136,36,33));
		this.setForeground(new Color(240,183,74));
		this.setActionCommand(Commande);
		this.addActionListener((ActionListener) j);
		this.setAlignmentX(Component.CENTER_ALIGNMENT);
	}
	
	public BoutonPlateau(JPanel j, String commande,Color c) {
		this(j,commande);
		this.setBackground(c);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
}
