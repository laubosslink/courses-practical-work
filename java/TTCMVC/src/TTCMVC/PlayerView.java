package TTCMVC;

import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class PlayerView extends JFrame{
    private PlayerModel playerModel;
    private JTextField nom, symbol;
    private JButton validate;
    private GridLayout layout;

    public JButton getValidate() {
        return validate;
    }

    public JTextField getNom() {
        return nom;
    }

    public JTextField getSymbol() {
        return symbol;
    }
    
    public PlayerView(PlayerModel playerModel){
        this.playerModel = playerModel;
        
        setTitle("Joueur : Inconnu");
        
        setSize(300, 300);
        
        layout = new GridLayout(3, 2);
        setLayout(layout);
        
        nom = new JTextField();
        add(new JLabel("Nom : "));
        add(nom);
        
        symbol = new JTextField();
        add(new JLabel("CROIX/ROND : "));
        //add(symbol);
        add(new JLabel(playerModel.getSymbol().toString()));
        
        validate = new JButton("yes");
        add(new JLabel("Valider : "));
        add(validate);
        
        //setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    
    public void close(){
        setVisible(false);
    }
}
