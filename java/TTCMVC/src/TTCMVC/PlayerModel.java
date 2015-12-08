package TTCMVC;

import java.util.Observable;

/**
 * Classe qui permet d'avoir des informations sur le joueur
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class PlayerModel extends Observable{
    private String nom;
    private Symbol symbol;
    private boolean isDefined=false;

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public Symbol getSymbol() {
        return symbol;
    }

    public void setSymbol(Symbol symbol) {
        this.symbol = symbol;
    }
    
    public void playerIsDefined(){
        if(!isDefined){
            isDefined = true;
        } else {
            return;
        } 
        
        setChanged();
        notifyObservers();
    }
    
    public boolean isDefined(){
        return isDefined;
    }
}
