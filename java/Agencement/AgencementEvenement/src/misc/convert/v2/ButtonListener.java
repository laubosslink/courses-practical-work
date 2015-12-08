/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package misc.convert.v2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JComboBox;
import misc.counter.v3.Counter;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
class ButtonListener implements ActionListener{
    protected Converter counter;
    
    public ButtonListener(Converter c){
        this.counter = c;
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        //System.out.println(e.getActionCommand().toString());
        //System.out.println(((JComboBox)e.getSource()).getSelectedItem().toString());
        
        if (((JComboBox)e.getSource()).getSelectedItem().toString().equals("Euro -> Livre")) {
            counter.changeValue(1);
        } else if(((JComboBox)e.getSource()).getSelectedItem().toString().equals("Livre -> Euro")) {
            counter.changeValue(2);
        }
    }
}