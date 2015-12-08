package chat;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.net.UnknownHostException;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ChatView extends JFrame implements Observer{
    MsgModel model;
    JTextArea chatArea;
    JTextField myMsg;
    JLabel info, users;
    JTextField salon;

    public JTextField getMyMsg() {
        return myMsg;
    }

    public JTextField getSalon() {
        return salon;
    }
    
    
    public ChatView(MsgModel model){
        this.model = model;
        this.model.addObserver(this);
        
        setTitle("Réception des messages");
        setSize(800, 400);
        setLocationRelativeTo(this.getContentPane());
        setLayout(new BorderLayout());
        
        info = new JLabel("Salon : EMPTY");
        add(info, BorderLayout.PAGE_START);
        
        salon = new JTextField("EMPTY");
        salon.setPreferredSize(new Dimension(100, 20));
        add(salon, BorderLayout.LINE_START);
        
        chatArea = new JTextArea("Bienvenue sur le chat :");
        add(chatArea, BorderLayout.CENTER);
        
        users = new JLabel("");
        users.setPreferredSize(new Dimension(100, 400));
        add(users, BorderLayout.LINE_END);
        
        myMsg = new JTextField();
        myMsg.setPreferredSize(new Dimension(100, 100));
        add(myMsg, BorderLayout.PAGE_END);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    
    @Override
    public void update(Observable o, Object o1) {
        String data = "";
        String login;
        
        if(o1 instanceof String){
            data = (String) o1; 
        }
        
        if(model.getCmd(data).equals("MSG")){
            login = model.getOption(2, data);
            chatArea.setText(chatArea.getText() + "\n" + login + " dit : " + model.getMsg(data));
            myMsg.setText("");
        }
        
        if(model.getCmd(data).equals("SALON")){
            info.setText("Salon actuel : " + model.getCurrentChannel());
            
            if(model.isLocalAddress(data)){
                myMsg.setText("");
                chatArea.setText("Bienvenue sur le salon " + model.getCurrentChannel());
            }
            
            users.setText(users.getText() + "\n" + model.getOption(2, data));
        }
    }
    
    public static void main(String[] args) throws UnknownHostException{
        new ChatView(new MsgModel());
    }
    
    public void close(){
        setVisible(false);
    }
}
