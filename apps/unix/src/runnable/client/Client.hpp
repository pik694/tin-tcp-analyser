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

        void sendMessageAsync(const std::string& message);

        ~Client() override = default;

    private:
        struct message_t{
            message_t(const std::string& message);
            char* data;
            size_t length;
            ~message_t();
        };


        void handleConnect(const boost::system::error_code& error);

        void handleReadHeader(const boost::system::error_code& error);
        void handleReadMessage(const boost::system::error_code& error);

        void queueMessage(std::string message);
        void handleSendMessage(const boost::system::error_code& error);


        void close();

        boost::asio::io_context context_;
        boost::asio::ip::tcp::socket socket_;

        size_t messageLength_ = 0;
        static const size_t MAX_MESSAGE_LENGTH = 1024;

        char rcvMessage_ [MAX_MESSAGE_LENGTH + 1];

        std::queue<std::unique_ptr<message_t>> queuedMessages_;



    };

}


#endif //UNIX_TCP_ANALYSER_CLIENT_HPP
