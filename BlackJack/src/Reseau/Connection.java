package Reseau;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

import Panel.Connect.Identification;


public class Connection {
	
	public static Connection share = new Connection();
	
	public  int port = 8080;
	public  boolean recoit = true;
	
    public  void broadcast(String broadcastMessage, InetAddress address) throws IOException {
        DatagramSocket socket = new DatagramSocket();
        socket.setBroadcast(true);
 
        byte[] buffer = broadcastMessage.getBytes();
        
        DatagramPacket packet 
          = new DatagramPacket(buffer, buffer.length, address, port);
        socket.send(packet);
        socket.close();
    }
    
    private  void ecouteUDP(Identification ident) throws IOException {  		
    	      DatagramSocket dsocket = new DatagramSocket(port);
    	      byte[] buffer = new byte[50];

    	      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    	      
    	      Thread t = new Thread() {
    	          public void run() {
    	        	  	while (recoit) {
    	      	        try {
							dsocket.receive(packet);
							String msg = new String(buffer, 0, packet.getLength());
							
		    	      	        ident.getListeServeur().add(packet.getAddress().getHostName(),port,msg);

		    	      	        packet.setLength(buffer.length);
					} catch (IOException e) {
							e.printStackTrace();
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
			e.printStackTrace();
		} 
    }

	public void ferme() {
		recoit = !recoit;
	}

}
