package Views;
import Models.*;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class SliderView extends JFrame implements Observer{
    private RVBModel model;
    private JSlider r, v, b;

    public JSlider getB() {
        return b;
    }

    public JSlider getR() {
        return r;
    }

    public JSlider getV() {
        return v;
    }
    
    public SliderView(RVBModel model){
        this.model = model;
        this.model.addObserver(this);
        
        setTitle("SliderView");
        setLayout(new GridLayout(3, 2));
        setSize(300, 300);
        
        add(new JLabel("R = "));
        
        r = new JSlider(JSlider.HORIZONTAL, 0, 100, model.getR());
        add(r);
        
        
        add(new JLabel("V = "));
        
        v = new JSlider(JSlider.HORIZONTAL, 0, 100, model.getV());
        add(v);
        
        
        add(new JLabel("B = "));
        
        b = new JSlider(JSlider.HORIZONTAL, 0, 100, model.getB());
        add(b);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    
    @Override
    public void update(Observable o, Object o1) {
        r.setValue(model.getR());
        v.setValue(model.getV());
        b.setValue(model.getB());
    }
}
