package Panel.Jeu;

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
	
	ArrayList<Joueur> listeJoueur = new ArrayList();
	
	public ListeJoueur(Jeu jeu) {
		this.jeu = jeu;
		
		listeJoueur.add(new Joueur(0,"YOU",12000));
		listeJoueur.add(new Joueur(1,12000));
		listeJoueur.add(new Joueur(2,12000));
		listeJoueur.add(new Joueur(3,12000));
		listeJoueur.add(new Joueur(4,12000));
		listeJoueur.add(new Joueur(5,12000));
		listeJoueur.add(new Joueur(6,12000));
		
		createVue();
		this.setLayout(null);
	}
	
	private void createVue() {
		for(int i = 0 ; i< listeJoueur.size();i++) {
			list.add(new labelJouer(listeJoueur.get(i).getid(),listeJoueur.get(i).getnom(),listeJoueur.get(i).getsomme(),list.getComponentCount()));			
		}
		list.setOpaque(false);
		list.setPreferredSize(new Dimension(280, (list.getComponentCount()+1)*50));
		list.setBounds(10,80,280, (list.getComponentCount()+1)*50);
		
		this.add(this.scrollPaneVertical(list));
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(tapis, 0, 0,300, 500, this);
		
		g.setColor(or);
		g.setFont(new Font("verdana", Font.BOLD, 35));
		g.drawString("Joueurs", 70, 50);
	}
	
	/**
	 * Creation du JScrollPane
	 * @param comp
	 * @return JScrollPane
	 */
    public static JScrollPane scrollPaneVertical(JComponent comp) {    	
        JScrollPane scroller = new JScrollPane(comp);
        scroller.getHorizontalScrollBar().setUnitIncrement(30);
        scroller.setBounds(10,60,280,380);
        scroller.getVerticalScrollBar().setPreferredSize(new Dimension(0,0));
        scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scroller.setOpaque(false);
        scroller.getViewport().setOpaque(false);
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
			
			this.setPreferredSize(new Dimension(280, 50));
			this.setBounds( 0 , 10*incrementY , 280, 50);
			
			this.setBackground(transparent);
			
			this.setLayout(null);
		}
		
		public void paintComponent(Graphics g) {
			g.setFont(new Font("verdana", Font.BOLD, 20));
			g.setColor(or);
			g.drawString(nom, 40, 30);
			
			g.setFont(new Font("verdana", Font.BOLD, 20));
			g.setColor(or);
			g.drawString(String.valueOf(somme)+"$", 140, 30);
			
			g.drawRect(0, 0, 275, 40);
		}
	}
}
