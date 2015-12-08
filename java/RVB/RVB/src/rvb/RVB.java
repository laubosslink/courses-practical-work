package rvb;

import java.awt.Color;
import javax.swing.JFrame;
import javax.swing.JPanel;
import Models.*;
import Views.*;
import Controllers.*;
/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class RVB {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        RVBModel model = new RVBModel();
        
        JPanel p = new GraphicalView(model, Color.RED, Color.GREEN, Color.BLUE);
        JFrame f = new JFrame("GraphicalView");
        f.setLocationRelativeTo(f.getContentPane());
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.getContentPane().add(p);
        f.pack();
        f.setVisible(true);
        
        TextFieldView textFieldView = new TextFieldView(model);
        TextFieldController tc = new TextFieldController(textFieldView, model);
        
        SliderView sv = new SliderView(model);
        SliderController sc = new SliderController(model, sv);
        
        TextualView textualView = new TextualView(model);
        RandomController rc = new RandomController(model);
        rc.go(10);
        
    }
}
