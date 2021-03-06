package Reseau;

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
import Constante.ConstanteParser;
import Constante.ConstanteResau;
import Jeu.FrameJeu;
import Model.Plateau;

public class BlackJackClient implements Constante, ConstanteResau,ConstanteParser {

	private FrameJeu fenetreclient;
	private static final String LO_ADDR = "127.0.0.1";
	public static final int DEFAULT_LOCAL_PORT = 1989;

	private String ip;
	private PrintStream defaultOutStream = System.out;
	private InputStream defaultInStream = System.in;
	private BufferedReader cliReader = new BufferedReader(new InputStreamReader(defaultInStream));

	private BufferedReader socketReader;
	private BufferedWriter socketWriter;

	private boolean game = true;

	public BlackJackClient() throws UnknownHostException, IOException, InterruptedException {
		this(LO_ADDR);
	}

	public BlackJackClient(String hostAddr) throws UnknownHostException, IOException, InterruptedException {
		this("localhost", hostAddr, DEFAULT_LOCAL_PORT, "127.0.0.1");
	}

	public void setMessage(String s, BufferedWriter w) {
		try {
			w.write(s);
			w.flush();
		} catch (IOException e) {
			fenetreclient.showErreurScreen(null);
			game = false;
		}
	}

	public BlackJackClient(String hostname, String hostAddr, Integer hostPort, final String adresse)
			throws UnknownHostException, IOException, InterruptedException {
		ip = adresse;
		final Socket socketSend = new Socket(InetAddress.getByName(hostname), hostPort);

		socketWriter = new BufferedWriter(new OutputStreamWriter(socketSend.getOutputStream()));
		socketReader = new BufferedReader(new InputStreamReader(socketSend.getInputStream()));
		try {
			new Thread() {
				public void run() {
					setMessage(GeneratorEntete.share.generationEnteteGet(connect), socketWriter);
					fenetreclient = new FrameJeu(BlackJackClient.this);
					try {
						while(true){
							String message = litEntete();
							if(message==null)break;
							message = message.replace("\0", "");
							if(!message.isEmpty()) {
								if(isDigit(message) && message != null) {
									readPlateau(Integer.parseInt(message));
								}else {
									dialogue(message);
								}
							}
						}
					} catch (IOException e) {
						fenetreclient.showErreurScreen(null);
					}
				}
			}.start();
		} catch (Exception e) {
			fenetreclient.showErreurScreen(null);
		}
	}

	public void dialogue(String message) {
		if(message.contains(";")){
			String[] dialogue = message.split(";");
			for(int i = 0 ; i < dialogue.length;i++) {
				fenetreclient.addDialogue(dialogue[i]);
			}
		}else if(!message.isEmpty()){
			fenetreclient.addDialogue(message);
		}
	}

	public String litEntete() throws IOException {
		String ligne = socketReader.readLine();
		if(ligne==null) {
			fenetreclient.showErreurScreen(ligne);
			return null;
		}
		String ligne2 = socketReader.readLine();
		
		if(ligne2 == null) {
			fenetreclient.showErreurScreen(null);
			return null;
		}
		
		while(!ligne2.contains(taille)) {
			ligne2 = socketReader.readLine();
			if(ligne2 == null) {
				fenetreclient.showErreurScreen(null);
				return null;
			}
		}
		String message = Parser.share.parseJsonMessage(ligne2);
		
		return message;
	}
	
	public void readPlateau(int size) throws IOException{
		String s;
		StringBuilder msg = new StringBuilder();
		int sizeRead = 0;
		
		while(msg.toString().length() < size-3) {
			s= "";
			s = socketReader.readLine();
			sizeRead += s.length();
			msg.append(s+"\n");	
		}
		
		if(Parser.share.parserMotClef(msg.toString())) {
			msg.setLength(msg.length()-1);
			dialogue(Parser.share.parseJsonMessage(msg.toString()));
			return;
		}
		
		Plateau p = Parser.share.parseJsonData(msg.toString());
		fenetreclient.setPlateau(p);
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

			for (; n.hasMoreElements();) {
				NetworkInterface e = n.nextElement();
				if (e.getName().equals("en0") || e.getName().equals("eth0") || e.getName().equals("Adresse IPv4")) {
					Enumeration<InetAddress> a = e.getInetAddresses();
					InetAddress addr = null;
					for (; a.hasMoreElements();) {
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
	
	private boolean isDigit(String message) {
		try {
			Integer.parseInt(message);
		}catch(NumberFormatException e) {
			return false;
		}
		return true;
	}

}