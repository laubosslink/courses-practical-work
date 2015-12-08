/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tpudp;

import java.io.*;
import java.net.*;
import java.util.*;


/**
 * Serveur Daytime en UDP
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class DaytimeServer {

    private DatagramSocket server;

    public DaytimeServer() throws SocketException {
            server = new DatagramSocket(9876);
    }

    public void listen() throws IOException {
        DatagramPacket client;
        
        while (true) {
            // Réception du paquet client (pour connaitre ip/port de retour)
            client = new DatagramPacket(new byte[1], 1);
            server.receive(client);

            // Récupération de la date actuelle
            Date now = Calendar.getInstance().getTime();
            
            // Changement des données du datagrame actuel
            client.setData(now.toString().getBytes());
            
            // Envoie du nouveau paquet avec la date
            server.send(client);
        }
    }

    public static void main(String[] args) throws IOException {
        // Création du serveur d'écoute
        new DaytimeServer().listen();
    }
}
