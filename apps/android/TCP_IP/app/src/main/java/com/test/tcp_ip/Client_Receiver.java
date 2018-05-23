package com.test.tcp_ip;

import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client_Receiver extends Thread {

    public Socket client_socket;
    public BufferedReader reader;
    public String message;
    public TextView clientTextView;

    public Client_Receiver(Socket client_socket, TextView clientTextView){
        this.client_socket = client_socket;
        this.clientTextView = clientTextView;

    }

    @Override
    public void run() {
        try {
            reader = new BufferedReader(new InputStreamReader(client_socket.getInputStream()));
            do{
                message = reader.readLine();
                System.out.println("client odebral: " + message);
            }while(!message.contains("q"));
            client_socket.close();
        }catch(Exception e){
            System.out.println("koniec polaczenia");
            e.printStackTrace();
        }finally {
            try {
                client_socket.close();
            } catch(IOException e) {
                e.printStackTrace();
            }
        }
    }
}
