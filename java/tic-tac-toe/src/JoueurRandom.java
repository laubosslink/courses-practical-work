
import batailleNavale.modele.BatailleNavale;
import batailleNavale.modele.CaseNotFoundException;
import batailleNavale.modele.Joueur;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author laubosslink
 */
public class JoueurRandom extends Joueur {

    public JoueurRandom(String name, BatailleNavale plateau) {
        super(name, plateau);
    }
    
    @Override
    public void joue() {
        try {
            Random r = new Random();
            int hauteur = r.nextInt(super.getModele().getHauteur());
            int largeur = r.nextInt(super.getModele().getLargeur());
            
            // 
            if(!super.getModele().estJoue(super.getModele().getJoueurCourant(), hauteur, largeur)){
                this.getModele().tir(hauteur, largeur);
                return;
            } else {
                this.joue();
            }
            
        } catch (CaseNotFoundException ex) {
            Logger.getLogger(JoueurRandom.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
