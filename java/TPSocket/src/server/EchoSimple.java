/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Le premier serveur echo (pas de thread)
 * @author laubosslink
 */
public class EchoSimple {

    public static void main(String[] args) throws IOException {
        System.out.print("Lancement du service ... ");
        
        ServerSocket server = new ServerSocket(9876);
        
        if(server.isBound()){
            System.out.println("OK");
        }
        
        Socket client;
        
        PrintWriter envoie_client;
        BufferedReader reception_client;
        String chaine_client="";
        int clientCount=0, liveCountClient=0;
        
        while(true){
            client = server.accept();
            System.out.println("Connexion d'un client");
            clientCount++;
            liveCountClient++; // Inutile avec l'absence de thread, mais réponse à la question du tp...
            
            System.out.println("Envoi d'un message de bienvenue");
            envoie_client = new PrintWriter(client.getOutputStream());
            envoie_client.println("Bienvenue, vous êtes le client" + clientCount);
            envoie_client.flush();
            
            System.out.println("Demande d'instructions");
            envoie_client.println("J'attends vos instructions");
            envoie_client.flush();
            
            do{
                reception_client = new BufferedReader(new InputStreamReader(client.getInputStream()));
                chaine_client = reception_client.readLine();
                
                System.out.println("Reçu : " + chaine_client);
                
                if(!chaine_client.toLowerCase().equals("bye")){
                    System.out.println("Envoi : " + chaine_client);

                    envoie_client.println(chaine_client);
                    envoie_client.flush();
                } 
                
            }while(!chaine_client.toLowerCase().equals("bye"));
            
            envoie_client.println("Fin de connexion, au revoir");
            envoie_client.flush();
            
            client.close();
            liveCountClient--;
            
            System.out.println("Fin de transmission client");
        }
    }
}
