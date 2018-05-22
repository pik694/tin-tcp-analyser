//
// Created by Daniel Bigos on 22.05.18.
//

#ifndef UNIX_TCP_ANALYSER_ALLOWEDCONGESTIONPROTOCOL_H
#define UNIX_TCP_ANALYSER_ALLOWEDCONGESTIONPROTOCOL_H

#include "TCPOption.h"

namespace tcp_analyser::utils::system_api::options
{
    class AllowedCongestionControl : public TCPOption
    {
    public:
        AllowedCongestionControl();
        virtual ~AllowedCongestionControl();
    };
}

#endif //UNIX_TCP_ANALYSER_ALLOWEDCONGESTIONPROTOCOL_H
