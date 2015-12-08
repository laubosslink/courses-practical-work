/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import batailleNavale.BatailleNavale;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author laubosslink
 */
public class BatailleNavaleTexte {
    private Scanner sc = new Scanner(System.in);
    private BatailleNavale b;
    
    public BatailleNavaleTexte(){
        Integer hauteur, largeur;
        
        System.out.println("Veuillez entrer la hauteur : ");
        hauteur = this.sc.nextInt();
        
        System.out.println("Veuillez entrer la largeur : ");
        largeur = this.sc.nextInt();
                
        this.b = new BatailleNavale(hauteur, largeur);
    }
    
    public void start(){
        System.out.println("Nom du joueur 1 : ");
        String joueur;
        
        joueur = this.sc.next();
        JoueurRandom j1 = new JoueurRandom(joueur, b);
        
        System.out.println("Nom du joueur 2 : ");
        joueur = this.sc.next();
        
        JoueurRandom j2 = new JoueurRandom(joueur, b);
        
        b.addJoueurs(j1, j2);
       
        b.ajouteBateauxRandom(0);
        b.ajouteBateauxRandom(1);
        
        b.run();
    }
    
}
