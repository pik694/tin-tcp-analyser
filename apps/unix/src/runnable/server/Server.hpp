//
// Created by Piotr Żelazko on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_SERVER_HPP
#define UNIX_TCP_ANALYSER_SERVER_HPP

#include <runnable/Runnable.h>

namespace tcp_analyser::runnable::server {
    class Server : public Runnable{
    public:
        Server(uint16_t port) {}

    };
}

#endif //UNIX_TCP_ANALYSER_SERVER_HPP
