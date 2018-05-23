package com.test.tcp_ip;

import android.app.Activity;
import android.content.Context;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Server_Receiver extends Thread{

    public Socket server_socket;
    public BufferedReader reader;
    public String message;
    public TextView serverTextView;
    public ServerSocket serverSocket;

    public Server_Receiver(Socket server_socket, TextView serverTextView, ServerSocket serverSocket){
        this.server_socket = server_socket;
        this.serverSocket = serverSocket;
        this.serverTextView = serverTextView;
    }

    @Override
    public void run() {
        try {
            reader = new BufferedReader(new InputStreamReader(server_socket.getInputStream()));
            do{
                message = reader.readLine();
                System.out.println("server odebral: " + message);

            }while(!message.contains("q"));
            server_socket.close();
            serverSocket.close();
        }catch(Exception e){
            System.out.println("koniec polaczenia");
            e.printStackTrace();
        }finally{
            try {
                server_socket.close();
                serverSocket.close();
            } catch(IOException e) {
                e.printStackTrace();
            }
        }
    }
}
