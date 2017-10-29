package Constante;

import java.awt.Color;
import java.awt.Image;
import java.awt.Toolkit;

public interface Constante {

	public Image fond=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/fond.png");
	
	public Image fondPlateau=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/table.png");
	
	public Image tapis=Toolkit.getDefaultToolkit().createImage("./src/Ressource/Image/tapis.png");
	
	public Color or = new Color(232, 179, 83);
	
	public Color transparent =new Color(1f,0f,0f,.5f );
}
