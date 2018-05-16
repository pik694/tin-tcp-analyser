//
//  utils.swift
//  tcp_analyser
//
//  Created by Piotr Żelazko on 16.05.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

import Foundation


class Utils{
    class func getIPAddress() -> String? {
        var address: String?
        var ifaddr: UnsafeMutablePointer<ifaddrs>? = nil
        if getifaddrs(&ifaddr) == 0 {
            var ptr = ifaddr
            while ptr != nil {
                defer {
                    ptr = ptr?.pointee.ifa_next
                }
                
                let interface = ptr?.pointee
                let addrFamily = interface?.ifa_addr.pointee.sa_family
                if addrFamily == UInt8(AF_INET) || addrFamily == UInt8(AF_INET6) {
                    
                    if let name: String = String(cString: (interface?.ifa_name)!), name == "en0" {
                        var hostname = [CChar](repeating: 0, count: Int(NI_MAXHOST))
                        getnameinfo(interface?.ifa_addr, socklen_t((interface?.ifa_addr.pointee.sa_len)!), &hostname, socklen_t(hostname.count), nil, socklen_t(0), NI_NUMERICHOST)
                        address = String(cString: hostname)
                    }
                }
            }
            freeifaddrs(ifaddr)
        }
        return address
    }
    
    class func getCurrentTime() -> String {
        let date = Date()
        let calender = Calendar.current
        let components = calender.dateComponents([.hour, .minute, .second, .nanosecond], from: date)
        
        let hour = components.hour
        let minute = components.minute
        let second = components.second
        let nanosecond = components.nanosecond
        
        return String(
            String(hour!)
                + ":" + String(minute!)
                + ":" + String(second!)
                + ":" + String(nanosecond!/1000000)
        )
    }
    
}



