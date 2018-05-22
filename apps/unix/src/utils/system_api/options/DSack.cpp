//
// Created by Daniel Bigos on 22.05.18.
//

#include "DSack.h"

using namespace tcp_analyser::utils::system_api::options;

DSack::DSack()
    : TCPOption( "sysctl net.ipv4.tcp_dsack" )
{
    getOption();
    setOption();
}

DSack::~DSack()
{
    revertOption();
}
