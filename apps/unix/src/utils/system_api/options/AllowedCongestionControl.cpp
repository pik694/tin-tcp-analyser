//
// Created by Daniel Bigos on 22.05.18.
//

#include "AllowedCongestionControl.h"

using namespace tcp_analyser::utils::system_api::options;

AllowedCongestionControl::AllowedCongestionControl()
    : TCPOption( "sysctl net.ipv4.tcp_allowed_congestion_control" )
{
    getOption();
    setOption();
}

AllowedCongestionControl::~AllowedCongestionControl()
{
    revertOption();
}
