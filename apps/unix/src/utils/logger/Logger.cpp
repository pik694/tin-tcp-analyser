//
// Created by Daniel Bigos on 03.05.2018.
//

#include <iostream>
#include "Logger.hpp"
#include "log/LogFactory.h"

using namespace tcp_analyser::utils::logger;
using namespace tcp_analyser::utils::logger::log;

Logger* Logger::instance_ = nullptr;

Logger &Logger::getInstance()
{

    if( instance_ == nullptr )
        instance_ = new Logger();

    return *instance_;
}

void Logger::log()
{

}

void Logger::add( const std::string &log, LogLevel level )
{

}

void Logger::add( std::exception &e )
{
    add( e.what(), LogLevel::error );
}

Logger::~Logger()
{
    if( instance_ )
        delete( instance_ );

    instance_ = nullptr;
}

void log( const std::string &log, LogLevel level )
{
    //TODO
}
