//
// Created by Piotr Żelazko on 03.05.2018.
//

#include <iostream>
#include <thread>
#include <utils/Logger.hpp>
#include "Client.hpp"

using boost::asio::ip::tcp;
using tcp_analyser::utils::Logger;

tcp_analyser::runnable::client::Client::Client(std::string &hostname, uint16_t port) :
        hostname_(hostname),
        port_(port) {

}

void tcp_analyser::runnable::client::Client::run() {
    //TODO: think how to write this code
    //TODO: do not make it difficult ... KISS, it is just one app

//    stream_ = std::make_unique<tcp::iostream>(hostname_, std::to_string(port_));
//
//    if (!*stream_) {
//        throw std::runtime_error(stream_->error().message());
//    }

    std::thread sender (&Client::sendMessages, this);

    std::this_thread::sleep_for(std::chrono::seconds(2));


    sendMessageAsync("message");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    end_ = true;
    cv_.notify_all();

    sender.join();

}

void tcp_analyser::runnable::client::Client::sendMessageAsync(const std::string &message) {

    {
        std::unique_lock<std::mutex> lock(outQueueMutex_);
        outQueue_.emplace(message);
    }

    cv_.notify_one();
}

void tcp_analyser::runnable::client::Client::sendMessages() {

    while (true) {
        std::string message;
        {
            std::unique_lock<std::mutex> lock(outQueueMutex_);
            cv_.wait(lock, [this] { return !(this->outQueue_.empty()) || end_; });
            if (end_)
                break;

            message = outQueue_.front();
            outQueue_.pop();
        }

        std::cout << "Message: " <<  message << std::endl;
    }

}



