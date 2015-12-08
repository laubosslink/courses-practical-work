/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Views;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import Controllers.RandomController;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TextualView implements Observer{
    String[] drapeau;
    Models.RVBModel rvb;

    public TextualView(Models.RVBModel rvb) {
        this.rvb = rvb;
        
        int taille = rvb.getB() + rvb.getR() + rvb.getV();
        drapeau = new String[100];
        
        rvb.addObserver(this);
    }
    
    
    public String toString(){
        String output = "";
        
        for(int r=0; r<rvb.getR(); r++){
            output += "R";
        }
        
        for(int v=0; v<rvb.getV(); v++){
            output += "V";
        }
        
        for(int b=0; b<rvb.getB(); b++){
            output += "B";
        }
        
        return output;
    }

    @Override
    public void update(Observable o, Object o1) {
        System.out.println(this);
    }
    
}
