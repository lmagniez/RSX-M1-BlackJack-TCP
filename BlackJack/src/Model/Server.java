package Model;

import java.util.Scanner;

public class Server {

	private String hostname;
	private String adr;
	private String port;
	private int nbJoueur;
	
	public Server(String hostname,String adr, String port, int nbJ) {
		this.hostname = hostname;
		this.adr = adr;
		this.port = port;
		this.nbJoueur = nbJ;
	}

	public String getAdr() {
		return adr;
	}

	public void setAdr(String adr) {
		this.adr = adr;
	}

	public int getNbJoueur() {
		return nbJoueur;
	}

	public void setNbJoueur(int nbJoueur) {
		this.nbJoueur = nbJoueur;
	}

	public String getPort() {
		return port;
	}

	public void setPort(String port) {
		this.port = port;
	}
	
	

	public String getHostname() {
		return hostname;
	}

	public void setHostname(String hostname) {
		this.hostname = hostname;
	}

	public static Server creationServeur(String hostname,String addr, int port, String msg) {
		int nb;
		if((nb=lireNombrePersonne(msg)) ==-1)return null;
		Server server = new Server(hostname,addr,Integer.toString(port),nb);		
		return server;
	}

	private static int lireNombrePersonne(String msg) {
			msg = msg.replaceAll("[\\D]", "");
			if(msg.equals(""))return -1;
			return Integer.parseInt(msg);
	}
	
	

}
