
public class Grid {
	private Symbol[][] _grid;
	
	public Grid(){
		this._grid = new Symbol[3][3];
		this.initGrid();
	}
	
	public Grid(int taille){
                if(taille < 3){
                    System.out.println("Taille minimum de la grille : 3, on met à 3 par défaut.");
                    taille = 3;
                }
            
		this._grid = new Symbol[taille][taille];
		this.initGrid();
	}
	
	public void initGrid(){
		for(int i=0; i<this._grid.length; i++){
			for(int j=0; j<this._grid[i].length; j++){
				this._grid[i][j] = Symbol.VIDE;
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
		String output="";
		
                for(int j=0; j<this._grid[0].length; j++){
                    output += "_ ";
                }

                output += "\n";
                
		for(int i=0; i<this._grid.length; i++){
			for(int j=0; j<this._grid[i].length; j++){
				output += this._grid[i][j];
			}
		
                    output += "\n"; 
		}
		
                for(int j=0; j<this._grid[0].length; j++){
                    output += "_ ";
                }
                
                output += "\n";
                
		return output;
	}
	
	
	
}
