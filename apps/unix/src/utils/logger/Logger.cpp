//
// Created by Daniel Bigos on 03.05.2018.
//

#include <iostream>
#include "Logger.hpp"
#include "log/LogFactory.h"

using namespace tcp_analyser::utils::logger;
using namespace tcp_analyser::utils::logger::log;

Logger* Logger::instance_ = nullptr;
bool Logger::work_ = false;
bool Logger::shouldFinish_ = false;

std::mutex mutex_;
std::condition_variable conditionVariable_;

Logger &Logger::getInstance()
{

    if( instance_ == nullptr )
        instance_ = new Logger();

    return *instance_;
}

void Logger::log()
{
    while( work_ )
    {
        std::unique_lock<std::mutex> guard( mutex_ );
        conditionVariable_.wait( guard, []{ return !logsQueue_.empty(); } );

        logsQueue_.front()->show();
        logsQueue_.pop();
        work_ = !( shouldFinish_ && logsQueue_.empty() );
    }
}

void Logger::close()
{
    shouldFinish_ = true;
}

void Logger::add( const std::string &log, LogLevel level )
{
    std::unique_lock< std::mutex > guard( mutex_ );
    logsQueue_.emplace( LogFactory::getInstance().getLog( log, level ) );
    conditionVariable_.notify_all();
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

