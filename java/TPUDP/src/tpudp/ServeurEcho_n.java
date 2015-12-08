/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tpudp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

/**
 * Serveur Echo UDP multiplicateur
 * @author laubosslink <laubosslink@society-lbl.com>
 */

public class ServeurEcho_n {
    static public final int 
            DEFAULTPORT = 9876, 
            PAQUETSIZE = 8184;
    
    DatagramSocket server;
    
    public ServeurEcho_n() throws SocketException{
        this(DEFAULTPORT);
    }
    
    public ServeurEcho_n(int port) throws SocketException{
        server = new DatagramSocket(port);
    }
    
    /**
     * Permet de lancer le serveur
     */
    public void listen() throws IOException{
        DatagramPacket client;
        String clientString;
        
        // Ecoute en boucle
        while(true){
            // Création d'un paquet de réception, on ne peut connaitre la taille, donc taille max UDP
            client = new DatagramPacket(new byte[PAQUETSIZE], PAQUETSIZE);
            
            // Attente de la réception d'un paquet
            server.receive(client);
            
            // On a un client
            System.out.println("Reçu de " + client.getAddress());
            
            // On enregistre les données du paquet dans un chaine de caractère
            clientString = new String(client.getData());
            
            // Lecture de la taille de répétition de l'echo (multiplicateur)
            Integer multiplicateur = Integer.parseInt(clientString.split(":")[0]);
            
            // On enlève le multiplicateur de la chaine de caractère
            clientString = clientString.split(":")[1];
            
            // Affichage du multiplicateur
            System.out.println("Multiplicateur  : " + multiplicateur + ",");
            
            // Affichage de la phrase d'origine
            System.out.println("Phrase  : " + clientString + ".");
            
            System.out.println("");
            
            // On découte la chaine de caractère au niveau des espaces pour avoir un tableau
            String[] parseClientString = clientString.split(" ");
            
            String output="";
            
            // On utilise le multplicateur pour créer notre nouvelle chaine de caractère
            for(int i=0; i<parseClientString.length-1; i++){
                for(int j=0; j<multiplicateur; j++){
                    output += parseClientString[i] + " ";
                }
            }
            
            // Envoie d'un nouveau paquet, avec la taille de notre nouvelle chaine
            // Le client est configuré pour réceptionner cette taille, car il prépare un paquet
            // d'une taille équivalente en lisant lui aussi le multiplicateur de son côté
            server.send(new DatagramPacket(output.getBytes(), output.length(), client.getAddress(), client.getPort()));
        }
    }
    
    public static void main(String args[]) throws SocketException, IOException{
        // Lancement du serveur en écoute
        new ServeurEcho_n().listen();
    }
}
