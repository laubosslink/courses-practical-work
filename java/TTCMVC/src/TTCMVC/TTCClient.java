package TTCMVC;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Proxy;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Observable;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TTCClient implements ActionListener {
    private GridView viewGrid;
    private Socket server;
    private GridModel modelGrid;
    
    private TTTController ttc;
    private PlayerModel player1, player2;
    
    public TTCClient(){
        super();
    }
    
    public void run() throws UnknownHostException, IOException, InterruptedException{
        server = new Socket(InetAddress.getLocalHost(), 9876);
        
        player1 = new PlayerModel();
        player2 = new PlayerModel();
        
        player1.setSymbol(Symbol.ROND);
        player2.setSymbol(Symbol.CROIX);
        
        PlayerView playerView = new PlayerView(player1);
        PlayerController playerController = new PlayerController(playerView, player1);
        
        playerView.getValidate().addActionListener(playerController);
        
        modelGrid = new GridModel();
        viewGrid = new GridView(modelGrid);
        
        ttc = new TTTController(viewGrid, playerView, player1, modelGrid, player2);
        
        for(int i=0; i<9; i++){
            
            viewGrid.getCases()[i].addActionListener(this); // L'ordre peut jouer un rôle important ! c'est le cas avec setCurrentPlayer qui est changé et pose problème dans le deuxième listener qui le lit, or entre temps il a changé... ATTENTION
            viewGrid.getCases()[i].addActionListener(ttc);
        }
        
        int input;
        modelGrid.setJ2Status("Joue");
        modelGrid.setJ1Status("Patientez");
        
        while(true){
            input = server.getInputStream().read();
            modelGrid.setGridSymbol(input, player2.getSymbol());
            ttc.setCurrentPlayer(player1);
            modelGrid.setJ1Status("C'est à vous");
            modelGrid.setJ2Status("Patiente");
        }
    }
    
    public static void main(String args[]) throws UnknownHostException, IOException, InterruptedException{
        new TTCClient().run();
    }
    
     @Override
    public void actionPerformed(ActionEvent ae) {
        for(int i=0; i<9; i++){
            if(viewGrid.getCases()[i] == ae.getSource() && ttc.getCurrentPlayer() == player1){
                try {
                    modelGrid.setJ1Status("Attendez");
                    modelGrid.setJ2Status("Joue");
                    server.getOutputStream().write(i);
                    ttc.setCurrentPlayer(player2);
                } catch (IOException ex) {
                    Logger.getLogger(TTTServer.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
}
