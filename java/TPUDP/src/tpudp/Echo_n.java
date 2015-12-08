/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tpudp;

import java.io.IOException;
import java.net.*;
import java.util.EmptyStackException;

/**
 * Client Echo_n en UDP.
 * 
 * Explication : On utilise un paquet de même taille pour l'émission/réception
 * => optimisé pour que la taille du paquet envoyé, soit suffisant pour mettre la phrase de retours
 * Pourquoi ? Si on utilise deux paquets, l'un en émission avec la taille de la chaine entrée,
 * et l'un en réception (côté client) on ne peut pas connaitre la taille du paquet de réception
 * sans l'avoir reçu ! C'est pourquoi on utilise la taille max, avec un même paquet en émission/réception.
 * 
 * Remarque, pour une application plus complête et plus sérieuse, on pourrait envoyer un premier paquet
 * qui indique au serveur la taille du message, et le client pourrait envoyer un premier paquer pour indiquer
 * la taille du message de retour. A ce moment là, il faudrait gérer l'ordre des paquet, en y inscrivant dans
 * leur donnée un numéro pour pouvoir les ordonnées. Car en UDP, les paqets n'arrivent pas forcément dans le 
 * même ordre.
 * 
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class Echo_n {
    DatagramSocket client;
    
    public Echo_n() throws SocketException, UnknownHostException, IOException{
        client = new DatagramSocket();
        //client.setSoTimeout(3000); // optionel
    }
    
    /**
     * Permet d'obtenir le retour à partir d'un tableau de chaine de caractères.
     * Remarque utile pour la ligne de commande
     * @param args liste des arguments
     * @return l'echo avec nombre n de fois spécifié
     * @throws UnknownHostException
     * @throws IOException 
     */
    public String echo(String[] args) throws UnknownHostException, IOException{
        String output="";
        
        for(String concat : args){
            output += concat;
        }
        return echo(output);
    }
    
    /**
     * Permet d'obtenir le retour à partir d'une chaine de caractère
     * @param msg l'echo à envoyer
     * @return l'echo avec nombre n de fois spécifié
     * @throws UnknownHostException
     * @throws IOException 
     */
    public String echo(String msg) throws UnknownHostException, IOException{
        String output="";
        
         // Si on ne retrouve pas de : la chaine n'est pas correcte.
        if(!msg.contains(":")){
            System.out.println("Erreur :  \"" + msg + "\" n'est pas correcte.");
            throw new EmptyStackException();
        }
        
        // Longueur de la chaine
        int string_length = msg.length();
        
        // On agrandit le tableau de byte pour qu'il puisse en retours récepter la nouvelle phrase
        for(int i=0; i<Integer.parseInt(msg.split(":")[0]); i++){
            for(int j=0; j<string_length; j++){
                msg += " ";
            }
        }
        
        // Si la taille est inférieur ou égale à 0 on envoie une chaine vide, sinon l'echo auprès du serveur
        if(Integer.parseInt(msg.split(":")[0]) > 0){
            // Création du paquet (avec une taille adapté à la réception)
            DatagramPacket p = new DatagramPacket(msg.getBytes(), msg.length(), InetAddress.getLocalHost(), 9876);
            
            //Envoie du paquet pour que le serveur connaisse ip/port
            client.send(p);

            // Réception du résultat
            client.receive(p);
            
            output += "Résultat : " + new String(p.getData());
        } else {
            output += "";
        } 
        
        // Résultat final
        return output;
    }
    
    public static void main(String args[]) throws SocketException, UnknownHostException, IOException{
        // Si on a des arguments en ligne de commande, on traite, sinon on affiche un exemple
        if(args.length > 0){
            System.out.println(new Echo_n().echo(args));
        } else {
            System.out.println(new Echo_n().echo("10:Bonjour le monde"));
        }
    }
}
