package TTCMVC;

import java.util.Observable;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class GridModel extends Observable{
    private Symbol[][] grid;
    private String j1Status, j2Status;
    
    public GridModel(){
        grid = new Symbol[3][3];
        
        for(int y=0; y<grid.length; y++){
            for(int x=0; x<grid[y].length; x++){
                grid[y][x] = Symbol.VIDE;
            }
        }
    }
    
    public Symbol[][] getGrid(){
        return grid;
    }
    
    public Symbol getGrid(int n){
        return grid[(int)Math.floor(n/3)][n%3];
    }
    
    public void setGridSymbol(int n, Symbol s){
        int x, y;
        
        x = n % 3 ;
        y = (int) Math.floor(n / 3); // ceil pour la valeur la plus grande
        
        grid[y][x] = s;
        
        setChanged();
        notifyObservers();
    }
    
    public String getJ1Status() {
        return j1Status;
    }

    public void setJ1Status(String j1Status) {
        this.j1Status = j1Status;
        setChanged();
        notifyObservers();
    }

    public String getJ2Status() {
        return j2Status;
    }

    public void setJ2Status(String j2Status) {
        this.j2Status = j2Status;
        setChanged();
        notifyObservers();
    }
}
