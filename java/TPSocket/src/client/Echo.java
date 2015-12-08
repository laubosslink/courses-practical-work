/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 *
 * @author parmentl
 */
public class Echo {
    public static void main(String[] args) throws UnknownHostException, IOException{
        Socket s = new Socket(InetAddress.getLocalHost(), 9876);
        
        // Crée un buffer pour l'entrée clavier
        BufferedReader clavier = new BufferedReader(new InputStreamReader(System.in));
        
        // Permet d'envoyer une chaine de caractères au serveur
        PrintWriter ps = new PrintWriter(s.getOutputStream(), true); 
        
        // Crée un buffer pour la réception
        BufferedReader reception = new BufferedReader(new InputStreamReader(s.getInputStream()));;
                
        String entree_clavier;
        String chaine_reception;
        
        do{ 
            //On récupère l'entrée clavier
            entree_clavier = clavier.readLine();
            
            // On envoie l'entrée clavie au serveur
            System.out.println("Envoie au serveur de : " + entree_clavier);
            ps.println(entree_clavier);
            
            chaine_reception = reception.readLine();
            System.out.println("Echo -> " + chaine_reception);
            
       } while(!entree_clavier.toLowerCase().equals("fin") || entree_clavier.equals("."));          
    }
}
