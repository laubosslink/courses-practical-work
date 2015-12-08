import java.util.Scanner;

public class Player {
	private String nom;
	private Scanner sc;
        private Symbol s;
	
        
	public Player(){
		this.sc = new Scanner(System.in);
		System.out.println("Veuillez entrer votre nom : ");
		this.nom = this.sc.nextLine();
                
                System.out.println("Veuillez entrer votre symbol (CROIX ou ROND) : ");
		this.s = Symbol.valueOf(sc.nextLine());
                
	}
        
	public void jouer(TTT t){
		int x, y;
		
                System.out.println(this.toString() + " joue...");
                
		do {
			System.out.print("Veuillez entrer une coordonnée x : ");
			x = this.sc.nextInt();
			System.out.print("Veuillez entrer une coordonnée y : ");
			y = this.sc.nextInt();
                        
                        // On ajuste les valeurs (par intuition, la coordonnée 1 vaut 0 dans le tableau java)
                        x--;
                        y--;
			
		} while(!t.isValidStep(x, y));
                
                t.setCoord(x, y, this.s);
		
	}
	
	public String toString(){
		String output="";
		output += "Joueur (nom) : " + this.nom;
		return output;
		
	}
	
}
