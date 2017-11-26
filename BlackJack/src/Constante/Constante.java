package Constante;

import java.awt.Color;
import java.awt.Image;
import java.awt.Toolkit;

import javax.swing.ImageIcon;

public interface Constante {

	public Image fond=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/fond.png");
	public Image fondGeneral=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/fondGeneral.jpg");
	
	public Image fondListe=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/fond_liste.png");
	
	public ImageIcon loading = new ImageIcon( "./src/Ressource/Image/loading.gif" );
	public Image cadre = Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/cadre.png");
	
	public Image fondPlateau=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/table.png");
	
	public Image tapis=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/tapis.png");
	
	public Image avatar=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/avatar.png");
	
	public Color or = new Color(232, 179, 83);
	
	public Color transparent =new Color(1f,0f,0f,.5f );
	
	public Image[][] cartes = { 
			{   Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/1.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/2.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/3.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/4.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/5.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/6.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/7.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/8.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/9.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/10.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/11.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/12.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/coeur/13.png")},
			
			{   Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/1.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/2.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/3.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/4.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/5.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/6.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/7.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/8.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/9.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/10.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/11.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/12.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/carreau/13.png")},
			
			{   Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/1.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/2.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/3.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/4.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/5.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/6.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/7.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/8.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/9.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/10.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/11.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/12.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/trefle/13.png")},
			
			{   Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/1.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/2.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/3.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/4.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/5.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/6.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/7.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/8.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/9.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/10.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/11.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/12.png"),
				Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/pique/13.png")},
	};
	
	public Image carteRecto =  Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/jeu/face.png");
}
