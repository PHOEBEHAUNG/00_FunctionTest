package phoebe.com.socket;

import java.net.ServerSocket;
import java.net.Socket;
public class connectwork extends java.lang.Thread {
 
    private boolean OutServer = false;
    private ServerSocket server;
    private final int ServerPort = 8765;// port
 
    public connectwork() {
        try {
            server = new ServerSocket(ServerPort);
 
        } catch (java.io.IOException e) {
            System.out.println("Socket is a problem !");
            System.out.println("IOException :" + e.toString());
        }
    }
 
    public void run() {
        Socket socket;
        java.io.BufferedInputStream in;
 
        System.out.println("server is running !");
        while (!OutServer) {
            socket = null;
            try {
                synchronized (server) {
                    socket = server.accept();
                }
                System.out.println("get connect : InetAddress = "
                        + socket.getInetAddress());
                // TimeOut
                socket.setSoTimeout(15000);
 
                in = new java.io.BufferedInputStream(socket.getInputStream());
                byte[] b = new byte[1024];
                String data = "";
                int length;
                while ((length = in.read(b)) > 0)// <=0 end
                {
                    data += new String(b, 0, length);
                }
 
                System.out.println("value:" + data);
                in.close();
                in = null;
                socket.close();
 
            } catch (java.io.IOException e) {
                System.out.println("Socket is a problem !");
                System.out.println("IOException :" + e.toString());
            }
 
        }
        System.out.println("server end!");
    }
 
    public static void main(String args[]) {
        (new connectwork()).start();
    }
 
}