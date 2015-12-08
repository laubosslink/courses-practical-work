package chat;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.net.UnknownHostException;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextArea;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ReceptionView extends JFrame implements Observer{
    MsgModel model;
    JTextArea chatArea;
    JLabel info;
    JLabel users;
    
    public ReceptionView(MsgModel model){
        this.model = model;
        this.model.addObserver(this);
        
        setTitle("Réception des messages");
        setSize(800, 400);
        setLocationRelativeTo(this.getContentPane());
        setLayout(new BorderLayout());
        
        info = new JLabel("Chat : EMPTY");
        add(info, BorderLayout.PAGE_START);
        
        chatArea = new JTextArea();
        add(chatArea, BorderLayout.CENTER);
        
        users = new JLabel("Users : ");
        users.setPreferredSize(new Dimension(100, 400));
        add(users, BorderLayout.LINE_END);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    
    @Override
    public void update(Observable o, Object o1) {
        String data = "";
        
        if(o1 instanceof String){
            data = (String) o1; 
        }
        
        System.out.println(model.getCurrentChannel());
        System.out.println(model.getOption(1, data));
        
        if(model.getCmd(data).equals("/send") && model.getOption(1, data).equals(model.getCurrentChannel())){
            chatArea.setText(chatArea.getText() + "\n-" + model.getMsg(data));
        } 
        
        if(model.getCmd(data).equals("/join")){
            info.setText("Chat : " + model.getCurrentChannel());
        }
    }
    
    public static void main(String[] args) throws UnknownHostException{
        new ReceptionView(new MsgModel());
    }
}
