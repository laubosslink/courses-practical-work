/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package misc.convert.v3;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class Converter extends JPanel{
    protected JTextField value;
    protected JTextField convertedValue;
    final double EUROTOLIVRE=1.3056, LIVRETOEURO=0.7659; 
    
    public Converter(){
        setLayout(new GridLayout(1,4));
        
        value = new JTextField(0);
        JLabel euros = new JLabel("Euros");
        
        convertedValue = new JTextField(0);
        JLabel pounds = new JLabel("Pouns");
        
        add(value);
        add(euros);
        
        ActionListener l1 = new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent ae) {
                changeValue(1);
            }
        };
        
        ActionListener l2 = new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent ae) {
                changeValue(2);
            }
        };
        
        
        value.addActionListener(l1);
        convertedValue.addActionListener(l2);
        
        add(convertedValue);
        add(pounds);
        
    }
    
    public void changeValue(int i) {
        if(i == 1){
            convertedValue.setText(Double.toString(Double.parseDouble(value.getText()) * EUROTOLIVRE));
        } else if(i ==2){
            value.setText(Double.toString(Double.parseDouble(convertedValue.getText()) * LIVRETOEURO));
        }
    }
    
    public static void main(String[] args) {
        JFrame f = new JFrame("Counter");
        f.getContentPane().add(new Converter());
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.pack();
        f.setVisible(true);
    }
}
