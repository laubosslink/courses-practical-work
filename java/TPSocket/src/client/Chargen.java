/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author parmentl
 */
public class Chargen {   
    public static void main(String[] args) throws IOException{
        Socket s = new Socket(InetAddress.getLocalHost(), 9876);
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        
        while(true){
            try {
                System.out.println(br.readLine());
                Thread.sleep(1);
            } catch (InterruptedException ex) {
                Logger.getLogger(Chargen.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
