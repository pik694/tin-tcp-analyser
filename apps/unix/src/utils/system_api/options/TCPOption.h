//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_TCPOPTION_H
#define UNIX_TCP_ANALYSER_TCPOPTION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string>

const unsigned  ENABLE = 1;
const unsigned DISABLE = 0;

namespace tcp_analyser::utils::system_api::options
{
    enum class TCPOptions_E
    {
        SACK = 4,
        TIMESTAMPS = 8
    };

    class TCPOption
    {
    public:
        TCPOption() = default;
        virtual ~TCPOption() = default;

    protected:
        bool enabled_ { false };
        std::string command_;
    };
}

#endif //UNIX_TCP_ANALYSER_TCPOPTION_H
