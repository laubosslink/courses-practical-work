/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package misc.counter.v3;

/**
 * Class button listener
 * @author laubosslink <laubosslink@society-lbl.com>
 */
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 *
 * @author parmentl
 */
class ButtonListener implements ActionListener{
    protected Counter counter;
    
    public ButtonListener(Counter c){
        this.counter = c;
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("+")) {
            counter.changeValue(+1);
        } else {
            counter.changeValue(-1);
        }
    }
}
