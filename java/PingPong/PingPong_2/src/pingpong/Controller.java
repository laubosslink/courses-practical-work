/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pingpong;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class Controller implements MouseListener{
    private Model model;
    private View[] view;

    public Controller(Model model, View[] view) {
        this.model = model;
        this.view = view;
        
        for(int i=0; i<this.view.length; i++){
            this.view[i].getContentPane().addMouseListener(this);
        }
    }

    @Override
    public void mouseClicked(MouseEvent me) {
        for(int i=0; i<this.view.length; i++){
            if(this.view[i].getDessin() == me.getComponent()) {
                this.model.setJeton(false);
                this.model.setXY(0, 0);
            }
        }
        
        for(int i=0; i<this.view.length; i++){
            // Représente la fenêtre sur laquelle on clique
            if(this.view[i].getDessin() != me.getComponent()){
                // Sur cette fenêtre on lui donne les coordonnées de la souris
                this.model[i].setXY(me.getX(), me.getY()); // Le jeton sera mis à vrai
            }
        }
        
    }

    @Override
    public void mousePressed(MouseEvent me) { }

    @Override
    public void mouseReleased(MouseEvent me) {}

    @Override
    public void mouseEntered(MouseEvent me) {}

    @Override
    public void mouseExited(MouseEvent me) {}
    
    public static void main(String[] args){
        Model m = new Model();
        View[] v = {new View(m), new View(m), new View(m)};
        new Controller(m, v);
    }
}
