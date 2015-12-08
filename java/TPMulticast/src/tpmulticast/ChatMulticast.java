package tpmulticast;

import java.io.IOException;
import java.util.Scanner;

/**
 * Préliminaires :
 * Q1 : 224.0.19.0-224.0.19.63 Walt Disney Company
 */

/**
 * Classe permettant de lancer un chat utilisant ReceptionMsg et DiffuseMsg
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ChatMulticast {
    public static void main(String[] args) throws IOException, InterruptedException{
        ReceptionMsg rcpt;
        DiffuseMsg diff;
        
        if(args.length == 2){
            rcpt = new ReceptionMsg(args[0], Integer.valueOf(args[1]));
            diff = new DiffuseMsg(args[0], Integer.valueOf(args[1]));
        } else {
            //System.out.println("Veuillez spécifier une IP et un Port");
            rcpt = new ReceptionMsg(ReceptionMsg.DEFAULT_IP, ReceptionMsg.DEFAULT_PORT);
            diff = new DiffuseMsg(DiffuseMsg.DEFAULT_IP, DiffuseMsg.DEFAULT_PORT);
        }
        
        // On démarre un thread pour écouter l'adresse de diffusion
        rcpt.start();
        
        String reponse;
        
        // On doit pouvoir écrire !
        do{
            Scanner sc = new Scanner(System.in);
            reponse = sc.nextLine();
            
            // Envoie du message 
            diff.send(reponse);
        } while(!reponse.toLowerCase().equals("bye"));
        
        rcpt.interrupt();
    }
}
