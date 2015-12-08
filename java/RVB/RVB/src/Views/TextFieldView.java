/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Views;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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
public class TextFieldView extends JFrame implements Observer {
    Models.RVBModel model;
    JTextField r, v, b;

    public JTextField getB() {
        return b;
    }

    public JTextField getR() {
        return r;
    }

    public JTextField getV() {
        return v;
    }
    
    public TextFieldView(Models.RVBModel model) {
        this.model = model;
        model.addObserver(this);
        
        setSize(200, 200);
        setLayout(new GridLayout(3, 2));
        
        r = new JTextField();
        v = new JTextField();
        b = new JTextField();
        
        add(new JLabel("R = "));
        add(r);
        
        add(new JLabel("V = "));
        add(v);
        
        add(new JLabel("B = "));
        add(b);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    @Override
    public void update(Observable o, Object o1) {
        r.setText(Integer.toString(model.getR()));
        
        v.setText(Integer.toString(model.getV()));
        
        b.setText(Integer.toString(model.getB()));
        
    }
    
}
