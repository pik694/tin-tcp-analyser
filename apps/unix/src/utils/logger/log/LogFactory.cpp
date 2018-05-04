//
// Created by Daniel Bigos on 04.05.18.
//

#include <stdexcept>
#include "LogFactory.h"

using namespace tcp_analyser::utils::logger::log;

LogFactory* LogFactory::instance_ = nullptr;

LogFactory &LogFactory::getInstance()
{
    if( !instance_ )
        instance_ = new LogFactory();

    return *instance_;
}

LogFactory::~LogFactory()
{
    if( instance_ )
        delete( instance_ );

    instance_ = nullptr;
}

Log *LogFactory::getLog( std::string message, LogLevel log_level )
{
    Log *log = nullptr;
    switch( log_level )
    {
        case LogLevel::info:
            log = new InfoLog( message );
            break;
        case LogLevel::warning:
            log = new WarningLog( message );
            break;
        case LogLevel::error:
            log = new ErrorLog( message );
            break;
    }
    return log;
}
