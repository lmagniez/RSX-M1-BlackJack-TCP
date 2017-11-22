package Reseau;

import java.net.InetAddress;
import java.net.UnknownHostException;

import Constante.ConstanteResau;

public class GeneratorEntete implements ConstanteResau{
	
	public static GeneratorEntete share = new GeneratorEntete();
	
	public String generationEnteteGet(String route) {
		return get + route + "\n";
	}
	
	public String generationEntetePostNumber(String route,int number ) {
		return post + route + "\n" + String.valueOf(number) + "\n";
	}

	public String generationEntetePostString(String route,String data) {
		return post + route + "\n" + data + "\n";
	}

	public String generationEnteteGetAvecHost(String route,String adresse){
		return get + route + "\nhost: "+ adresse +"\n";
	}
}
