//
// Created by Daniel Bigos on 22.05.18.
//

#include "FRTO.h"

using namespace tcp_analyser::utils::system_api::options;

FRTO::FRTO()
    : TCPOption( "sysctl net.ipv4.tcp_frto")
{
    getOption();
    setOption();
}

FRTO::~FRTO()
{
    revertOption();
}
