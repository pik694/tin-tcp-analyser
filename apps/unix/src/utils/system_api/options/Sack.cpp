//
// Created by Daniel Bigos on 14.05.18.
//

#include <string>
#include "Sack.h"

using namespace tcp_analyser::utils::system_api::options;

Sack::Sack()
{
    command_ = "sysctl net.ipv4.tcp_sack" ;
    std::system( ( command_ + "=" + std::to_string( ENABLE ) ).c_str() );
}

Sack::~Sack()
{
    std::system( ( command_ + "=" + std::to_string( DISABLE ) ).c_str() );
}
