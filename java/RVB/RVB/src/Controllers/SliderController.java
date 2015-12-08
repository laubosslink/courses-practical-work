package Controllers;
import Views.*;
import Models.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class SliderController implements ChangeListener, MouseListener{
    private RVBModel model;
    private SliderView view;

    public SliderController(RVBModel model, SliderView view) {
        this.model = model;
        this.view = view;
        
        this.view.getR().addMouseListener(this);
        
        this.view.getV().addMouseListener(this);
        this.view.getB().addMouseListener(this);
    }

    @Override
    public void stateChanged(ChangeEvent ce) {
       //throw new UnsupportedOperationException("Not yet supported.");
        // Pas intéressant ! Dès que ca change, ca notifie, pose des problème sur ce modèle
    }

    @Override
    public void mouseClicked(MouseEvent me) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void mousePressed(MouseEvent me) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void mouseReleased(MouseEvent me) {
       JSlider src = (JSlider) me.getSource();
        
       //if(src.getValueIsAdjusting()){
            if(src == view.getR()){
                model.setR(src.getValue());
            } else if(src == view.getV()){
                model.setV(src.getValue());
            } else if(src == view.getB()){
                model.setB(src.getValue());
            }
       //}
    }

    @Override
    public void mouseEntered(MouseEvent me) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void mouseExited(MouseEvent me) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }
    
    
}
