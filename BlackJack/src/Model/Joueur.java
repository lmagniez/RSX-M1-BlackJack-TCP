package Model;

public class Joueur {

	private int id;
	private String nom;
	private int somme;

	public Joueur(int id , int somme) {
		this.id = id;
		this.nom = "J"+ (id+1);
		this.somme = somme;
	}

	public Joueur(int id, String nom, int somme) {
		this(id,somme);
		this.nom = nom;
	}
	
	public int getid() {
		return id;
	}
	
	public int getsomme() {
		return somme;
	}
	
	public String getnom() {
		return nom;
	}
}
