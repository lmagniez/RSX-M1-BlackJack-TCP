package Model;

import java.util.ArrayList;

public class Jeu {

	private ArrayList<CarteValue> jeuCartes = new ArrayList<CarteValue>();
	private ArrayList<CarteCouleur> jeuCouleurs = new ArrayList<CarteCouleur>();
	private int value;
	private EtatJeu etat;
	
	public EtatJeu getEtat() {
		return etat;
	}
	public void setEtat(EtatJeu etat) {
		this.etat = etat;
	}
	public ArrayList<CarteValue> getJeuCartes() {
		return jeuCartes;
	}
	public void setJeuCartes(ArrayList<CarteValue> jeuCartes) {
		this.jeuCartes = jeuCartes;
	}
	public ArrayList<CarteCouleur> getJeuCouleurs() {
		return jeuCouleurs;
	}
	public void setJeuCouleurs(ArrayList<CarteCouleur> jeuCouleurs) {
		this.jeuCouleurs = jeuCouleurs;
	}
	public int getValue() {
		return value;
	}
	public void setValue(int value) {
		this.value = value;
	}
	
	@Override
	public String toString() {
		return "Jeu [jeuCartes=" + jeuCartes + ", jeuCouleurs=" + jeuCouleurs + ", value=" + value + ", etat=" + etat
				+ "]";
	}
}
