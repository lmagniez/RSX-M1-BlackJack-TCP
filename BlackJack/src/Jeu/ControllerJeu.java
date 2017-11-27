package Jeu;

import Constante.ConstanteMessage;
import Constante.ConstanteResau;
import Reseau.BlackJackClient;
import Reseau.GeneratorEntete;

public class ControllerJeu implements ConstanteMessage,ConstanteResau{

	private BlackJackClient joueurReseau;
	private ModelJeu modelJ;
	
	public ControllerJeu(BlackJackClient newJ, ModelJeu modelJeux) {
		joueurReseau = newJ;
		modelJ = modelJeux;
	}

	public void mise(int miseValue) {
		boolean assezArgent = modelJ.verifAssezArgent(miseValue);
		if(assezArgent) {
			String entete = GeneratorEntete.share.generationEntetePostNumber(mise,miseValue);
			joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
			modelJ.desactiveAllBoutons();
		}else {
			modelJ.afficheErreurMessage(erreurMise);
		}
	}

	public void demandeCarte() {
		String entete = GeneratorEntete.share.generationEnteteGet(tirer);
		joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
		modelJ.desactiveAllBoutons();
	}

	public void rester() {
		String entete = GeneratorEntete.share.generationEnteteGet(rester);
		joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
		modelJ.desactiveAllBoutons();
	}

	public void demandeDouble() {
		String entete = GeneratorEntete.share.generationEnteteGet(doubler);
		joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
		modelJ.desactiveAllBoutons();
	}

	public void demandeSplit() {
		String entete = GeneratorEntete.share.generationEnteteGet(split);
		joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
		modelJ.desactiveAllBoutons();
	}

	public void demandeQuitter() {
		String entete = GeneratorEntete.share.generationEnteteGet(leave);
		joueurReseau.setMessage(entete, joueurReseau.getSocketWriter());
		modelJ.desactiveAllBoutons();
	}
}
