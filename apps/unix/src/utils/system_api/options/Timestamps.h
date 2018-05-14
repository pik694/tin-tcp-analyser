//
// Created by Daniel Bigos on 14.05.18.
//

#ifndef UNIX_TCP_ANALYSER_TIMESTAMPS_H
#define UNIX_TCP_ANALYSER_TIMESTAMPS_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{
    class Timestamps : public TCPOption
    {
    public:
        Timestamps();

        virtual ~Timestamps();
    };
}

#endif //UNIX_TCP_ANALYSER_TIMESTAMPS_H
