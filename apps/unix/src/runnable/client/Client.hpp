//
// Created by Piotr Żelazko on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_CLIENT_HPP
#define UNIX_TCP_ANALYSER_CLIENT_HPP

#include <runnable/Runnable.h>
#include <boost/asio.hpp>
#include <queue>

namespace tcp_analyser::runnable::client {

    class Client : public Runnable{
    public:
        Client(std::string& hostname, uint16_t port);

        void run() override;

        ~Client() override = default;

    private:

        void handleConnect(const boost::system::error_code& error);

        void handleReadHeader(const boost::system::error_code& error);
        void handleReadMessage(const boost::system::error_code& error);

        void close();

        boost::asio::io_context context_;
        boost::asio::ip::tcp::socket socket_;

        size_t messageLength_ = 0;
        static const size_t MAX_MESSAGE_LENGTH = 1024;

        char message_ [MAX_MESSAGE_LENGTH + 1];
    };

}


#endif //UNIX_TCP_ANALYSER_CLIENT_HPP
