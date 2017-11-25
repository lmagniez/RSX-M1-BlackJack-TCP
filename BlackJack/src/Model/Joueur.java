package Model;

import java.util.ArrayList;

public class Joueur {

	private int id_joueur;
	private String nom;
	private int credit;
	private int mise_totale;
	private int mise_actuelle;
	private EtatJoueur etat;
	private ArrayList<Jeu> jeux = new ArrayList();
	
	public Joueur() {
	}
	
	public Joueur(int id_joueur, int credit, int mise_totale, int mise_actuelle, EtatJoueur etat, ArrayList<Jeu> jeux) {
		this.nom = "Joueur"+ (id_joueur+1);
		this.id_joueur = id_joueur;
		this.credit = credit;
		this.mise_totale = mise_totale;
		this.mise_actuelle = mise_actuelle;
		this.etat = etat;
		this.jeux = jeux;
	}
	
	public Joueur(int id_joueur, String nom, int credit, int mise_totale, int mise_actuelle, EtatJoueur etat, ArrayList<Jeu> jeux) {
		this(id_joueur,credit,mise_totale,mise_actuelle,etat,jeux);
		this.nom = nom;
	}

	public int getid() {
		return id_joueur;
	}
	
	public void setId_joueur(int id_joueur) {
		this.id_joueur = id_joueur;
	}

	public void setCredit(int credit) {
		this.credit = credit;
	}

	public void setEtat(EtatJoueur etat) {
		this.etat = etat;
	}

	public int getsomme() {
		return credit;
	}
	
	public String getNom() {
		return nom;
	}
	
	public void setNom(String nom) {
		this.nom = nom;
	}

	public int getId_joueur() {
		return id_joueur;
	}

	public int getCredit() {
		return credit;
	}

	public EtatJoueur getEtat() {
		return etat;
	}

	public int getMise_totale() {
		return mise_totale;
	}

	public void setMise_totale(int mise_totale) {
		this.mise_totale = mise_totale;
	}

	public int getMise_actuelle() {
		return mise_actuelle;
	}

	public void setMise_actuelle(int mise_actuelle) {
		this.mise_actuelle = mise_actuelle;
	}

	public ArrayList<Jeu> getJeux() {
		return jeux;
	}

	public void setJeux(ArrayList<Jeu> jeux) {
		this.jeux = jeux;
	}

	@Override
	public String toString() {
		return "Joueur [id_joueur=" + id_joueur + ", nom=" + nom + ", credit=" + credit + ", mise_totale=" + mise_totale
				+ ", mise_actuelle=" + mise_actuelle + ", etat=" + etat + ", jeux=" + jeux + "]";
	}
	
	
	
}
