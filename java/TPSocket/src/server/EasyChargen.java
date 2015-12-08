/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Un serveur chargen plus compréhensible
 * @author laubosslink
 */
public class EasyChargen {
    public static void main(String[] args) throws IOException, InterruptedException{
        ServerSocket chargen = new ServerSocket(9876);
        Socket client = chargen.accept();
        BufferedOutputStream br = new BufferedOutputStream(client.getOutputStream());
        
        // Liste des charactères chargen
        String s = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz";
       
        // D'après la norme, on affiche 72 caractères
        final int LONGUEUR=72;
        
        // D'après la norme, normalement on a 90 caractères
        final int MAX=s.length();
        
        // Pointeur de déplacement
        int debut=0;
        
        // On parcours 72 caractères, et à chaque tour de boucle on se déplace
        while(true){
            
            // On cherche nos 72 caractères
            for(int i=debut; i<debut+LONGUEUR; i++){
                
                /* Si notre i (nième) caractère est inférieur à 90 (nombre de caractères total dans la chaine s pour chargen)
                * Alors on ajout i (nième) caractère de la chaine s dans le buffer
                * Sinon, on ajout i (nième) modulo 90 
                */
                
                if(i<MAX){
                    br.write(s.charAt(i));
                } else {
                    br.write(s.charAt(i%MAX));
                }
            }
            
            // Ajout du retour à la ligne
            br.write((byte) '\n');
            
            // Envoie du buffer
            br.flush();
            
            // Incrémentation du pointeur 
            debut++;
            
            // Notre pointeur à fait l'ensemble de la chaine ? On repart du début
            debut %= MAX;
            
            // Permet d'avoir un affichage lisible humainement !
            Thread.sleep(50);
        }

    }
}
