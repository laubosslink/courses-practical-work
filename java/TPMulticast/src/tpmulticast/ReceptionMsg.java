package tpmulticast;

import java.awt.GridLayout;
import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JTextArea;

/**
 * Classe permettant de s'inscrire a une adresse de diffusion et d'afficher les messages qui y sont reçus
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ReceptionMsg extends Thread{
    public static final String DEFAULT_IP="224.0.0.25";
    public static final int DEFAULT_PORT=9877, DEFAULT_SIZE_PACKET=150;
    
    private String ip;
    private int port;
    private MulticastSocket multicast;
    
    private boolean receptNode;

    /**
     * Initialisation/inscription de l'adresse de diff sur un port
     * @param ip L'ip à laquelle on veut s'abonner
     * @param port Le port d'écoute sur l'adresse de diffusion
     * @throws IOException 
     */
    public ReceptionMsg(String ip, int port) throws IOException {
        this.ip = ip;
        this.port = port;
    
        this.multicast = new MulticastSocket(port);
        this.multicast.joinGroup(InetAddress.getByName(ip));
    }
    
    /**
     * Lancement d'un noeud d'écoute
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
            
            System.out.println("<Debug> IP r : " + receivePacket.getAddress().toString());
            
            // Si l'ip de l'émetteur est égal à celle du récepteur on affiche pas le message
            //if(receivePacket.getAddress().toString() == )
            //System.out.println(NetworkInterface.getByName(InetAddress.getLocalHost().getCanonicalHostName()));
            
            System.out.println("-" + new String(receivePacket.getData())); //, receivePacket.getLength()
        }
    }
    
    /**
     * Pour le fun, on test une lecture en mode graphique
     * @throws IOException 
     */
    public void listenWithGui() throws IOException{
        receptNode = true;
        
        JFrame frame = new JFrame("Reception des Messages");
        frame.setSize(400, 400);
        frame.setLayout(new GridLayout(1, 1));
        
        JTextArea GUIDiffuseText = new JTextArea("Bonjour, je suis le récepteur :");
        GUIDiffuseText.setLineWrap(true);
        frame.add(GUIDiffuseText);
        
        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        
        byte[] byteReception;
        
        while(receptNode){
            // Il faut le mettre dans la boucle ! Sinon on le buffer qui contient le reste des messages précédents
            byteReception = new byte[DEFAULT_SIZE_PACKET];
            
            DatagramPacket receivePacket = new DatagramPacket(byteReception, byteReception.length);
                    
            this.multicast.receive(receivePacket);
            
            GUIDiffuseText.setText(GUIDiffuseText.getText() + "\n-" + new String(receivePacket.getData()));
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
            Logger.getLogger(ReceptionMsg.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void interrupt(){
        this.receptNode = false;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws SocketException, IOException, InterruptedException {
        ReceptionMsg rcpt;
        
        if(args.length == 2){
            rcpt = new ReceptionMsg(args[0], Integer.valueOf(args[1]));
        } else {
            rcpt = new ReceptionMsg(ReceptionMsg.DEFAULT_IP, ReceptionMsg.DEFAULT_PORT);
        }
        
        rcpt.listen();
        // Pour le fun :
        //rcpt.listenWithGui();
    }
}
