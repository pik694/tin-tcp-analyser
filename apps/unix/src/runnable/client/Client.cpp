//
// Created by Piotr Żelazko on 03.05.2018.
//

#include "Client.hpp"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

using boost::asio::ip::tcp;
//using tcp_analyser::utils::logger::Logger;

tcp_analyser::runnable::client::Client::Client(std::string &hostname, uint16_t port) :
        context_(),
        socket_(context_) {

    tcp::resolver resolver(context_);
    auto endpoints = resolver.resolve(hostname, std::to_string(port));

    boost::asio::async_connect(
            socket_,
            endpoints,
            boost::bind(&Client::handleConnect, this, boost::asio::placeholders::error)
    );
}

void tcp_analyser::runnable::client::Client::run() {

    boost::thread_group workers;

    for (int i = 0; i < 2; ++i)
        workers.create_thread(
                boost::bind(&boost::asio::io_context::run, &context_)
        );

    std::cout << "Press any key to exit\n";
    std::cin.get();

    boost::asio::post(context_, boost::bind(&Client::close, this));

    workers.join_all();
}

void tcp_analyser::runnable::client::Client::handleConnect(const boost::system::error_code &error) {
    if (!error) {
        boost::asio::async_read(
                socket_,
                boost::asio::buffer(&messageLength_, sizeof(messageLength_)),
                boost::bind(&Client::handleReadHeader, this, boost::asio::placeholders::error)
        );
    }
}

void tcp_analyser::runnable::client::Client::handleReadHeader(const boost::system::error_code &error) {
    //TODO: logger
    if (!error && messageLength_ < MAX_MESSAGE_LENGTH) {

        boost::asio::async_read(
                socket_,
                boost::asio::buffer(rcvMessage_, messageLength_),
                boost::bind(&Client::handleReadMessage, this, boost::asio::placeholders::error)
        );

    } else {
        boost::asio::post(context_, boost::bind(&Client::close, this));
    }

}

void tcp_analyser::runnable::client::Client::handleReadMessage(const boost::system::error_code &error) {
    //TODO: logger
    if (!error) {
        //Logger

        std::cout.write(rcvMessage_, messageLength_);

        boost::asio::async_read(
                socket_,
                boost::asio::buffer(&messageLength_, sizeof(messageLength_)),
                boost::bind(&Client::handleReadHeader, this, boost::asio::placeholders::error)
        );
    } else {
        boost::asio::post(context_, boost::bind(&Client::close, this));
    }
}

void tcp_analyser::runnable::client::Client::sendMessageAsync(const std::string &message) {
    boost::asio::post(
            context_,
            boost::bind(&Client::queueMessage, this, message)
    );
}

void tcp_analyser::runnable::client::Client::queueMessage(std::string message) {
    bool writeInProgress = !queuedMessages_.empty();

    queuedMessages_.emplace(new message_t(message));

    if (!writeInProgress) {

        boost::asio::async_write(
                socket_,
                boost::asio::buffer(queuedMessages_.front()->data, queuedMessages_.front()->length),
                boost::bind(&Client::handleSendMessage, this, boost::asio::placeholders::error)
        );
    }
}

void tcp_analyser::runnable::client::Client::handleSendMessage(const boost::system::error_code &error) {

    if (!error){
        queuedMessages_.pop();
        if (!queuedMessages_.empty())
            boost::asio::async_write(
                    socket_,
                    boost::asio::buffer(queuedMessages_.front()->data, queuedMessages_.front()->length),
                    boost::bind(&Client::handleSendMessage, this, boost::asio::placeholders::error)
            );
    }
    else {
        close();
    }
}


void tcp_analyser::runnable::client::Client::close() {
    socket_.close();
}

tcp_analyser::runnable::client::Client::message_t::message_t(const std::string &message) {

    length = message.size() + sizeof(size_t);
    data = new char[length + 1];

    *data = message.size();
    memcpy(const_cast<char*>(message.c_str()), data + sizeof(size_t), message.size());
}

tcp_analyser::runnable::client::Client::message_t::~message_t() {
    delete data;
}
