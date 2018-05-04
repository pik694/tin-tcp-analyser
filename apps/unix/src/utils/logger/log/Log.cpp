//
// Created by Daniel Bigos on 04.05.18.
//

#include "Log.h"

using namespace tcp_analyser::utils::logger::log;

Log::Log( std::string &message )
    : message_( std::move( message ) ) { }

std::string Log::getMessage()
{
    return message_;
}
