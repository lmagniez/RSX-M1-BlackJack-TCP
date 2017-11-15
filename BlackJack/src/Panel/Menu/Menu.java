package Panel.Menu;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;

import Constante.Constante;
import Reseau.Connection;

public class Menu extends JPanel implements ActionListener,Constante{

	private FrameJeuMenu frame;
	private Bouton jouer=new Bouton(this,"Jouer");
	private Bouton quitter=new Bouton(this,"Quitter");
	
	/**
	 * Constructeur de Menu
	 * @param j FrameJeuMenu
	 */
	public Menu(FrameJeuMenu j){
		frame=j;
		this.setPreferredSize(new Dimension(frame.getHeight(), frame.getWidth()));
		creerlayout();
	}
	
	/**
	 * Creer le layout du serveur
	 */
	private void creerlayout() {
		setLayout(null);
		jouer.setBounds(50, 290, 300, 50);
		quitter.setBounds(50, 370, 300, 50);
		this.add(jouer);
		this.add(quitter);
	}

	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawImage(fond,0, 0, 400, 500,this);
	}


	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("Quitter")) 
			frame.dispose();
		else if (e.getActionCommand().equals("Jouer")) {
			Connection.creationBroadcast();
			frame.choosePort();
		}		
	}
}
