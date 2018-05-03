//
// Created by Piotr Żelazko on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_CLIENT_HPP
#define UNIX_TCP_ANALYSER_CLIENT_HPP

#include <runnable/Runnable.h>
#include <boost/asio.hpp>

namespace tcp_analyser::runnable::client {

    class Client : public Runnable{
    public:
        Client(std::string& hostname, uint16_t port);



        void run() override;

        ~Client() override = default;

    private:

        std::string hostname_;
        uint16_t port_;


        boost::asio::io_context context_;
    };

}


#endif //UNIX_TCP_ANALYSER_CLIENT_HPP
