package Reseau;

import java.awt.Frame;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;

import Constante.Constante;
import Constante.ConstanteResau;
import Jeu.FrameJeu;

public class BlackJackClient implements Constante,ConstanteResau {

	private FrameJeu fenetreclient;
	private static final String LO_ADDR = "127.0.0.1";
	public static final int DEFAULT_LOCAL_PORT = 1989;

	private String ip;
	private PrintStream defaultOutStream = System.out;
	private InputStream defaultInStream = System.in;
	private BufferedReader cliReader = new BufferedReader(new InputStreamReader(defaultInStream));
	private BufferedReader socketReader;
	private BufferedWriter socketWriter;
	private boolean game=true;
	
	
	public BlackJackClient() throws UnknownHostException, IOException, InterruptedException {
		this(LO_ADDR);
	}

	public BlackJackClient(String hostAddr) throws UnknownHostException, IOException, InterruptedException {
		this("localhost",hostAddr, DEFAULT_LOCAL_PORT,"127.0.0.1");
	}

	public void setMessage(String s, BufferedWriter w) {
		try {
			w.write(s);
			w.flush();
		} catch (IOException e) {
			fenetreclient.ecranFin("Erreur du Serveur");
			game=false;
		}
	}
	
	public BlackJackClient(String hostname,String hostAddr, Integer hostPort,final String adresse)
		throws UnknownHostException, IOException, InterruptedException {
		ip = adresse;
		Socket socketSend = new Socket(InetAddress.getByName(hostname), hostPort);
		Socket socketReceiv = new Socket(InetAddress.getByName(hostname), hostPort);
		
		socketReader = new BufferedReader(new InputStreamReader(socketReceiv.getInputStream()));
		socketWriter = new BufferedWriter(new OutputStreamWriter(socketSend.getOutputStream()));
		try {
			new Thread() {
				public void run() {
					try {
						setMessage(GeneratorEntete.share.generationEnteteGet(connect),socketWriter);
						fenetreclient = new FrameJeu(BlackJackClient.this); 

						System.out.println("-----> ");
						String result=socketReader.readLine();
						System.out.println("-----------> ");
						
						System.out.println("-----> " + result);
					} catch (IOException e) {
						e.printStackTrace();
					}
					
				}
			}.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public BufferedReader getSocketReader() {
		return socketReader;
	}

	public BufferedWriter getSocketWriter() {
		return socketWriter;
	}

	public static String getIpadresse() {
		try {
			Enumeration<NetworkInterface> n;
			n = NetworkInterface.getNetworkInterfaces();
			
			for (; n.hasMoreElements();){
                NetworkInterface e = n.nextElement();
                if(e.getName().equals("en0") || e.getName().equals("eth0") || e.getName().equals("Adresse IPv4")) {
                		Enumeration<InetAddress> a = e.getInetAddresses();
                		InetAddress addr = null;
                		for (; a.hasMoreElements();){
                            addr = a.nextElement();
                		}
                    return addr.getHostAddress();
                }
                
			}
		} catch (SocketException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		return "";
	}
	
}