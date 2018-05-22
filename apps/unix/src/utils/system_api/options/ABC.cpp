//
// Created by Daniel Bigos on 22.05.18.
//

#include "ABC.h"

using namespace tcp_analyser::utils::system_api::options;

ABC::ABC()
    : TCPOption( "sysctl net.ipv4.tcp_abc" )
{
    getOption();
    setOption();
}

ABC::~ABC()
{
    revertOption();
}
