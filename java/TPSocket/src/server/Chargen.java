/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


/**
 * Un serveur chargen optimisé (codé à la C)
 * @author laubosslink
 */
public class Chargen {
    public static void main(String[] args) throws IOException, InterruptedException{
        ServerSocket chargen = new ServerSocket(9876);
        Socket client = chargen.accept();
        BufferedOutputStream br = new BufferedOutputStream(client.getOutputStream());
        
        int x=0;
        
        while(true){
            
            /* Explication sur le parcours : 
             * 
             *  On se balade de l'élément 33+x à 105+x de la table ASCII (72 éléments)
             *  avec notre incrémentation x, pour se déplacer comme le veut la norme RFC864 (chargen)
             * 
             *  Remarque : Lorsque notre incrémentation x dépasse 18, on a 105+18=123 (soit le max, lettre z dans ASCII)
             *      Dans ce cas,
             *      On parcours non plus de l'élement 33+x à 105+x, mais 33+x au 123ème élément.
             *      Puis en même temps, on parcours de l'élement 33+x à 33+(x-18) car x vaut 19 quand on arrive pour la première fois dans else.
             *      => Quand on arrive au else pour la première fois, on affiche donc les élements d'ASCII alant de 33+19=52 à 123 soit 71 éléments
             *          et sachant que x = 19, on affiche 33 à 33+(x-18)=34 soit 1  élement en partant de 33.
             *          On a bien nos 72 éléments.
             * 
             * Pourquoi un algorithme "complexe" ?
             * 
             * Cette algorithme peut-être "peu" compréhensible, mais il est performant (pas trop d'utilisation de variables).
             * => Je pars de l'hyptohèse que la table ascii est suffisament stable depuis bien longtemps pour être sûr qu'elle
             * ne vas pas changer du jours au lendemain. Et il en est de même en ce qui concerne CHARGEN
             * Il n'y a donc pas d'intérêt de spécifier des variables inutiles en mémoire,
             * (cf. BASE=33, MAX=123, etc...) Ce qui pourrait rendre effectivement le code plus compréhensible, et évolutif. Mais moins
             * performant.
             */
            
            if(x <= 18){ 
                for(int i=33+x; i<105+x; i++){
                    br.write(i);
                }
            } else {
                for(int i=33+x; i<123; i++){
                    br.write(i);
                }

                for(int i=33; i<33+(x-18); i++){
                    br.write(i);
                }
            }

            br.write((byte) '\n');

            br.flush();

            x++;

            x %= 90;
        }

    }
}
