//
// Created by Daniel Bigos on 04.05.18.
//

#include <iostream>
#include "InfoLog.h"

using namespace tcp_analyser::utils::logger::log;

InfoLog::InfoLog( std::string &message )
        : Log(message) {}

void InfoLog::show()
{
    std::cout << message_ << std::endl;
}
