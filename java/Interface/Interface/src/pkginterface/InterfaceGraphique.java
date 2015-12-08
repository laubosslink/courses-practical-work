/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkginterface;
import java.awt.*;
import javax.swing.*;

/**
 *
 * @author parmentl
 */
public class InterfaceGraphique extends JFrame {
   public InterfaceGraphique(){             
      this.setTitle("Ma première fenêtre Java");
      this.setSize(400, 100);
      this.setLocationRelativeTo(null);               
 
      //Instanciation d'un objet JPanel
      JPanel pan = new JPanel();
      //Définition de sa couleur de fond
      pan.setBackground(Color.ORANGE);   
      
      //On prévient notre JFrame que notre JPanel sera son content pane
      this.setContentPane(pan);
      
      GridLayout gl = new GridLayout(3, 3);
      gl.setHgap(5); //Cinq pixels d'espace entre les colonnes (H comme Horizontal)
      gl.setVgap(5); //Cinq pixels d'espace entre les lignes (V comme Vertical) 
      //Ou en abrégé : GridLayout gl = new GridLayout(3, 2, 5, 5);

      this.setLayout(gl);

      for(int i=1; i<10; i++){
          this.getContentPane().add(new JButton(Integer.toString(i)));
      }
              
      this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      this.setVisible(true);
   }        
   
   public static void main(String args[]){
       new InterfaceGraphique();
   }
}

