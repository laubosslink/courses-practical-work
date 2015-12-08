package TTTG;

import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.util.Locale;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class Grid extends JPanel{
	private Symbol[][] _grid;
        private JButton[][] _buttons;
        
	public Grid(){
                
                setLayout(new GridLayout(3, 3));
                
                _buttons = new JButton[3][3];
                
                for(int i=0; i<_buttons.length; i++){
                    for(int j=0; j<_buttons[i].length; j++){
                        _buttons[i][j] = new JButton(Integer.toString(i));
                        add(_buttons[i][j]);
                    }
                }
                
	}
	
	/*
	 * Permet de savoir si la grille est pleine
	 * @return boolean vrai si pleine
	 */
	public boolean isFull(){
		for(int i=0; i<this._grid.length; i++){
			for(int j=0; j<this._grid[i].length; j++){
				if(this._grid[i][j].equals(Symbol.VIDE)){
					return false;
				}
			}
		}
		
		return true;
	}
	
	public Symbol[][] getGrid(){
            return this._grid;
	}
        
        public void setGrid(int x, int y, Symbol s){
            this._grid[y][x] = s;
        }
	
	public String toString(){
		String output="Please use grapgic";
                
		return output;
	}
        
        
        public static void main(String args[]){
            JFrame f = new JFrame("Grid");
            f.setSize(400, 100);
            f.getContentPane().add(new Grid());
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.pack();
            f.setVisible(true);
        }
}
