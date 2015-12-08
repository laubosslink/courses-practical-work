/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pingpong;

import java.awt.Graphics;
import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class View extends JFrame implements Observer{
    private Model m;
    private Rond dessin;

    public Rond getDessin() {
        return dessin;
    }
    
    
    public View(Model m){
        this.m = m;
        this.m.addObserver(this);
        
        setTitle("Fenêtre");
        setSize(400, 400);
        setLocationRelativeTo(null);               
        
        setLayout(new GridLayout());
        
        dessin = new Rond();
        setContentPane(dessin);
        
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
 
    @Override
    public void update(Observable o, Object o1) {
        this.dessin.setX(this.m.getX((Integer) o1));
        this.dessin.setY(this.m.getY((Integer) o1));
        this.repaint();
    }
}
