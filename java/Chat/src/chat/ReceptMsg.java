package chat;

import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe permettant de s'inscrire a une adresse de diffusion et d'afficher les messages qui y sont reçus
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ReceptMsg extends Thread {
    public static final String DEFAULT_IP="224.0.0.25";
    public static final int DEFAULT_PORT=9877, DEFAULT_SIZE_PACKET=300;
    
    private MsgModel model;
    
    private String ip;
    private int port;
    private MulticastSocket multicast;
    
    private boolean receptNode;

    /**
     * Initialisation alternative
     * @param model
     * @throws IOException 
     * @see ReceptMsg(String, int, MsgModel)
     */
    public ReceptMsg(MsgModel model) throws IOException{
        this(DEFAULT_IP, DEFAULT_PORT, model);
    }
    
    /**
     * Initialisation/inscription de l'adresse de diff sur un port
     * @param ip L'ip à laquelle on veut s'abonner
     * @param port Le port d'écoute sur l'adresse de diffusion
     * @throws IOException 
     */
    public ReceptMsg(String ip, int port, MsgModel model) throws IOException {
        this.ip = ip;
        this.port = port;
        this.model = model;
    
        this.multicast = new MulticastSocket(port);
        this.multicast.joinGroup(InetAddress.getByName(ip));
    }
    
    /**
     * Lancement d'un noeud d'écoute
     * Remarque, les messages reçus sont envoyés au model 
     * @throws IOException 
     */
    public void listen() throws IOException{
        receptNode = true;
        
        byte[] byteReception;
        
        while(receptNode){
            // Il faut le mettre dans la boucle ! Sinon on le buffer qui contient le reste des messages précédents
            byteReception = new byte[DEFAULT_SIZE_PACKET];
            
            DatagramPacket receivePacket = new DatagramPacket(byteReception, byteReception.length); 
                    
            this.multicast.receive(receivePacket);
            
            model.receiveData(receivePacket.getAddress().getHostAddress() + ":" + new String(receivePacket.getData(), 0, receivePacket.getLength()));
        }
    }
    
    /**
     * On doit pouvoir lancer un thread, utile lors de la question 3, afin de réaliser un chat écriture/lecture dans un même terminal
     */
    @Override
    public void run(){
        try {
            listen();
        } catch (IOException ex) {
            Logger.getLogger(ReceptMsg.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /**
     * On doit pouvoir interrompre le thread
     */
    @Override
    public void interrupt(){
        this.receptNode = false;
    }
}
