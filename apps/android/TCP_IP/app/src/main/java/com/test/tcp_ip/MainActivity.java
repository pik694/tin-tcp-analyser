package com.test.tcp_ip;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

   public  TextView serverTextView;
   public  TextView clientTextView;
   public  EditText portEditView;
   public  EditText ipEditView;
   public  int connectionPort;
   public  String ipAddress;
   public  Thread t1,t2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        serverTextView = (TextView)findViewById(R.id.serverTextView);
        clientTextView = (TextView)findViewById(R.id.clientTextView);
        portEditView   = (EditText)findViewById(R.id.portEditView);
        ipEditView     = (EditText)findViewById(R.id.ipEditView);

    }


    public void startServer(View v){
        Server_Thread serverThread = new Server_Thread(serverTextView,connectionPort);
        t1 = new Thread(serverThread );
        t1.start();
    }

    public void startClient(View v){
        Client_Thread clientThread = new Client_Thread(clientTextView,connectionPort,ipAddress);
        t2 = new Thread(clientThread);
        t2.start();
    }

    public void confirmData(View v){
        ipAddress      = ipEditView.getText().toString();
        connectionPort = Integer.parseInt(portEditView.getText().toString());
    }
}
