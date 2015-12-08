/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 *
 * @author parmentl
 */
public class DayTime {
    public static void main(String[] arg) throws UnknownHostException, IOException{
        
        // Connection au serveur local, sur le port 9876
        Socket s = new Socket(InetAddress.getLocalHost(), 9876);
        
        // Récupération du flux entrant
        InputStream is = s.getInputStream();
        
        // Création d'un buffer pour le flux entrant
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
                
        // Affichage des données du buffer
        System.out.println(br.readLine());
        
    }
}
