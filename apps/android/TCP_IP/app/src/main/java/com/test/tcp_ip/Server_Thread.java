package com.test.tcp_ip;

import android.content.Context;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Server_Thread implements Runnable{

    public ServerSocket serverSocket;
    public Socket socket;
    public TextView serverTextView;
    public int connectionPort;

    public Server_Thread(TextView serverTextView, int connectionPort){
        this.serverTextView = serverTextView;
        this.connectionPort = connectionPort;
    }


    @Override
    public void run()  {
        try {
            System.out.println("serwer1");
            serverSocket = new ServerSocket(this.connectionPort);
            socket = serverSocket.accept();
            System.out.println("serwer2");
            new Server_Sender(socket).start();
            new Server_Receiver(socket, serverTextView, serverSocket).start();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
