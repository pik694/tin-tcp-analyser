package com.test.tcp_ip;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.util.Random;

public class Server_Sender extends Thread{

    public Socket server_socket;
    public PrintWriter writer;

    public Server_Sender(Socket server_socket){
        this.server_socket = server_socket;
    }

    @Override
    public void run() {
        try {
            writer = new PrintWriter(server_socket.getOutputStream());
            while(true){
                if(server_socket.isClosed())
                    break;
                Random rnd = new Random();
                char c = (char) (rnd.nextInt(26) + 'a');
                writer.write(c + "\n");
                writer.flush();
                System.out.println("server wyslal: " + c);
                try {
                    Thread.sleep(1000);
                }catch(InterruptedException e){
                    e.printStackTrace();
                }
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
