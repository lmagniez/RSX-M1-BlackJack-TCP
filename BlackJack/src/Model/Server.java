package Model;

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
	
	

}
