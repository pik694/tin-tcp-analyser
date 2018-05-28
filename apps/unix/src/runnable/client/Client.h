//
// Created by Daniel Bigos on 15.05.18.
//

#ifndef UNIX_TCP_ANALYSER_CLIENT_H
#define UNIX_TCP_ANALYSER_CLIENT_H

#include <runnable/Runnable.h>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

const std::string CLIENT_MESSAGE = "Client message";

namespace tcp_analyser::runnable::client
{
    class Client : public Runnable
    {
    public:
        Client( std::string host, uint16_t port, std::vector< tcp_analyser::utils::system_api::options::TCPOptions_E > );

        Client() = delete;
        Client( const Client & ) = delete;
        Client &operator=( const Client & ) = delete;

        virtual ~Client() = default;

        virtual void run() override;

    private:

        void send();
        void receive();

        uint16_t port_;
        std::string hostname_;

    };
}

#endif //UNIX_TCP_ANALYSER_CLIENT_H
