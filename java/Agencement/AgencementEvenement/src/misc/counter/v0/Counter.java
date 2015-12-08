/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package misc.counter.v0;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.JFrame;

/**
 *
 * @author parmentl
 */
public class Counter extends JPanel implements ActionListener{
    protected JLabel value;
    
    public Counter(){
        setLayout(new GridLayout(2, 1));
        value = new JLabel("0", SwingConstants.CENTER);
        add(value);
        JPanel buttons = new JPanel();
        JButton inc = new JButton("+");
        JButton dec = new JButton("-");
        inc.addActionListener(this);
        dec.addActionListener(this);
        buttons.add(inc);
        buttons.add(dec);
        add(buttons);
    }

    public void changeValue(int i) {
        int newValue = Integer.parseInt(value.getText())+i;
        value.setText(""+newValue);
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("+")) {
            changeValue(+1);
        } else {
            changeValue(-1);
        }
    }
    
    public static void main(String[] args) {
        JFrame f = new JFrame("Counter");
        f.getContentPane().add(new Counter());
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.pack();
        f.setVisible(true);
    }
}