package Controllers;
import Views.*;
import Models.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JTextField;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TextFieldController implements ActionListener{
    private TextFieldView view;
    private RVBModel model;

    public TextFieldController(TextFieldView view, RVBModel model) {
        this.view = view;
        this.model = model;
        
        this.view.getR().addActionListener(this);
        this.view.getV().addActionListener(this);
        this.view.getB().addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        JTextField src = null;
        int srcInt = 0;
        
        if(ae.getSource() instanceof JTextField){
            src = (JTextField) ae.getSource();
            srcInt = Integer.parseInt(src.getText());
        
            if(src == this.view.getR()){
                this.model.setR(srcInt);
            } else if(ae.getSource() == this.view.getV()){
                this.model.setV(srcInt);
            } else if(ae.getSource() == this.view.getB()){
                this.model.setB(srcInt);
            }
        }
        
    }
}
