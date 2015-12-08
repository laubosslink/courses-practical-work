package chat;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class ChatController implements ActionListener{
    ReceptMsg rcpt;
    DiffuseMsg diff;
    MsgModel model;
    ChatView view;
    
    public ChatController() throws IOException{
        model = new MsgModel();
        view = new ChatView(model);
        
        try {
            rcpt = new ReceptMsg(model);
            rcpt.start();
        } catch (IOException ex) {
            Logger.getLogger(ChatController.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        diff = new DiffuseMsg();
        view.getMyMsg().addActionListener(this);
        view.getSalon().addActionListener(this);
    }
    
    public static void main(String[] args) throws IOException{
        ChatController chat = new ChatController();
        
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        
        if(ae.getSource() == view.getMyMsg()){
            
            String dataRcv = view.getMyMsg().getText();
            
            if(!model.thereIsCmd(dataRcv)){
                try {
                    diff.send("MSG\n" + model.getCurrentChannel() + "\n" +model.getLogin() + "\n" + dataRcv);
                } catch (IOException ex) {
                    Logger.getLogger(ChatController.class.getName()).log(Level.SEVERE, null, ex);
                }
            } else {
                try {
                    String send_cmd = dataRcv.substring(1).replace(' ', '\n');
                    diff.send(send_cmd);
                } catch (IOException ex) {
                    Logger.getLogger(ChatController.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        } else if(ae.getSource() == view.getSalon()){
            try {
                diff.send("SALON\n" + view.getSalon().getText() + "\n" + model.getLogin());
            } catch (IOException ex) {
                Logger.getLogger(ChatController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
