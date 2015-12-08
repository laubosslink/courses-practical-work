package TTCMVC;

import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * La grille du tic tac toe
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class GridView extends JFrame implements Observer {
    private JButton[] cases;
    private JLabel j1Status, j2Status;
    private GridModel modelGrid;
    
    public JButton[] getCases() {
        return cases;
    }
    
    public GridView(GridModel gridModel) {
        this.modelGrid = gridModel;
        
        setLayout(new GridLayout(4, 3));
        
        setTitle("Tic Tac Toe");
        setLocationRelativeTo(getRootPane());
        
        setSize(500, 400);
        
        cases = new JButton[9];
        
        for(int i=0; i<9; i++){
            cases[i] = new JButton(Symbol.VIDE.toString());
            super.add(cases[i]);
        }
        
        j1Status = new JLabel("J1");
        j2Status = new JLabel("J2");
        
        add(new JLabel("Joueurs : "));
        add(j1Status);
        add(j2Status);
        
        this.modelGrid.addObserver(this);
    }
    
    @Override
    public void update(Observable o, Object o1) {
        for(int n=0; n<9; n++){
            cases[n].setText(modelGrid.getGrid(n).toString());
        }
        
        j1Status.setText("J1 : " + modelGrid.getJ1Status());
        j2Status.setText("J2 : " + modelGrid.getJ2Status());
    }
    
    public void open(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}
