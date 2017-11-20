package Jeu;

import Reseau.BlackJackClient;

public class ControllerJeu {

	private BlackJackClient joueurReseau;
	private ModelJeu modelJ;
	
	public ControllerJeu(BlackJackClient newJ, ModelJeu modelJeux) {
		joueurReseau = newJ;
		modelJ = modelJeux;
	}

	public void mise(int mise) {
		boolean assezArgent = modelJ.verifAssezArgent(mise);
		if(assezArgent) {
			
			
			modelJ.afficheBoutonAction();
		}else {
			modelJ.afficheErreurMessage();
		}
	}

}
