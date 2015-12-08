package TTCMVC;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class PlayerController implements ActionListener {
    PlayerView playerView;
    PlayerModel playerModel;

    public PlayerController(PlayerView pv, PlayerModel pm) {
        this.playerView = pv;
        this.playerModel = pm;
    }
    
    @Override
    public void actionPerformed(ActionEvent ae) {
        if(ae.getSource().equals(playerView.getValidate()) && !playerModel.isDefined()){
            playerModel.setNom(playerView.getNom().getText());
            playerModel.playerIsDefined();
            playerView.close();
        } else {
            System.out.println("Le joueur " + playerModel.getNom() + " est déjà définit..");
        }
    }

}
