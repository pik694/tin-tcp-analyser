//
// Created by Daniel Bigos on 22.05.18.
//

#ifndef UNIX_TCP_ANALYSER_DSACK_H
#define UNIX_TCP_ANALYSER_DSACK_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{
    class DSack : public TCPOption
    {
    public:
        DSack();
        virtual ~DSack();
    };
}

#endif //UNIX_TCP_ANALYSER_DSACK_H
