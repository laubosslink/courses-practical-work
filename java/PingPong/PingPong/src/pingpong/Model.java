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
    private int x[], y[];
    private boolean jeton=false;

    public Model(int i){
        x = new int[i];
        y = new int[i];
    }
    
    public int getLength(){
        return x.length;
    }
    
    public boolean isJeton() {
        return jeton;
    }

    public void setJeton(boolean jeton) {
        this.jeton = jeton;
    }

    public int getX(int i) {
        return x[i];
    }

    public int getY(int i) {
        return y[i];
    }
    
    public void setXY(int i, int x, int y){
        //if(!jeton){
            if(this.x[i] != x){
                this.x[i] = x;
                setChanged();
            }

            if(this.y[i] != y){
                this.y[i] = y;
                setChanged();
            }
            
            notifyObservers(i);
            this.jeton = true;
        //}
    }
}
