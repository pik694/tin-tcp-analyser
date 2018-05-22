//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_TCPOPTION_H
#define UNIX_TCP_ANALYSER_TCPOPTION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string>

const int ENABLE = 1;
const int DISABLE = 0;
const int UNDEFINED = -1;

const std::string FIFO  = "/tmp/tcp_analyser";

namespace tcp_analyser::utils::system_api::options
{
    enum class TCPOptions_E
    {
        SACK = 1,
        TIMESTAMPS = 2,
        DSACK = 3,
        FRTO = 4,
        ABC = 5,
        ALLOWED_CONGESTION_CONTROL = 6
    };

    class TCPOption
    {
    public:
        TCPOption() = delete;
        TCPOption( std::string option );
        virtual ~TCPOption() = default;

        void getOption();
        void setOption();
        void revertOption();

    protected:
        int value_ { UNDEFINED };
        std::string option_;
    };
}

#endif //UNIX_TCP_ANALYSER_TCPOPTION_H
