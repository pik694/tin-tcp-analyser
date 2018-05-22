//
// Created by Daniel Bigos on 16.05.18.
//

#ifndef UNIX_TCP_ANALYSER_SERVER_H
#define UNIX_TCP_ANALYSER_SERVER_H

#include <runnable/Runnable.h>

namespace  tcp_analyser::runnable::server
{
    class Server : public Runnable
    {
    public:
        Server() = delete;
        Server( const Server & ) = delete;
        Server &operator= ( const Server & ) = delete;
        Server( uint16_t port, std::vector< tcp_analyser::utils::system_api::options::TCPOptions_E > );
        virtual ~Server() = default;

        virtual void run() override;

    private:
        void send();
        void receive();

        uint16_t port_;

    };
}

#endif //UNIX_TCP_ANALYSER_SERVER_H
