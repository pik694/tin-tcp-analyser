//
//  ClientViewController.swift
//  tcp_analyser
//
//  Created by Piotr Żelazko on 16.05.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

import UIKit
import SwiftSocket

class ClientViewController: UIViewController {
    
    let timeout : UInt32 = 3
    var shouldEnd = false
    
    enum ClientState: String {
        case disconnected = "Disconnected"
        case connected = "Connected"
        case connecting = "Connecting"
        case disconnecting = "Disconnecting"
    }
    
    var state_: ClientState = .disconnected
    
    var clientState : ClientState {
        get{
            return state_
        }
        set{
            DispatchQueue.main.async {
                self.state_ = newValue
                self.statusLabel.text = self.state_.rawValue
                self.hostnameField.resignFirstResponder()
                self.portField.resignFirstResponder()
                switch self.state_ {
                case .connected:
                    self.button.setTitle("Disconnect", for: .normal)
                    self.button.isEnabled = true
                    self.activityIndicator.stopAnimating()
                case .disconnected:
                    self.navigationItem.hidesBackButton = false
                    self.button.setTitle("Connect", for: .normal)
                    self.button.isEnabled = true
                    self.hostnameField.isEnabled = true
                    self.activityIndicator.stopAnimating()
                    self.portField.isEnabled = true
                case .connecting:
                    self.navigationItem.hidesBackButton = true
                    self.hostnameField.isEnabled = false
                    self.portField.isEnabled = false
                    fallthrough
                case .disconnecting:
                    self.activityIndicator.startAnimating()
                    self.button.isEnabled = false
                }
            }
        }
    }

    @IBOutlet weak var hostnameField: UITextField!
    @IBOutlet weak var portField: UITextField!

    @IBOutlet weak var statusLabel: UILabel!

    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!
    @IBOutlet weak var button: UIButton!
    @IBOutlet weak var logTextView: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        activityIndicator.hidesWhenStopped = true
    }
    
    @IBAction func clickedButton() {
        switch clientState {
        case .connected:
            clientState = .disconnecting
            DispatchQueue.main.asyncAfter(deadline: .now() + Double(timeout)*2){
                    self.clientState = .disconnected
            }
            shouldEnd = true
        case.disconnected:
            clientState = .connecting
            connect()
        default:
            print("Should not happen")
        }
    }
    
    func connect(){
        let client = TCPClient(address: hostnameField.text!, port: Int32(portField.text!)!)
        
        DispatchQueue.global(qos: .userInitiated).async {
            switch client.connect(timeout: Int(self.timeout)){
            case .success:
                self.clientState = .connected
                DispatchQueue.global(qos: .background).async {
                    self.send(client: client)
                }
                DispatchQueue.global(qos: .background).async {
                    self.receive(client: client)
                }
            case .failure(let error):
                self.log(error.localizedDescription)
                self.clientState = .disconnected
                client.close()
            }
        }
        
    }
    
    func send(client: TCPClient){
        if !shouldEnd {
            
            switch client.send(string: "Hello World!\n") {
            case .success:
                DispatchQueue.global(qos: .background).asyncAfter(deadline: .now() + Double(timeout)) {
                    self.send(client: client)
                }
            case.failure(let error):
                log(error.localizedDescription)
            }
        }
        else{
            client.send(string: "q")
        }
    }
    
    func receive(client: TCPClient){
        var message: String = ""
        while !shouldEnd {
            if let d = client.read(1, timeout: Int(timeout)) {
                if let character = String(bytes: d, encoding: String.Encoding.utf8) {
                    if character == "\n" {
                        log(message)
                        message.removeAll()
                    } else if character == "q" {
                        break;
                    } else {
                        message.append(character)
                    }
                }
            }
        }
        
        
        clientState = .disconnected
        client.close()
    }
    
    func log(_ log: String) {
        let message = "[\(Utils.getCurrentTime())]: \(log)\n"
        print(message)
        DispatchQueue.main.async {
            self.logTextView.text.append(message)
            self.logTextView.scrollToBottom()
        }
    }
}
