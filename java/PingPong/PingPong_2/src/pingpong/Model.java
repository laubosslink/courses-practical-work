/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pingpong;

import java.util.Observable;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class Model extends Observable {
    private int x, y;
    private boolean jeton=false;

    public boolean isJeton() {
        return jeton;
    }

    public void setJeton(boolean jeton) {
        this.jeton = jeton;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
    
    public void setXY(int x, int y){
        if(!jeton){
            if(this.x != x){
                this.x = x;
                setChanged();
            }

            if(this.y != y){
                this.y = y;
                setChanged();
            }
            
            notifyObservers();
            this.jeton = true;
        }
    }
}
