package Reseau;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;


public class Connection {
	
    public static void broadcast(String broadcastMessage, InetAddress address) throws IOException {
        DatagramSocket socket = new DatagramSocket();
        socket.setBroadcast(true);
 
        byte[] buffer = broadcastMessage.getBytes();
        
        DatagramPacket packet 
          = new DatagramPacket(buffer, buffer.length, address, 8080);
        socket.send(packet);
        Connection.ecouteUDP();
        socket.close();
        
    }
    
    private static void ecouteUDP() {
	}

	public static void creationBroadcast() {
		try {
			Connection.broadcast("I WANT TO PLAY BLACKJACK", InetAddress.getByName("255.255.255.255"));
		} catch (Exception e) {
			e.printStackTrace();
		} 
    }

}
