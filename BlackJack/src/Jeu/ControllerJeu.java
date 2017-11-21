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
			System.out.println(entete);
			modelJ.afficheBoutonAction();
		}else {
			modelJ.afficheErreurMessage(erreurMise);
		}
	}

	public void demandeCarte() {
		String entete = GeneratorEntete.share.generationEnteteGet(tirer);
		System.out.println(entete);
	}

	public void rester() {
		String entete = GeneratorEntete.share.generationEnteteGet(rester);
		System.out.println(entete);
	}

	public void demandeDouble() {
		String entete = GeneratorEntete.share.generationEnteteGet(doubler);
		System.out.println(entete);
	}

	public void demandeSplit() {
		String entete = GeneratorEntete.share.generationEnteteGet(split);
		System.out.println(entete);
		
	}

	public void demandeQuitter() {
		String entete = GeneratorEntete.share.generationEnteteGet(leave);
		System.out.println(entete);
	}
}
