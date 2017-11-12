package Panel.Connect;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import Constante.Constante;
import Jeu.Jeu;
import Model.Joueur;
import Model.Server;
import Panel.Jeu.BoutonPlateau;
import Panel.JeuClient.FrameJeu;
import Panel.Menu.FrameJeuMenu;

public class ListeServeur extends JPanel implements Constante{

	FrameJeuMenu jeu;
	private JPanel list = new JPanel();
	
	ArrayList<Server> listeServer = new ArrayList();
	
	public ListeServeur(FrameJeuMenu f) {
		this.jeu = f;
		
		listeServer.add(new Server("127.0.0.1","80",4));
		listeServer.add(new Server("127.0.0.2","80",1));
		listeServer.add(new Server("127.0.0.3","80",2));
		listeServer.add(new Server("127.0.0.4","80",8));
		listeServer.add(new Server("127.0.0.5","80",4));
		listeServer.add(new Server("127.0.0.6","80",4));
		listeServer.add(new Server("127.0.0.7","80",7));
		this.setOpaque(false);
		createVue();
		this.setLayout(null);
	}
	
	private void createVue() {
		for(int i = 0 ; i< listeServer.size();i++) {
			list.add(new labelServer(listeServer.get(i).getAdr(),listeServer.get(i).getPort(),listeServer.get(i).getNbJoueur(),list.getComponentCount(),jeu));			
		}
		list.setOpaque(false);
		list.setPreferredSize(new Dimension(350, (list.getComponentCount()+1)*75));
		list.setBounds(5,5,350, (list.getComponentCount()+1)*75);
		
		this.add(this.scrollPaneVertical(list));
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
		private String addresse;
		private String port;
		private int nbJoueur;
		private BoutonPlateau boutonConnect= new BoutonPlateau(this,"Join");
		private FrameJeuMenu frameJeuMenu;
		
		private labelServer(String addr,String port,int nbJoueur,int incrementY,FrameJeuMenu frameJeuMenu) {
			this.frameJeuMenu = frameJeuMenu;
			this.addresse = addr;
			this.nbJoueur = nbJoueur;
			this.port = port;
			
			this.setPreferredSize(new Dimension(340, 75));
			this.setBounds( 0 , 10*incrementY , 300, 75);

			boutonConnect.setBounds(200,15,120,40);
			
			this.add(boutonConnect);
			this.setBackground(transparent);
			this.setLayout(null);
		}
		
		public void paintComponent(Graphics g) {
			g.setFont(new Font("verdana", Font.BOLD, 15));
			g.setColor(or);

			g.drawString("Adresse: "+this.addresse, 10, 20);
			g.drawString("Port: "+this.port, 10, 40);
			g.drawString("Table: "+nbJoueur+"/8", 10, 60);
			g.drawRect(0, 0, 338, 70);
		}
		
		/**
		 * Action Performed 
		 */
		@Override
		public void actionPerformed(ActionEvent e) {
			if (e.getActionCommand().equals("Join")) {
				String[] tab = { this.addresse, this.port };
				creerclient(tab);
				repaint();
				
				//TO DO 
				//error = "CONNECTION A FAIRE";
				new FrameJeu(null);
				frameJeuMenu.setVisible(false);
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
}
