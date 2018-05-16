//
//  ViewController.swift
//  tcp_analyser
//
//  Created by Piotr Żelazko on 16.05.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

import UIKit
import SwiftSocket

class ServerController: UIViewController {

    let timeout: Int32 = 5

    var port: UInt = 8080

    enum ServerStatus: String {
        case running = "Running"
        case notRunning = "Not running"
        case stopping = "Stopping"
        case error = "Error"
        case starting = "Starting"
    }

    var shouldStop: Bool = false
    var status_: ServerStatus = .notRunning

    var serverStatus: ServerStatus {
        get {
            return status_
        }
        set(newValue) {
            DispatchQueue.main.async {
                self.portField.resignFirstResponder()
                self.status_ = newValue
                self.statusLabel.text = newValue.rawValue
                switch self.status_ {
                case .starting:
                    self.navigationItem.hidesBackButton = true
                    self.portField.isEnabled = false
                    self.button.isEnabled = false
                    self.activityIndicator.startAnimating()
                case .running:
                    self.activityIndicator.stopAnimating()
                    self.button.isEnabled = true
                    self.button.setTitle("Stop", for: .normal)
                case .notRunning:
                    self.navigationItem.hidesBackButton = false
                    self.activityIndicator.stopAnimating()
                    self.portField.isEnabled = true
                    self.button.setTitle("Start", for: .normal)
                    self.button.isEnabled = true
                case .stopping:
                    self.button.isEnabled = false
                    self.activityIndicator.startAnimating()
                case .error:
                    self.activityIndicator.stopAnimating()
                }
            }

        }
    }
    var clientsNo: Int {
        get {
            return Int(devicesNoLabel.text!)!
        }
        set {
            devicesNoLabel.text = String(newValue)
        }
    }

    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!
    @IBOutlet weak var button: UIButton!
    @IBOutlet weak var portField: UITextField!
    @IBOutlet weak var addressLabel: UILabel!
    @IBOutlet weak var logsView: UITextView!
    @IBOutlet weak var statusLabel: UILabel!
    @IBOutlet weak var devicesNoLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()

        clientsNo = 0
        activityIndicator.hidesWhenStopped = true
        addressLabel.text = Utils.getIPAddress()

        serverStatus = .notRunning

    }

    @IBAction func clickedButton(_ sender: UIButton) {

        switch serverStatus {
        case .notRunning:
            port = UInt(portField.text!)!
            serverStatus = .starting
            DispatchQueue.global(qos: .userInitiated).async(execute: startServer)
        case .running:
            serverStatus = .stopping
            shouldStop = true
            let delay: Double = 2 * Double(self.timeout)
            DispatchQueue.main.asyncAfter(deadline: .now() + delay) {
                self.serverStatus = .notRunning
            }
        default:
            print("Should not happen")
        }

    }


    func startServer() {
        if let address = Utils.getIPAddress() {
            let server = TCPServer(address: address, port: Int32(port))

            switch server.listen() {
            case .success:
                serverStatus = .running
                while !shouldStop {
                    if let client = server.accept(timeout: timeout) {
                        DispatchQueue.main.async {
                            self.clientsNo += 1
                        }
                        DispatchQueue.global(qos: .background).async {
                            self.receive(client: client)
                        }
                        DispatchQueue.global(qos: .background).async {
                            self.send(client: client)
                        }
                    }
                }
            case .failure(let error):
                print(error)
                serverStatus = .error
            }
            server.close()
        }
    }

    func log(_ log: String) {
        let message = "[\(Utils.getCurrentTime())]: \(log)\n"
        print(message)
        DispatchQueue.main.async {
            self.logsView.text.append(message)
            self.logsView.scrollToBottom()
        }
    }

    func receive(client: TCPClient) {

        log("New client from: \(client.address)\(client.port)")

        var message: String = ""
        while !shouldStop {
            if let d = client.read(1, timeout: Int(timeout)) {
                if let character = String(bytes: d, encoding: String.Encoding.utf8) {
                    if character == "\n" {
                        log("\(client.address):\(client.port) : " + message)
                        message.removeAll()
                    } else if character == "q" {
                        break;
                    } else {
                        message.append(character)
                    }
                }
            }
        }

        log("Client \(client.address):\(client.port) exiting");
        client.close()
        DispatchQueue.main.async {
            self.clientsNo -= 1
        }
    }

    func send(client: TCPClient) {

        switch client.send(string: "Some message\n") {
        case .success:
            DispatchQueue.global(qos: .background).asyncAfter(deadline: .now() + 10) {
                self.send(client: client)
            }
        case .failure(let error):
            print(error)
        }
    }


}

