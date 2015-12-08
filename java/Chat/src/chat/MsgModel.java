package chat;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Observable;

/** Classe permettant d'obtenir des infos sur un message
 * 
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class MsgModel extends Observable{
    private String currentChannel, myIp, login;
    private static final String SEPARATOR="\n";
    
    public MsgModel() throws UnknownHostException {
        myIp = InetAddress.getByName(InetAddress.getLocalHost().getCanonicalHostName()).getHostAddress();
        currentChannel = "";
        login = "An0nym0us";
    }

    public String getLogin() {
        return login;
    }

    public String getMyIp() {
        return myIp;
    }

    public String getCurrentChannel() {
        return currentChannel;
    }

    public void setCurrentChannel(String raw_data) {
        this.currentChannel = getSalon(raw_data);
        setChanged();
        notifyObservers(raw_data);
    }
    
    public void notifyCurrentMsg(String msg){
        setChanged();
        notifyObservers(msg);
    }
    
    public void receiveData(String raw_data){
        debug(raw_data);
        
        if(getCmd(raw_data).equals("MSG")){
            notifyCurrentMsg(raw_data);
        } else if(getCmd(raw_data).equals("SALON")){
            if(isLocalAddress(raw_data)){
                setCurrentChannel(raw_data);
            } 
            
            if(getSalon(raw_data).equals(currentChannel)) {
                notifyObservers(raw_data);
            }
        }
    }
    
    public String getCmd(String raw_data){
        return getData(raw_data).split(SEPARATOR)[0];
    }
    
    public String getOption(int i, String raw_data){
        return getData(raw_data).split(SEPARATOR)[i];
    }
    
    public String getSalon(String raw_data){
        if(getCmd(raw_data).equals("SALON")){
            return getOption(1, raw_data);
        } 
        
        return "";
    }
    
    public boolean isLocalAddress(String adr){
        if(getSrcHost(adr).equals(getMainIp()) || getSrcHost(adr).equals(getMyIp())){
            return true;
        }
        
        if(adr.equals("127.0.0.1") || adr.equals("127.0.1.1")){
            return true;
        }
        
        return false;
    }
    
    public String getSrcHost(String raw_data){
        return raw_data.split(":")[0];
    }
    
    public String getData(String data){
        return data.split(":")[1];
    }
    
    public String getMsg(String data){
        String output = "";
        String datas[] = getData(data).split(SEPARATOR);
        
        if(getCmd(data).equals("MSG")){
            for(int i=3; i<datas.length; i++){
                output += datas[i] + " ";
            }
        }
        
        return output;
    }
    
    public boolean thereIsCmd(String msg){
        if(msg.length() > 0){
            return msg.charAt(0) == '/';
        }
        
        return false;
    }
    
    // TODO delete this functions in futur
    public void debug(String msg){
        System.out.println("<debug>MsgModel : " + msg);
    }
    
    public static List<String> getIps() {
        List<String> ips = new ArrayList<String>();

        try {
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();

            while (interfaces.hasMoreElements()) {  // carte reseau trouvee
                NetworkInterface interfaceN = (NetworkInterface) interfaces.nextElement();
                Enumeration<InetAddress> ienum = interfaceN.getInetAddresses();
                while (ienum.hasMoreElements()) {  // retourne l adresse IPv4 et IPv6
                    InetAddress ia = ienum.nextElement();
                    String adress = ia.getHostAddress().toString();

                    if (adress.length() < 16) {          //On s'assure ainsi que l'adresse IP est bien IPv4
                        //System.out.println(ia.getHostAddress());
                        ips.add(ia.getHostAddress());
                    }

                    //ips.add(adress);
                }
            }
        } catch (Exception e) {
            System.out.println("pas de carte reseau");
            e.printStackTrace();
        }

        return ips;
    }
    
    public static String getMainIp(){
        return MsgModel.getIps().get(0);
    }
}
