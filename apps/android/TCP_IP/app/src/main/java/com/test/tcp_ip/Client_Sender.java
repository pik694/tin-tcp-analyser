package com.test.tcp_ip;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;

public class Client_Sender extends Thread{

    public PrintWriter writer;
    public Socket client_socket;

    public Client_Sender(Socket client_socket){
        this.client_socket = client_socket;
    }

    @Override
    public void run() {
        try {
            writer = new PrintWriter(client_socket.getOutputStream());//, true);
            while(true){
                if(client_socket.isClosed())
                    break;
                Random rnd = new Random();
                char c = (char) (rnd.nextInt(26) + 'a');
                writer.write(c + "\n");
                System.out.println("client wyslal: " + c);
                writer.flush();
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
