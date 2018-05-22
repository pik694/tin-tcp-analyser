//
// Created by Daniel Bigos on 14.05.18.
//

#include "Timestamps.h"

using namespace tcp_analyser::utils::system_api::options;

Timestamps::Timestamps()
    : TCPOption( "sysctl net.ipv4.tcp_timestamps" )
{
    getOption();
    setOption();
}

Timestamps::~Timestamps()
{
    revertOption();
}
