//
// Created by Daniel Bigos on 14.05.18.
//

#include <string>
#include <sys/stat.h>
#include <thread>
#include <fstream>
#include "Sack.h"
#include <utils/logger/Logger.hpp>
#include <iostream>
#include <sstream>

using namespace tcp_analyser::utils::system_api::options;

Sack::Sack()
    : TCPOption( "sysctl net.ipv4.tcp_sack" )
{
    getOption();
    setOption();
}

Sack::~Sack()
{
    revertOption();
}
