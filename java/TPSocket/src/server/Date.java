/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Calendar;

/**
 *
 * @author laubosslink
 */
public class Date {
    public static void main(String[] args) throws IOException{

        // Création d'un serveur sur le port d'écoute 9876
        ServerSocket s = new ServerSocket(9876);
        
        while(true){
            // Attente d'un client
            Socket client = s.accept();

            // Récupère la file de sortie vers le client
            OutputStream sortie = client.getOutputStream();

            // On récupère la date actuelle
            Calendar calendar = Calendar.getInstance();

            // On la parse dans un tableau de byte
            byte[] date = calendar.getTime().toString().getBytes();

            // On envoie le tableau de byte au client
            sortie.write(date);
            
            // On ferme la connexion
            client.close();
        }
    }
}
