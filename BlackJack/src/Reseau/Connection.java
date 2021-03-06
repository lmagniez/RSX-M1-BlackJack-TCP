package Reseau;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.UnknownHostException;

import Panel.Connect.Identification;


public class Connection {
	
	public static Connection share = new Connection();
	
	public  int portTCP = 9090;
	public  int portUDP = 8080;
	
	public  boolean recoit = true;
	
    public  void broadcast(String broadcastMessage, InetAddress address) throws IOException {
        DatagramSocket socket = new DatagramSocket();
        socket.setBroadcast(true);
 
        byte[] buffer = broadcastMessage.getBytes();
        
        DatagramPacket packet 
          = new DatagramPacket(buffer, buffer.length, address, portUDP);
        socket.send(packet);
        socket.close();
    }
    
    private  void ecouteUDP(final Identification ident) throws IOException {  		
    	      final DatagramSocket dsocket = new DatagramSocket(portUDP);
    	      final byte[] buffer = new byte[50];

    	      final DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    	      
    	      Thread t = new Thread() {
    	          public void run() {
    	        	  	while (recoit) {
    	      	        try {
							dsocket.receive(packet);
							String msg = new String(buffer, 0, packet.getLength());
							ident.getListeServeur().add(packet.getAddress().toString().replaceAll("/", ""),packet.getAddress().getHostName(),portTCP,msg);
		    	      	    packet.setLength(buffer.length);
					} catch (IOException e) {
							System.out.println("RECEIV UDP");
					}
    	      	     }
    	          }
    	        };
    	      t.start();
	}

	public  void creationBroadcast(Identification ident) {
		try {
			share.broadcast("I WANT TO PLAY BLACKJACK", InetAddress.getByName("255.255.255.255"));
	        share.ecouteUDP(ident);
		} catch (Exception e) {
			ident.afficheEcranErreur("Veuillez fermer les autres \n fenetres de BlackJack");
		} 
    }

	public void ferme() {
		recoit = !recoit;
	}

}
