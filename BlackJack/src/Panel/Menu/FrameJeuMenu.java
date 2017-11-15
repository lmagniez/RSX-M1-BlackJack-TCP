package Panel.Menu;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Panel.Connect.Identification;
import Reseau.Connection;

public class FrameJeuMenu extends JFrame{

	Menu m=new Menu(this);
	Identification ident;
	
	/**
	 * Constructeur de la Frame de Menu
	 */
	public FrameJeuMenu(){
		this.setTitle("BlackJack");
		this.setSize(400,500);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		this.setFocusable(false);
		this.add(m);
		this.setVisible(true);
	}
	
	/**
	 * Swap les ecrans
	 * @param j
	 */
	public void swapEcran(JPanel j){
		getContentPane().removeAll();
		getContentPane().repaint();
		this.add(j);
		validate();
	}

	public void choosePort() {
		ident=new Identification(1,this);
		Connection.share.creationBroadcast(ident);
		swapEcran(ident);
	}
}
