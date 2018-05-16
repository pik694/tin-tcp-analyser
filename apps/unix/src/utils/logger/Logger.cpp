//
// Created by Daniel Bigos on 03.05.2018.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <iomanip>
#include "Logger.hpp"
#include "log/LogFactory.h"

using namespace tcp_analyser::utils::logger;
using namespace tcp_analyser::utils::logger::log;

Logger* Logger::instance_ = nullptr;

std::mutex mutex_;
std::condition_variable conditionVariable_;

Logger::Logger()
        : shouldFinish_( false ) { }

Logger *Logger::getInstance()
{
    if( instance_ == nullptr )
        instance_ = new Logger();

    return instance_;
}

void Logger::log()
{
    while( !( shouldFinish_ && logsQueue_.empty() ) )
    {
        std::unique_lock<std::mutex> guard( mutex_ );
        conditionVariable_.wait( guard, [this]{ return !logsQueue_.empty(); } );

        logsQueue_.front()->show();
        logsQueue_.pop();
    }
}

void Logger::close()
{
    shouldFinish_ = true;
    add( "Exiting program...", LogLevel::info );
}

void Logger::add( const std::string &log, LogLevel level )
{
    {
        std::unique_lock< std::mutex > guard( mutex_ );
        logsQueue_.emplace( LogFactory::getInstance().getLog( getSystemDate() + " : " + log, level ) );
    }
    conditionVariable_.notify_all();
}

void Logger::add( std::exception &e )
{
    add( e.what(), LogLevel::error );
}

std::string Logger::getSystemDate()
{
    std::ostringstream stream;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t( now );
    stream << std::put_time( std::localtime( &now_c ), "%F %T" );
    return stream.str();
}

Logger::~Logger()
{
    if( instance_ )
        delete( instance_ );

    instance_ = nullptr;
}



