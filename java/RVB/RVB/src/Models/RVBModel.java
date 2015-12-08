package Models;

import java.util.Observable;
import java.util.Observer;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class RVBModel extends Observable implements Interfaces.RVBModel {
    public int[] rvb;
    
    public RVBModel() {
        
        rvb = new int[3];
        rvb[0] = 33;
        rvb[1] = 33;
        rvb[2] = 34;
        
    }

    public RVBModel(int r, int v, int b) {
        if(r + v + b != 100){
            throw new IllegalArgumentException("R + V + B doit être égale à 100");
        }
        
        this.rvb = new int[3];
        
        this.rvb[0] = r;
        this.rvb[1] = v;
        this.rvb[2] = b;
    }
    

    @Override
    public int getR() {
        return this.rvb[0];
    }

    @Override
    public int getV() {
        return this.rvb[1];
    }
    
    @Override
    public int getB() {
        return this.rvb[2];
    }   
    
    @Override
    public void setR(int r) {
        this.rvb[0] = r;
        balanceValues(0);
    }

    @Override
    public void setV(int v) {
        this.rvb[1] = v;
        balanceValues(1);
    }
    
    @Override
    public void setB(int b) {
        this.rvb[2] = b;
        balanceValues(2);
    }

    /**
     * Permet d'équilibrer les valeurs RVD, sans toucher la valeur idx
     * @param idx L'idx à ne pas modifier (1 = rouge, 2 = vert, 3 = bleu)
     */
    public void balanceValues(int idx){
        
        int total = 0, restant = 0, totalV = 0;
        
        for(int i=0; i<3; i++){
             if(i != idx){
                 total += this.rvb[i]; 
             }
         }
         
        total = (total == 0)? 1 : total;
        
        restant = 100 - this.rvb[idx];
        
        for(int i=0; i<3; i++){
            if(i != idx){
                this.rvb[i] = Math.round((float)(restant * this.rvb[i]) / total);
                totalV += this.rvb[i];
            }
        }
         
         
        //Correction crado pour éviter "101", voir TestRVB
        if(totalV != restant){
            for(int i=0; i<3; i++){
                if(i != idx){
                    this.rvb[i] -= 1;
                    break;
                }
            }
        }
        
        super.setChanged();
        super.notifyObservers();
    }
    
    public void balancesValuesWithoutRatio(int idx){
        int total = 100 - get(idx);
        
        boolean pair = false;
        int reponse[] = new int[2];
        
        if((total%2) == 1){
            pair = true;
            reponse[0] = total/2;
            reponse[1] = total/2 + 1;
        } else {
            reponse[0] = total/2;
            reponse[1] = total/2;
        }
        
        int j=0;
        for(int i=0; i<3; i++){
            if(i != idx){
                this.rvb[i] = reponse[j];
                j++;
            }
        }
        
        super.setChanged();
        super.notifyObservers();
    }
    
    @Override
    public int get(int idx) {
        return this.rvb[idx];
    }

    @Override
    public void set(int idx, int value) {
        this.rvb[idx] = value;
        balanceValues(idx);
    }
}
