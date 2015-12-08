/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author laubosslink
 */
public class Echo{
    
    private ServerSocket server;
    private int countClient;
    private int simultClient;
    
    public Echo() throws IOException{
        simultClient = 0;
        countClient = 0;
        
        this.log("Lancement du service...");
        server = new ServerSocket(9876);
        
        if(server.isBound()){
            this.log("OK");
        }
    }
    
    public void listen() throws IOException{
        Socket client;
        
        while(true){
            client = server.accept();
            
            if(client.isConnected()){
                this.log("Connexion d'un client");
                new Client(client).start();
                countClient++;
            }
        }
    }
    
    // On pourrait à l'avenirs crée un système de log, et enregistrer dans un fichier
    public void log(String message){
        System.out.println(message);
    }
    
    // Création d'un sous classe (avec thread) pour chaque client
    public class Client extends Thread{
        Socket client;
        
        public Client(Socket client){
            this.client = client;
        }
        
        public void writeToClient(String message) throws IOException{
            this.client.getOutputStream().write((message + "\n").getBytes());
        }
        
        @Override
        public void run(){
            
            simultClient++;
            
            try {
                System.out.println("Envoie d'un message de bienvenue");
                writeToClient("Bienvenue vous êtes le client numéro " + countClient);
                writeToClient("Nombre de client simultanés : " + simultClient);
                System.out.println("Il y a " + simultClient + " client simultanés.");
                
                // Création du buffer pour la lecture
                BufferedReader br = new BufferedReader(new InputStreamReader(this.client.getInputStream()));
                
                String reception="";
                
                do{
                    reception = br.readLine();
                    
                    System.out.println("Reçu : " + reception);
                    
                    System.out.println("Envoi : " + reception);
                    writeToClient(reception);
                    
                }while(!reception.toLowerCase().equals("bye"));
                
                writeToClient("Fin de connexion, aurevoir");
                
                System.out.println("Fin de transmission client");
                
                simultClient--;
                this.client.close();
            } catch (IOException ex) {
                simultClient--;
                Logger.getLogger(Echo.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        }
    }
    
    public static void main(String[] args) throws IOException{
        new Echo().listen();
    }
}
