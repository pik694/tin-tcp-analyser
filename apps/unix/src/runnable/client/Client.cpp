//
// Created by Daniel Bigos on 15.05.18.
//

#include <chrono>
#include <utils/logger/Logger.hpp>
#include "Client.h"
#include <thread>

using namespace tcp_analyser::runnable::client;
using namespace tcp_analyser::utils::logger;

void Client::run()
{
    std::thread thread( &Logger::log, Logger::getInstance() );
    stream_.connect( hostname_, std::to_string( port_ ) );
    if( !stream_ )
        throw std::runtime_error( "Cannot connect to the server:" + hostname_ + " at port:" + std::to_string( port_ ) );
    else
    {
        Logger::getInstance()->add( "Client connected to the server at " + hostname_ + " at port: " + std::to_string( port_ ) );
    }

    std::string message;
    while( std::getline( stream_, message ) );

    Logger::getInstance()->add( "Connection closed" );

    Logger::getInstance()->close();
    thread.join();
}

Client::Client( std::string host, uint16_t port )
    : hostname_( host ),
      port_( port ) { }
