package TTCMVC;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TTTController implements ActionListener{
    private GridModel modelGrid;
    private PlayerModel modelPlayer;
    private PlayerModel currentPlayer;
    
    private GridView viewGrid;
    private PlayerView viewPlayer;

    public PlayerModel getCurrentPlayer() {
        return currentPlayer;
    }

    public void setCurrentPlayer(PlayerModel currentPlayer) {
        this.currentPlayer = currentPlayer;
    }
    
    public TTTController(GridView viewGrid, PlayerView viewPlayer, PlayerModel modelPlayer, GridModel modelGrid,  PlayerModel currentPlayer) {
        
        this.modelPlayer = modelPlayer;
        this.modelGrid = modelGrid;
        this.currentPlayer = currentPlayer;
        
        this.viewPlayer = viewPlayer;
        this.viewGrid = viewGrid;
        
        PlayerController pc = new PlayerController(viewPlayer, modelPlayer);
        viewPlayer.getValidate().addActionListener(pc);
        
        while(!modelPlayer.isDefined()){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(TTTController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        viewGrid.open();
    }
    
    @Override
    public void actionPerformed(ActionEvent ae) {
        if(currentPlayer == modelPlayer){
            for(int i=0; i<9; i++){
                if(viewGrid.getCases()[i] == ae.getSource() && viewGrid.getCases()[i].getText() == Symbol.VIDE.toString()){
                    modelGrid.setGridSymbol(i, currentPlayer.getSymbol());
                }
            }
        } else {
            prevent("Ce n'est pas a votre tour !");
        }
    }
    
    public void prevent(String message){
        // On ouvre une fenêtre pour prévenir que ce n'est pas son tour
            JFrame f = new JFrame("ATTENTION");
            f.setLayout(new BorderLayout());
            f.getContentPane().add(new JLabel(message));
            f.setSize(300, 100);
            f.setVisible(true);
    }
}
