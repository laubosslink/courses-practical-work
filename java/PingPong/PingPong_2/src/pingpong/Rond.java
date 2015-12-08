/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pingpong;

import java.awt.Graphics;
import javax.swing.JPanel;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class Rond extends JPanel {
    private int x, y;
    
    public int getX(){
        return x;
    }
    
    public int getY(){
        return y;
    }
    
    public void setX(int x){
        this.x = x/2;
    }
    
    public void setY(int y){
        this.y = y/2;
    }
    
    @Override
    public void paintComponent(Graphics g){
        if(x == 0 && y ==0){
            g.fillOval(0, 0, 0, 0);
        } else {
            g.fillOval(x, y, 10, 10);
        }
    }
}
