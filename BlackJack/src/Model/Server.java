package Model;

import java.util.Scanner;

public class Server {

	private String adr;
	private String port;
	private int nbJoueur;
	
	public Server(String adr, String port, int nbJ) {
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

	public static Server creationServeur(String hostName, int port, String msg) {
		Server server = new Server(hostName,Integer.toString(port),lireNombrePersonne(msg));		
		return server;
	}

	private static int lireNombrePersonne(String msg) {
		int number = Integer.parseInt(msg.replaceAll("[\\D]", ""));
		return number;
	}
	
	

}
