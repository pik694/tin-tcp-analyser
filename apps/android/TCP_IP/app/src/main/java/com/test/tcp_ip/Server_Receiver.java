package com.test.tcp_ip;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
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
    public final int DO_UPDATE_SERVER_TEXT_VIEW = 1;
    public final int DO_UPDATE_SERVER_STATUS_TEXT_VIEW = 3;


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
                if(message != null ){
                    sendMessageToMainThread(message);
                }
            }while(!message.contains("q"));
            sendCahngeStatusToMainThread();
            server_socket.close();
            serverSocket.close();
            sendMessageToMainThread("Serwe zamknął socket");
        }catch(Exception e){
            try {
                sendCahngeStatusToMainThread();
                server_socket.close();
                serverSocket.close();
            }catch(Exception e2 ){
                sendMessageToMainThread(e2.getMessage());
            }
            sendMessageToMainThread(e.getMessage());
        }
    }

    public void sendMessageToMainThread(String message){
        Message msg = Message.obtain();
        msg.obj = message;
        msg.what = DO_UPDATE_SERVER_TEXT_VIEW;
        msg.setTarget(MainActivity.handler);
        msg.sendToTarget();
    }

    public void sendCahngeStatusToMainThread(){
        Message msg = Message.obtain();
        msg.what = DO_UPDATE_SERVER_STATUS_TEXT_VIEW;
        msg.setTarget(MainActivity.handler);
        msg.sendToTarget();
    }
}
