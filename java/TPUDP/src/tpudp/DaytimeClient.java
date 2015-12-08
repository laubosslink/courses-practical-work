package tpudp;

import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
import java.net.SocketException;

/*
 * En tête de 64 bits = 8 octet
 * (2^16) = 65 536 octet (car la longueur a une unité en octet)
 * On enlève les octet d'en-tête pour connaitre le nombre d'octets pour les données : 2^16-8 = 65 528
 * 
 * public class TPUDP {

    public static void main(String[] args) throws SocketException, IOException {
       
       
    }
}
 */

/*
 * Client Daytime en UDP
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class DaytimeClient {
    static public final int 
            DATESIZE = 29,
            SERVERPORT = 9876;
    
    private InetAddress server;
    private int serverPort;
    
    private DatagramSocket client;
    private String currentDate;
    
    public DaytimeClient(InetAddress server, int port) throws SocketException{
        this.serverPort = port;
        this.server = server;
        
        client = new DatagramSocket();
        client.setSoTimeout(3000);
    }
    
    public DaytimeClient() throws SocketException, UnknownHostException{
        this(InetAddress.getLocalHost(), SERVERPORT);
    }
    
    public void updateDate() throws UnknownHostException, IOException{
        
        DatagramPacket tmpPacket = new DatagramPacket(new byte[DATESIZE], DATESIZE, server, serverPort);
        client.send(tmpPacket);
        //tmpPacket.setLength(DATESIZE);
        client.receive(tmpPacket);
        
        currentDate = new String(tmpPacket.getData());
    }
        
    /**
     * Permet de récupérer la date à l'instant T ou on appel la méthode
     * @return la date actuelle
     */
    public String toString(){
        
        // Mise à jours de la date
        try {
            updateDate();
        } catch (UnknownHostException ex) {
            Logger.getLogger(DaytimeClient.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(DaytimeClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return currentDate;
    }
    
    public static void main(String args[]) throws SocketException, InterruptedException, UnknownHostException{
        
        /*
            DaytimeClient date = new DaytimeClient();
            System.out.println("le serveur donne la date actuelle : " + date);
            Thread.sleep(3000);
            System.out.println("3 secondes après le serveur répond : " + date);
        */
        
        if(args.length == 2){
            System.out.println(
                    new DaytimeClient(
                            InetAddress.getByName(args[0]), 
                            Integer.parseInt(args[1])
                            )
                    );
        }
    }
}
