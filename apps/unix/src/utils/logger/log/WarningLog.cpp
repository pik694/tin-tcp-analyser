//
// Created by Daniel Bigos on 04.05.18.
//

#include <iostream>
#include "WarningLog.h"


using namespace tcp_analyser::utils::logger::log;


WarningLog::WarningLog( std::string &message )
        : Log(message) { }

void WarningLog::show()
{
    std::cout << message_ << std::endl;
}
