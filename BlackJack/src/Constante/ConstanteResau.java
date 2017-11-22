package Constante;

import Reseau.BlackJackClient;

public interface ConstanteResau {
	
	public String ip = BlackJackClient.getIpadresse();
	
	public String get = "GET ";
	public String post = "POST ";
	
	public String mise = "/action/mise";
	public String tirer = "/action/tirer";
	public String split = "/action/split";

	public String leave = "/action/leave";
	public String doubler = "/action/doubler";
	public String rester = "/action/rester";
	
	public String connect = "action/connect";
}
