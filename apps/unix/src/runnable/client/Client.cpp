//
// Created by Piotr Żelazko on 03.05.2018.
//

#include <utils/Logger.hpp>
#include "Client.hpp"

using boost::asio::ip::tcp;
using tcp_analyser::utils::Logger;

tcp_analyser::runnable::client::Client::Client(std::string &&hostname, uint16_t port) :
        hostname_(hostname),
        port_(port) {

}

void tcp_analyser::runnable::client::Client::run() {
    try {
        tcp::socket socket(context_);
        tcp::resolver resolver(context_);

        boost::asio::connect(socket, resolver.resolve(hostname_, std::to_string(port_)));

    }
    catch (std::exception &e) {
        Logger::getInstance().log(e.what());
    }

}



