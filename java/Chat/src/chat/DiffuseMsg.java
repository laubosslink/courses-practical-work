package chat;

import java.awt.GridLayout;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;
import java.util.Scanner;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;

/**
 * Classe permettant de s'inscrire a une adresse de diffusion, et d'y écrire un message
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class DiffuseMsg {
    public static final String DEFAULT_IP="224.0.0.25";
    public static final int DEFAULT_PORT=9877;
    
    private String ip;
    private int port;
    private MulticastSocket group;
    
    public DiffuseMsg() throws IOException{
        this(DEFAULT_IP, DEFAULT_PORT);
    }
    
    /**
     * Permet de récupérer le nom de la machine clientefe
     * @return le nom du diffuseur du message
     * @throws UnknownHostException 
     */
    public String getNom() throws UnknownHostException{
        return InetAddress.getLocalHost().getHostName();
    }
    
    /**
     * Instanciation + inscription au groupe multicast
     * @param ip L'ip auprès de laquelle on s'inscrit
     * @param port Le port par lequelle on envoie les messages
     * @throws IOException 
     */
    public DiffuseMsg(String ip, int port) throws IOException{
        this.ip = ip;
        this.port = port;
        
        this.group = new MulticastSocket();
        this.group.joinGroup(InetAddress.getByName(ip));
    }
    
    /**
     * Envoie d'un message a l'adresse de diffusion
     * @param msg Le message à envoyer
     * @throws IOException 
     */
    public void send(String msg) throws IOException{
        DatagramPacket packet = new DatagramPacket(msg.getBytes(), msg.length(), InetAddress.getByName(ip), port); 
        this.group.send(packet);
    }
}
