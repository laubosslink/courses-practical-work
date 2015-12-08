/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package misc.convert.v1;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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
        if (e.getActionCommand().equals("Euro -> Livre")) {
            counter.changeValue(1);
        } else if(e.getActionCommand().equals("Livre -> Euro")) {
            counter.changeValue(2);
        }
    }
}