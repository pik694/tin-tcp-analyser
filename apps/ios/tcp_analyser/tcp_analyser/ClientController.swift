//
//  ClientController.swift
//  tcp_analyser
//
//  Created by Piotr Żelazko on 16.05.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

import UIKit

class ClientController: UIViewController {

    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!
    
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        activityIndicator.hidesWhenStopped = true
        
    }

    
    @IBAction func clickedConnectButton(_ sender: UIButton) {
        
        let title = sender.currentTitle == "Connect" ? "Disconnect" : "Connect"
        sender.setTitle(title, for: UIControlState.normal)
        
        activityIndicator.isAnimating ? activityIndicator.stopAnimating() : activityIndicator.startAnimating()
        
    }

}
