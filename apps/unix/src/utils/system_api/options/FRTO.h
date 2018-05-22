//
// Created by Daniel Bigos on 22.05.18.
//

#ifndef UNIX_TCP_ANALYSER_FRTO_H
#define UNIX_TCP_ANALYSER_FRTO_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{
    class FRTO : public TCPOption
    {
    public:
        FRTO();
        virtual ~FRTO();
    };
}

#endif //UNIX_TCP_ANALYSER_FRTO_H
