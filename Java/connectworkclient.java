import java.net.InetSocketAddress;
import java.net.Socket;
import java.io.BufferedOutputStream;
 
public class connectworkclient {
    private String address = "192.168.0.107";// ip
    private int port = 8765;// port
 
    public connectworkclient() {
 
        Socket client = new Socket();
        InetSocketAddress isa = new InetSocketAddress(this.address, this.port);
        try {
            client.connect(isa, 10000);
            BufferedOutputStream out = new BufferedOutputStream(client
                    .getOutputStream());
            // send string
            out.write("Send From Client ".getBytes());
            out.flush();
            out.close();
            out = null;
            client.close();
            client = null;
 
        } catch (java.io.IOException e) {
            System.out.println("Socket meet problem !");
            System.out.println("IOException :" + e.toString());
        }
    }
 
    public static void main(String args[]) {
        new connectworkclient();
    }
}