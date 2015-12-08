/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Controllers;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class RandomController {
    Models.RVBModel model;
    
    public RandomController(Models.RVBModel model){
        this.model = model;
    }
    
    public void go(int turn){
        for(int i=0; i<turn; i++){
            try {
                Thread.sleep(500);
            } catch (InterruptedException ex) {
                Logger.getLogger(RandomController.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            int idx = ((int) (Math.random()*100)) % 3;
            this.model.set(idx, (int) (Math.random()*100));
        }
    }
}
