package Panel.Connect;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Constante.Constante;
import Panel.JeuClient.FrameJeu;
import Panel.Menu.Bouton;
import Panel.Menu.FrameJeuMenu;
import Reseau.BlackJackClient;

public class Identification extends JPanel implements ActionListener, Constante {

	private FrameJeuMenu f;
	private int type;
	private JTextField port = new JTextField("1664");
	private JTextField adresse = new JTextField("adresse");
	private Bouton play = new Bouton(this, "Connection");
	private String error = "";

	/**
	 * Constructeur de Identification
	 * @param t int
	 * @param fen FrameJeuMenu
	 */
	public Identification(int t,FrameJeuMenu fen) {
		type = t;
		f=fen;
		creerlayout();
	}
	
	/**
	 * Creer le layout du panel
	 */
	private void creerlayout() {
		setLayout(null);

		port.setBounds(50, 260, 300, 50);
		adresse.setBounds(50, 310, 300, 50);

		play.setBounds(50, 400, 300, 50);
		
		this.add(port);
		this.add(adresse);
		this.add(play);
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(fond, 0, 0, 400, 500, this);
		g.setColor(Color.WHITE);
		g.setFont(new Font("verdana", Font.BOLD, 15));
		g.drawString(error, 110, 380);
	}

	/**
	 * Action Performed 
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("Connection")) {
			String[] tab = { adresse.getText(), port.getText() };
			creerclient(tab);
			repaint();
			
			//TO DO 
			error = "CONNECTION A FAIRE";
			new FrameJeu(null);
			f.setVisible(false);
		}
	}

	/**
	 * Creer le client
	 * @param tab
	 */
	private void creerclient(String[] tab) {
		/*
		 try {
			if (tab.length > 1 && !tab[0].equals("") && !tab[1].equals("")) {
				new BattleShipClient(tab[0], Integer.valueOf(tab[1]));
			} else if (tab.length > 0 && !!tab[0].equals("")) {
				new BattleShipClient(tab[0]);
			} else {
				new BattleShipClient();
			}
			f.setVisible(false);
		} catch (UnknownHostException e1) {
			error = "Unknown Error";
			repaint();
		} catch (IOException e1) {
			error = "Connection refused";
			repaint();
		} catch (InterruptedException e1) {
			error = "Connection Lost";
			repaint();
		}*/
	}
}
