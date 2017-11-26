package Model;

import java.util.ArrayList;

public class Plateau {

	private int nb_joueur;
	private int tour_id_joueur;
	private int tour_id_jeu;
	private int tour_started;
	private Jeu jeu_croupier;
	
	private ArrayList<Joueur> listJoueur= new ArrayList();

	public Plateau() {
	}
	
	public Plateau(int nb_joueur, int tour_id_joueur, int tour_id_jeu, Jeu jeu_croupier, ArrayList<Joueur> listJoueur) {
		super();
		this.nb_joueur = nb_joueur;
		this.tour_id_joueur = tour_id_joueur;
		this.tour_id_jeu = tour_id_jeu;
		this.jeu_croupier = jeu_croupier;
		this.listJoueur = listJoueur;
	}
	
	public int getNb_joueur() {
		return nb_joueur;
	}

	public void setNb_joueur(int nb_joueur) {
		this.nb_joueur = nb_joueur;
	}

	public int getTour_id_joueur() {
		return tour_id_joueur;
	}

	public void setTour_id_joueur(int tour_id_joueur) {
		this.tour_id_joueur = tour_id_joueur;
	}

	public int getTour_id_jeu() {
		return tour_id_jeu;
	}

	public void setTour_id_jeu(int tour_id_jeu) {
		this.tour_id_jeu = tour_id_jeu;
	}

	public Jeu getJeu_croupier() {
		return jeu_croupier;
	}

	public void setJeu_croupier(Jeu jeu_croupier) {
		this.jeu_croupier = jeu_croupier;
	}

	public ArrayList<Joueur> getListJoueur() {
		return listJoueur;
	}

	public void setListJoueur(ArrayList<Joueur> listJoueur) {
		this.listJoueur = listJoueur;
	}

	public int getTour_started() {
		return tour_started;
	}

	public void setTour_started(int tour_started) {
		this.tour_started = tour_started;
	}

	@Override
	public String toString() {
		return "Plateau [nb_joueur=" + nb_joueur + ", tour_id_joueur=" + tour_id_joueur + ", tour_id_jeu=" + tour_id_jeu
				+ ", jeu_croupier=" + jeu_croupier + ", listJoueur=" + listJoueur + "]";
	}
	
	
	
}
