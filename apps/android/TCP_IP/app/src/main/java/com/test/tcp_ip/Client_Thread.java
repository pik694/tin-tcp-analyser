package com.test.tcp_ip;

import android.os.AsyncTask;
import android.widget.TextView;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Client_Thread implements Runnable {

    public TextView clientTextView;
    public Socket clientSocket;
    public int connectionPort;
    public String ipAddress;

    public Client_Thread(TextView clientTextView, int connectionPort, String ipAddress){
        this.clientTextView = clientTextView;
        this.connectionPort = connectionPort;
        this.ipAddress = ipAddress;
    }

    @Override
        public void run()  {
        try {
            System.out.println("client1");
            clientSocket = new Socket(this.ipAddress, this.connectionPort);
            System.out.println("client2");
            new Client_Receiver(clientSocket, clientTextView).start();
            new Client_Sender(clientSocket).start();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
