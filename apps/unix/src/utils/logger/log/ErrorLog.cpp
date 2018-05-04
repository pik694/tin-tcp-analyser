//
// Created by daniel on 04.05.18.
//

#include <iostream>
#include "ErrorLog.h"

using namespace tcp_analyser::utils::logger::log;

void ErrorLog::show()
{
    std::cerr << message_ << std::endl;
}

ErrorLog::ErrorLog( std::string &message )
    : Log( message ) { }
