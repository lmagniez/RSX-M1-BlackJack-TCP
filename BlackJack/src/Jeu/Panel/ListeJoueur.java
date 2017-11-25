package Jeu.Panel;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import Constante.Constante;
import Jeu.Jeu;
import Model.Joueur;

public class ListeJoueur extends JPanel implements Constante{

	Jeu jeu;
	private JPanel list = new JPanel();
	
	public ArrayList<Joueur> listeJoueur = new ArrayList();
	
	public ListeJoueur(Jeu jeu) {
		this.jeu = jeu;
		createVue();
		this.setOpaque(false);
		this.setLayout(null);
	}
	
	private void createVue() {
		list.setOpaque(false);
		this.add(this.scrollPaneHorizontal(list));
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		g.setColor(or);
		g.setFont(new Font("verdana", Font.BOLD, 35));
		g.drawString("Joueurs", 160, 40);
	}
	
	public static JScrollPane scrollPaneHorizontal(JComponent component) {
		JScrollPane scroller = new JScrollPane(component);
		scroller.getHorizontalScrollBar().setUnitIncrement(30);
		scroller.setBounds(5, 50, 440,138);
		scroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
		scroller.getHorizontalScrollBar().setPreferredSize(new Dimension(0, 0));
		scroller.setOpaque(false);
		scroller.getViewport().setOpaque(false);
		scroller.setAlignmentX(JScrollPane.LEFT_ALIGNMENT);
		scroller.setBorder(null);
		return scroller;
	}
	
	
	class labelJouer extends JPanel{
		private int id;
		private String nom;
		private int somme;
		
		private labelJouer(int id, String nom,int somme,int incrementY) {
			this.id=id;
			this.nom = nom;
			this.somme = somme;
			
			this.setPreferredSize(new Dimension(138,138));
			this.setBounds(incrementY*138+(list.getComponentCount()+1)*20 , 0 , 138, 138);
			
			this.setBackground(transparent);
			
			this.setLayout(null);
		}
		
		public void paintComponent(Graphics g) {
			g.setFont(new Font("verdana", Font.BOLD, 20));
			g.setColor(or);
			
			if(nom.contains("Joueur")) {
				g.drawString(nom, 20, 30);
			}else {
				g.drawString(nom, 40, 30);
			}
			g.setFont(new Font("verdana", Font.BOLD, 20));
			g.setColor(or);
			g.drawString(String.valueOf(somme)+"$", 10, 125);
			
			g.drawImage(avatar,40,45, 50,50, this);
			
			g.drawRect(0, 5, 132, 130);
		}
	}


	public void addJoueur(Joueur joueur) {
		list.setLayout(null);
		list.add(new labelJouer(joueur.getid(),joueur.getNom(),joueur.getsomme(),list.getComponentCount()));
		list.setPreferredSize(new Dimension(list.getComponentCount()*138+(list.getComponentCount()+1)*20,200));
		list.setBounds(0,0,list.getComponentCount()*138+(list.getComponentCount()+1)*20,200);
	}

	public void removeJoueurs() {
		list.removeAll();
	}
}
