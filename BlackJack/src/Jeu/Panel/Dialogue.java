package Jeu.Panel;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import Constante.Constante;

public class Dialogue extends JPanel implements Constante{

	private JTextArea commande = new JTextArea();
	private int nbentre=0;
	
	public Dialogue() {
		commande.setEditable(false);
		commande.setFont(new Font("verdana", Font.BOLD, 12));
		commande.setForeground(Color.WHITE);
		commande.setOpaque(false);
		
		this.setBackground(Color.black);
		
		creerLayout();
	}
	
	private void creerLayout() {
		this.setLayout(null);
		commande.setBounds(4, 4,480,200);
		this.add(commande);
	}
	
	public void setText(String s) {
		if(nbentre==11){commande.setText("");nbentre=0;}
		commande.append(s + " \n");
		this.repaint();
		nbentre++;
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
}
