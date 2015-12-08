/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.iut.ap5.groupek.parmentier.laurent;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class VueControleurIMC extends JPanel implements ActionListener, Observer{
    private ModeleIMC model;
    private JTextField masse, taille;
    private JLabel imc, oms;
    private JButton valider;
    
    public VueControleurIMC(ModeleIMC model) {
        this.model = model;
        model.addObserver(this);
        setLayout(new GridLayout(5, 2));
        
        add(new JLabel("Taille (m) : "));
        taille = new JTextField(Double.toString(model.getTaille()));
        taille.addActionListener(this);
        add(taille);
        
        add(new JLabel("Poids (kg) : "));
        masse = new JTextField(Double.toString(model.getMasse()));
        masse.addActionListener(this);
        add(masse);
        
        add(new JLabel("IMC (kg.m-2) : "));
        imc = new JLabel(Double.toString(model.getImc()));
        add(imc);
       
        add(new JLabel("OMS : "));
        oms = new JLabel();
        add(oms);
        
        valider = new JButton("Valider");
        valider.addActionListener(this);
        add(valider);
    }
    
    @Override
    public void actionPerformed(ActionEvent ae) {
        String value="";
        
        if(ae.getSource() == this.masse){
            value = this.masse.getText();
            if(this.model.isValidDouble(value)){
                this.model.setMasse(Double.parseDouble(value));
            }
            
        } else if(ae.getSource() == this.taille){
            value = this.taille.getText();
            if(this.model.isValidDouble(value)){
                this.model.setTaille(Double.parseDouble(this.taille.getText()));
            }
            
        } else if(ae.getSource() == this.valider){
            value = this.masse.getText();
            if(this.model.isValidDouble(value)){
                this.model.setMasse(Double.parseDouble(this.masse.getText()));
            }
            
            value = this.taille.getText();
            if(this.model.isValidDouble(value)){
                this.model.setTaille(Double.parseDouble(this.taille.getText()));
            }
        }
        
    }

    @Override
    public void update(Observable o, Object o1) {
            this.imc.setText(Double.toString(this.model.getImc()));
            this.oms.setText(this.model.getOMS());
    }
    
    public static void main(String[] args){
        ModeleIMC m = new ModeleIMC();
        VueControleurIMC vcIMC = new VueControleurIMC(m);
        
        JFrame f = new JFrame("Calcul IMC");
        f.setSize(400, 200);
        f.setLocationRelativeTo(f.getContentPane());
        
        f.getContentPane().add(vcIMC);
        
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);
    }
}
