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

        void sendMessages();
        void receiveMessages();

        void sendMessageAsync(const std::string& message);

        void waitForExit();


        std::mutex outQueueMutex_;
        std::condition_variable cv_;
        bool end_ = false;

        std::queue<std::string> outQueue_;



        std::string hostname_;
        uint16_t port_;

        std::unique_ptr<boost::asio::ip::tcp::iostream> stream_;
    };

}


#endif //UNIX_TCP_ANALYSER_CLIENT_HPP
