//
// Created by Daniel Bigos on 14.05.18.
//

#ifndef UNIX_TCP_ANALYSER_SACK_H
#define UNIX_TCP_ANALYSER_SACK_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{
    class Sack : public TCPOption
    {
    public:
        Sack();
        virtual ~Sack();
    };
}

#endif //UNIX_TCP_ANALYSER_SACK_H
