/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.iut.ap5.groupek.parmentier.laurent;

import java.util.Observable;

/**
 * Classe permettant de contenir la taille, masse, et de calculer l'imc
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ModeleIMC extends Observable {
    private double masse, taille;

    public ModeleIMC(){
        this(1, 1);
    }   
    
    public ModeleIMC(double masse, double taille) {
        if(taille <= 0){
            throw new IllegalArgumentException("La taille doit être supérieur à 0");
        }
        
        this.masse = masse;
        this.taille = taille;
    }

    public double getMasse() {
        return masse;
    }

    public void setMasse(double masse) {
        if(masse != this.masse){
            setChanged();
        }
        
        this.masse = masse;
        notifyObservers();
    }

    public double getTaille() {
        return taille;
    }

    public void setTaille(double taille) {
        if(taille <= 0 ){
            throw new IllegalArgumentException("La taille doit être supérieur à 0");
        }
        
        if(taille != this.taille){
            setChanged();
        }
        
        this.taille = taille;
        notifyObservers("tailleChanged");
    }
    
    public double getImc(){
        return masse / (taille * taille);
    }
    
    public String toString(){
        String output="";
        
        output += "Masse : " + this.getMasse() + " kg\n";
        
        output += "Taille : " + this.getTaille() +" m\n";
                
        output += "Imc  : " + this.getImc() + " kg.m-2";
        
        return output;
    }
    
    public String getOMS(){
        String output = "";
        
        if(this.getImc() < 16.5){
            output += "Dénutrition";
        } else if(this.getImc() >= 16.5 && this.getImc() < 18.5){
            output += "Maigreur";
        } else if(this.getImc() >= 18.5 && this.getImc() < 25){
            output += "Corpulence normale";
        } else if(this.getImc() >= 25 && this.getImc() < 30){
            output += "Surpoids";
        } else if(this.getImc() >= 30 && this.getImc() < 35){
            output += "Obésité modérée";
        } else if(this.getImc() >= 35 && this.getImc() < 40){
            output += "Obésité sévère";
        }  else {
            output += "Obésité morbide ou massive";
        }
        
        return output;
    }
    
    public boolean isValidDouble(String str){
        try{
            Double d = Double.valueOf(str);
            return true;
        } catch(Exception e){
            return false;
        }
    }
    
    public static void main(String[] args){
        ModeleIMC imc = new ModeleIMC(54, 1.6);
        System.out.println(imc);
        System.out.println("OMS : " + imc.getOMS());
        
        System.out.println();
        
        imc.setMasse(80);
        imc.setTaille(1.6);
        
        System.out.println(imc);
        System.out.println("OMS : " + imc.getOMS());
        
        System.out.println();
        
        imc.setMasse(80);
        imc.setTaille(2);
        
        System.out.println(imc);
        System.out.println("OMS : " + imc.getOMS());
        
        System.out.println();
        
        imc.setMasse(0);
        imc.setTaille(1);
        
        System.out.println(imc);
        System.out.println("OMS : " + imc.getOMS());
    }
}
