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
}
