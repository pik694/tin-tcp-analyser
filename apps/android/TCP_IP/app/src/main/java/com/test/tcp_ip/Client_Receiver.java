package com.test.tcp_ip;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
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
    public final int DO_UPDATE_CLIENT_TEXT_VIEW = 2;
    public final int DO_UPDATE_CLIENT_STATUS_TEXT_VIEW = 4;

    public Client_Receiver(Socket client_socket, TextView clientTextView){
        this.client_socket = client_socket;
        this.clientTextView = clientTextView;
    }

    @Override
    public void run() {
        try {
            reader = new BufferedReader(new InputStreamReader(client_socket.getInputStream()));
            do {
                message = reader.readLine();
                System.out.println("client odebral: " + message);
                if (message != null) {
                    sendMessageToMainThread(message);
                }
            } while (!message.contains("q"));
            sendCahngeStatusToMainThread();
            sendMessageToMainThread("Klient zamknął socket");
            client_socket.close();
        } catch (Exception e) {
            try {
                sendCahngeStatusToMainThread();
                client_socket.close();
            } catch (Exception e2) {
                sendMessageToMainThread(e2.getMessage());
            }
            sendMessageToMainThread(e.getMessage());
        }
    }

    public void sendMessageToMainThread(String message){
        Message msg = Message.obtain();
        msg.obj = message;
        msg.what = DO_UPDATE_CLIENT_TEXT_VIEW;
        msg.setTarget(MainActivity.handler);
        msg.sendToTarget();
    }

    public void sendCahngeStatusToMainThread(){
        Message msg = Message.obtain();
        msg.what = DO_UPDATE_CLIENT_STATUS_TEXT_VIEW;
        msg.setTarget(MainActivity.handler);
        msg.sendToTarget();
    }
}
