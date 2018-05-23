package com.test.tcp_ip;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

   public  TextView serverTextView;
   public  TextView clientTextView;
   public  EditText portEditView;
   public  TextView clientStatusTextView;
   public  TextView serverStatusTextView;
   public  EditText ipEditView;
   public  int connectionPort;
   public  String ipAddress;
   public  static Thread t1,t2;
   public static Handler handler;
   public final int DO_UPDATE_SERVER_TEXT_VIEW = 1;
   public final int DO_UPDATE_CLIENT_TEXT_VIEW = 2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        serverTextView       = (TextView)findViewById(R.id.serverTextView);
        clientStatusTextView = (TextView)findViewById(R.id.clientStatusTextView);
        serverStatusTextView = (TextView)findViewById(R.id.serverStatusTextView);
        clientTextView       = (TextView)findViewById(R.id.clientTextView);
        portEditView         = (EditText)findViewById(R.id.portEditView);
        ipEditView           = (EditText)findViewById(R.id.ipEditView);
        handler              = new Handler(Looper.getMainLooper()){
            @Override
            public void handleMessage (Message msg){
                int what = msg.what;
                switch(what){
                    case DO_UPDATE_SERVER_TEXT_VIEW:
                        updateServerTextView(msg.obj.toString());
                        break;
                    case DO_UPDATE_CLIENT_TEXT_VIEW:
                        updateClientTextView(msg.obj.toString());
                        break;
                    default:
                        break;
                }
            }
        };
    }



    public void startServer(View v){
        Server_Thread serverThread = new Server_Thread(serverTextView,connectionPort);
        t1 = new Thread(serverThread );
        t1.start();
        serverStatusTextView.setText("Server on");
    }

    public void startClient(View v){
        Client_Thread clientThread = new Client_Thread(clientTextView,connectionPort,ipAddress);
        t2 = new Thread(clientThread);
        t2.start();
        clientStatusTextView.setText("Client on");
    }

    public void confirmData(View v){
        ipAddress      = ipEditView.getText().toString();
        connectionPort = Integer.parseInt(portEditView.getText().toString());
    }

    public void updateServerTextView(String message){
        serverTextView.setText("client sent: " + message);
    }

    public void updateClientTextView(String message){
        clientTextView.setText("server sent: " + message);
    }
}
