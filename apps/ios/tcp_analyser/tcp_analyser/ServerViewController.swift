//
//  ServerViewController.swift
//  tcp_analyser
//
//  Created by Piotr Żelazko on 16.05.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

import UIKit

import SwiftSocket

class ServerViewController: UIViewController {

    enum ServerState: String {

        case starting = "Starting"
        case notWorking = "Not working"
        case running = "Running"
        case error = "Error"

    }

    @IBOutlet weak var button: UIButton!

    @IBOutlet weak var portField: UITextField!

    @IBOutlet weak var ipLabel: UILabel!
    @IBOutlet weak var devicesNoLabel: UILabel!

    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!

    var state_: ServerState = ServerState.notWorking

    var serverState: ServerState {
        get {
            return state_
        }
        set(newValue) {
            state_ = newValue
            if newValue == ServerState.starting {
                activityIndicator.startAnimating()
            } else {
                activityIndicator.stopAnimating()
            }
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        activityIndicator.hidesWhenStopped = true
    }

    @IBAction
    func clickedButton(_ sender: UIButton) {

        switch state_ {
        case .notWorking:
            startServer()
        case .starting:
            stopServer()
        default:
            print("Other case")
        }


        devicesNoLabel.text = serverState.rawValue

    }

    func startServer() {


    }

    func stopServer() {

    }


}
