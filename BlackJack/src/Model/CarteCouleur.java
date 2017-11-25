package Model;

public enum CarteCouleur {
	coeur,carreau,trefle,pique;
	
	public static String getDirectory(CarteCouleur couleur) { 
		switch(couleur) {
		case coeur :
			return "coeur";
		case carreau :
			return "carreau";
		case trefle :
			return "trefle";
		default :
			return "coeur";
		}
	}
}
