/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkginterface;

import java.awt.*;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author parmentl
 */
public class GBC extends JFrame{
    public GBC(){
        
        this.setTitle("Test de GBC");
        this.setSize(600, 600);
        this.setLocationRelativeTo(null);

        // Création des cellules
        JButton celulleVerte = new JButton("1");
        celulleVerte.setBackground(Color.GREEN);
        celulleVerte.setPreferredSize(new Dimension(100, 100));
        
        JButton celulleVerte2 = new JButton("2");
        celulleVerte2.setBackground(Color.GREEN);
        celulleVerte2.setPreferredSize(new Dimension(100, 100));
        
        JButton celulleRed = new JButton("3");
        celulleRed.setBackground(Color.RED);
        celulleRed.setPreferredSize(new Dimension(100, 100));
        
        JButton celulleRed2 = new JButton("4");
        celulleRed2.setBackground(Color.RED);
        celulleRed2.setPreferredSize(new Dimension(100, 100));
        
        
        JButton celulleBlue = new JButton("5");
        celulleBlue.setBackground(Color.BLUE);
        celulleBlue.setPreferredSize(new Dimension(100, 100));
        
        JButton celulleBlue2 = new JButton("6");
        celulleBlue2.setBackground(Color.BLUE);
        celulleBlue2.setPreferredSize(new Dimension(100, 100));
        
        // Création du conteneur principale
        JPanel content = new JPanel();
        content.setPreferredSize(new Dimension(200, 100));
        content.setBackground(Color.WHITE);
        
        //On définit le layout manager
        content.setLayout(new GridBagLayout());
        
        // Maintenant on doit positionner nos cellules dans le conteneur principale
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        
        /*
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridheight = 2;
        gbc.gridwidth = 1;
        gbc.fill = GridBagConstraints.VERTICAL;
        
        content.add(celulleBlue, gbc);
        
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        
        content.add(celulleRed, gbc);
        
        
        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        
        content.add(celulleVerte, gbc);
        */
        
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridheight = 2;
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.gridwidth = 1;
        
        content.add(celulleRed, gbc);
        
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.gridheight = 3;
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.gridwidth = 1;
        
        content.add(celulleBlue, gbc);
        
        gbc.gridx = 2;
        gbc.gridy = 0;
        gbc.gridheight = 3;
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.gridwidth = 1;
        
        content.add(celulleRed2, gbc);
        
        gbc.gridx = 3;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.fill = GridBagConstraints.NONE;

        content.add(celulleVerte, gbc);
        
        gbc.gridx = 3;
        gbc.gridy = 1;
        gbc.gridheight = 1; // Si on met 2 pose probleme !
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        
        content.add(celulleBlue2, gbc);
        
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        //gbc.gridwidth = GridBagConstraints.REMAINDER; //A NE PAS FAIRE
        
        content.add(celulleVerte2, gbc);
        
        
        // Fermeture
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
        //On ajoute le conteneur
        this.setContentPane(content);

        this.setVisible(true);
    }
    
    public static void main(String[] args){
        new GBC();
    }
}
