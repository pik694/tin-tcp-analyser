//
// Created by Daniel Bigos on 22.05.18.
//

#ifndef UNIX_TCP_ANALYSER_ABC_H
#define UNIX_TCP_ANALYSER_ABC_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{

    class ABC : public TCPOption
    {
    public:
        ABC();
        virtual ~ABC();

    };
}

#endif //UNIX_TCP_ANALYSER_ABC_H
