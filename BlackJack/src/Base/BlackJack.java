package Base;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import Constante.ConstanteResau;
import Panel.Menu.FrameJeuMenu;
import Reseau.GeneratorEntete;
import Reseau.Parser;

public class BlackJack implements ConstanteResau{
	
	public static void main(String [] args) {
		
		System.out.println(GeneratorEntete.share.generationEnteteGet(connect));
		System.out.println(GeneratorEntete.share.generationEntetePostNumber(mise,200));
		System.out.println(GeneratorEntete.share.generationEntetePostString("NEXISTE/PAS","AU CAS OU"));
		
		FrameJeuMenu fen1=new FrameJeuMenu();
	}
}
