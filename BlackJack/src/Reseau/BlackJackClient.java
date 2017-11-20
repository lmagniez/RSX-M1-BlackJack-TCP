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
import java.net.Socket;
import java.net.UnknownHostException;

import Constante.Constante;
import Jeu.FrameJeu;

public class BlackJackClient implements Constante {

	private FrameJeu fenetreclient;
	private static final String LO_ADDR = "127.0.0.1";
	public static final int DEFAULT_LOCAL_PORT = 1989;

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
		this(hostAddr, DEFAULT_LOCAL_PORT);
	}

	public void setMessage(String s, BufferedWriter w) {
		try {
			w.write(s + "\n");
			w.flush();
		} catch (IOException e) {
			fenetreclient.ecranFin("Erreur du Serveur");
			game=false;
		}
	}
	
	public BlackJackClient(String hostAddr, Integer hostPort)
		throws UnknownHostException, IOException, InterruptedException {
		Socket socket = new Socket(InetAddress.getByName(hostAddr), hostPort);
		socketReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		socketWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
		try {
			new Thread() {
				public void run() {
					/*
					try {
					 
					} catch (IOException e) {
						fenetreclient.ecranFin("Erreur du Serveur");
						game=false;
					}*/
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
}