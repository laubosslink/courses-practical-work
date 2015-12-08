package TTCMVC;

import com.sun.media.sound.ModelAbstractChannelMixer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Observable;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TTTServer implements ActionListener{
    ServerSocket server;
    Socket client;
    private GridView viewGrid;
    private GridModel modelGrid;
    private TTTController ttc;
    private PlayerModel player1, player2;
    
    public TTTServer(){
        super();
    }
    
    public void run() throws IOException, InterruptedException{
        server = new ServerSocket(9876);
        
        player1 = new PlayerModel();
        player2 = new PlayerModel();
        
        player1.setSymbol(Symbol.CROIX);
        player2.setSymbol(Symbol.ROND);
        
        PlayerView playerView = new PlayerView(player1);
        PlayerController playerController = new PlayerController(playerView, player1);
        
        playerView.getValidate().addActionListener(playerController);
        
        modelGrid = new GridModel();
        viewGrid = new GridView(modelGrid);
        
        ttc = new TTTController(viewGrid, playerView, player1, modelGrid, player1);
        
        for(int i=0; i<9; i++){
            viewGrid.getCases()[i].addActionListener(this);
            viewGrid.getCases()[i].addActionListener(ttc);
        }
        
        modelGrid.setJ1Status("Ready");
        modelGrid.setJ2Status("Waiting...");
        client = server.accept();
        modelGrid.setJ2Status("Ready");
        modelGrid.setJ1Status("C'est à vous");
            
        int input;
        
        while(true){
            input = client.getInputStream().read();
            ttc.setCurrentPlayer(player1);
            modelGrid.setGridSymbol(input, player2.getSymbol());
            modelGrid.setJ1Status("C'est à vous");
            modelGrid.setJ2Status("Patiente");
        }
    }
    
    public static void main(String args[]) throws IOException, InterruptedException{
        new TTTServer().run();
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        for(int i=0; i<9; i++){
            if(viewGrid.getCases()[i] == ae.getSource() && ttc.getCurrentPlayer() == player1){
                try {
                    modelGrid.setJ1Status("Attendez");
                    modelGrid.setJ2Status("Joue");
                    client.getOutputStream().write(i);
                    ttc.setCurrentPlayer(player2);
                } catch (IOException ex) {
                    Logger.getLogger(TTTServer.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
}
