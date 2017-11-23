package Panel.Connect;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Rectangle2D;
import java.io.IOException;
import java.net.UnknownHostException;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import Constante.Constante;
import Constante.ConstanteResau;
import Jeu.FrameJeu;
import Jeu.Jeu;
import Jeu.Panel.BoutonPlateau;
import Model.Joueur;
import Model.Server;
import Panel.Menu.FrameJeuMenu;
import Reseau.BlackJackClient;
import Reseau.Connection;

public class ListeServeur extends JPanel implements Constante,ConstanteResau{

	FrameJeuMenu jeu;
	private JPanel list = new JPanel();
	private JLabel loadingLabel = new JLabel(loading) ;
	private JScrollPane scroll;
	private String erreur = "Manque d'argent";
	
	ArrayList<Server> listeServer = new ArrayList();
	
	public ListeServeur(FrameJeuMenu f) {
		this.jeu = f;
		this.setOpaque(false);
		this.setLayout(null);
		
		createVue();
		if(listeServer.isEmpty()) {
			loadingLabel.setBounds(75, 80, 200, 200);
			this.add(loadingLabel);
		}
	}
	
	public void add(String addr , String hostname, int port, String msg) {
		Server server = Server.creationServeur(hostname,addr,port,msg);
		if(server == null)return;
		listeServer.add(server);
		addServer();
		this.repaint();
	}
	
	private void addServer() {
		this.remove(this.getComponentCount()-1);
		int i = listeServer.size()-1;
		list.add(new labelServer(listeServer.get(i),list.getComponentCount(),jeu));
		list.setPreferredSize(new Dimension(350, (list.getComponentCount()+1)*75));
		list.setBounds(5,5,350, (list.getComponentCount()+1)*75);
	}

	private void createVue() {
		for(int i = 0 ; i< listeServer.size();i++) {
			list.add(new labelServer(listeServer.get(i),list.getComponentCount(),jeu));			
		}
		list.setOpaque(false);
		list.setPreferredSize(new Dimension(350, (list.getComponentCount()+1)*75));
		list.setBounds(5,5,350, (list.getComponentCount()+1)*75);
		
		this.removeAll();
		scroll = this.scrollPaneVertical(list);
		this.add(scroll);
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
	}
	
	/**
	 * Creation du JScrollPane
	 * @param comp
	 * @return JScrollPane
	 */
    public static JScrollPane scrollPaneVertical(JComponent comp) {    	
        JScrollPane scroller = new JScrollPane(comp);
        scroller.getHorizontalScrollBar().setUnitIncrement(30);
        scroller.setBounds(0,0,350, 370);
        scroller.getVerticalScrollBar().setPreferredSize(new Dimension(0,0));
        scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scroller.setOpaque(false);
        scroller.getViewport().setOpaque(false);
        scroller.setBorder(null);
        return scroller;
    }
	
	
	class labelServer extends JPanel implements ActionListener{
		private Server serv;
		private BoutonPlateau boutonConnect= new BoutonPlateau(this,"Join");
		private FrameJeuMenu frameJeuMenu;
		
		private labelServer(Server serv,int incrementY,FrameJeuMenu frameJeuMenu) {
			this.frameJeuMenu = frameJeuMenu;
			this.serv = serv;
			
			this.setPreferredSize(new Dimension(340, 75));
			this.setBounds( 0 , 10*incrementY , 300, 75);

			
			boutonConnect.setBounds(220,30,100,30);
			
			if(serv.getNbJoueur()>=7)this.boutonConnect.setEnabled(false);
			
			this.add(boutonConnect);
			
			this.setBackground(transparent);
			this.setLayout(null);
		}
		
		public void paintComponent(Graphics g) {
			g.setFont(new Font("verdana", Font.BOLD, 15));
			g.setColor(or);

			g.drawString("Adresse: "+serv.getAdr(), 10, 20);
			g.drawString("Port: "+serv.getPort(), 10, 40);
			g.drawString("Table: "+serv.getNbJoueur()+"/8", 10, 60);
			g.drawRect(0, 0, 338, 70);
		}
		
		/**
		 * Action Performed 
		 */
		public void actionPerformed(ActionEvent e) {
			if (e.getActionCommand().equals("Join")) {
				Connection.share.ferme();
				
				String[] tab = { serv.getHostname(),serv.getAdr(), serv.getPort() };
				creerclient(tab);
				repaint();
			}
		}

		/**
		 * Creer le client
		 * @param tab
		 */
		private void creerclient(String[] tab) {
			String error;
			BlackJackClient client;
			 try {
				if (tab.length > 1 && !tab[0].equals("") && !tab[1].equals("")) {
					client = new BlackJackClient(tab[0],tab[1], Integer.valueOf(tab[2]),ip);
				} else if (tab.length > 0 && !!tab[0].equals("")) {
					client = new BlackJackClient(tab[0]);
				} else {
					client= new BlackJackClient();
				}
				frameJeuMenu.setVisible(false);
			} catch (UnknownHostException e1) {
				error = "Unknown Error";
				repaint();
			} catch (IOException e1) {
				error = "Connection refused";
				repaint();
			} catch (InterruptedException e1) {
				error = "Connection Lost";
				repaint();
			}
		}
	}
}
