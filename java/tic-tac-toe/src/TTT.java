import java.util.Scanner;

public class TTT {
	private Player _j1;
	private Player _j2;
	private Grid _g;
	private Player _currentPlayer;
        private boolean winner=false;
        
        public TTT(){
            this._j1 = new Player();
            this._j2 = new Player();
            this._g = new Grid();
        }
	
	public TTT(Player j1, Player j2, Grid g){
		this._j1 = j1;
		this._j2 = j2;
		this._g = g;
	}
	
	public void start(){
                System.out.println("Grille actuelle : ");
                System.out.println(this._g);

		while(!this._g.isFull() && !this.thereIsWinner()){
			this._currentPlayer = (this._j1 == this._currentPlayer) ? this._j2 : this._j1;
			this._currentPlayer.jouer(this);
                        
                        System.out.println("Grille actuelle : ");
                        System.out.println(this._g);
		}
             
                if(thereIsWinner()){
                    System.out.println(this._currentPlayer.toString() + " a gagné !");
                } else {
                    System.out.println("Il n'y a pas de gagnant....");
                }
	}
	
        /**
         * Quand on édite les coordonnées, on en profite pour vérifier qu'il n'y a pas de gagnant !
         * Ceci permet d'optimiser un maximum le script, et de vérifier juste aux alentours, plutôt que de controler
         * l'ensemble de la grille à chaque tour
         * @param x abscisse
         * @param y ordonnée
         * @param s  le symbole à positionner
         */
        public void setCoord(int x, int y, Symbol s){
            Symbol[][] g = this._g.getGrid();
            
            if(x > 1 && y > 1 && g[y-1][x-1].equals(s)){
                if(x > 2 && y > 2 && g[y-2][x-2].equals(s)){
                    this.winner = true;
                }
                
                if(x < g[y].length-1 && y < g.length-1 &&  g[y+1][x+1].equals(s)){
                    this.winner = true;
                }
            }
            
            if(x < g[y].length-2 && y < g.length-2 &&  g[y+1][x+1].equals(s) && g[y+2][x+2].equals(s)){
                this.winner = true;
            }
            
            // TODO deuxième diagonale
            
            // Horizontale
            
            if(x > 1 && g[y][x-1].equals(s)){
                if(x > 2 && g[y][x-2].equals(s)){
                    this.winner = true;
                }
                
                if(x < g[y].length-1 && g[y][x+1].equals(s)){
                    this.winner = true;
                }
            }
            
            if(x < g[y].length-2 && g[y][x+1].equals(s) && g[y][x+2].equals(s)){
                this.winner = true;
            }
            
            // Vertical
            
            if(y > 1 && g[y-1][x].equals(s)){
                if(y > 2 && g[y-2][x].equals(s)){
                    this.winner = true;
                }
                
                if(y < g.length-1 && g[y+1][x].equals(s)){
                    this.winner = true;
                }
            }
            
            if(y < g.length-2 && g[y+1][x].equals(s) && g[y+2][x].equals(s)){
                this.winner = true;
            }
            
            
            this._g.setGrid(x, y, s);
        }
        
	public boolean thereIsWinner(){
                /*
                int x=0;
                
		for(int i=0; i<this._g.getGrid().length-2; i++){
                    for(int j=0; j<this._g.getGrid()[i].length; j++){
                        if(!this._g.getGrid()[i][j].equals(Symbol.VIDE)){
                            // On controle la verticale
                            if(this._g.getGrid()[i][j].equals(this._g.getGrid()[i+1][j]) && this._g.getGrid()[i+1][j].equals(this._g.getGrid()[i+2][j])){
                                return true;
                            }
                        }
                    }   
		}
                
                for(int i=0; i<this._g.getGrid().length; i++){
                    for(int j=0; j<this._g.getGrid()[i].length-2; j++){
                        if(!this._g.getGrid()[i][j].equals(Symbol.VIDE)){
                            // On controle l'horizontale
                            if(this._g.getGrid()[i][j].equals(this._g.getGrid()[i][j+1]) && this._g.getGrid()[i][j+1].equals(this._g.getGrid()[i][j+2])){
                                return true;
                            }
                        }
                    }
                }
                
                for(int i=0; i<this._g.getGrid().length-2; i++){
                    for(int j=0; j<this._g.getGrid()[i].length-2; j++){
                        if(!this._g.getGrid()[i][j].equals(Symbol.VIDE)){
                            // On controle la diagonale
                            if(this._g.getGrid()[i][j].equals(this._g.getGrid()[i+1][j+1]) && this._g.getGrid()[i+1][j+1].equals(this._g.getGrid()[i+2][j+2])){
                                return true;
                            }
                        }
                    }
                } 
                
		return false;
                 */
                 return this.winner;
	}
	
	public boolean isValidStep(int x, int y){
            
                // Si on sort des limites, retourne false
                if(x >= this._g.getGrid()[0].length || y >= this._g.getGrid().length || x < 0 || y < 0){
                    return false;
                }
                
                // Si la case n'est pas vide retourne false
		if(!this._g.getGrid()[y][x].equals(Symbol.VIDE)){
                    return false;
                }
                
                return true;
	}
}
