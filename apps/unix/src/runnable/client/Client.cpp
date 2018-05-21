//
// Created by Daniel Bigos on 15.05.18.
//

#include <chrono>
#include <utils/logger/Logger.hpp>
#include "Client.h"
#include <thread>

using namespace tcp_analyser::runnable::client;
using namespace tcp_analyser::utils::logger;
using namespace boost::asio::ip;

void Client::run()
{
    threads_.emplace_back( &Client::getQuitSignal, this );
    threads_.emplace_back( &Logger::log, Logger::getInstance() );
    try
    {
        stream_.connect( hostname_, std::to_string( port_ ) );
        if ( !stream_ )
            throw std::runtime_error( "Cannot connect to the server:" + hostname_ + " at port:" + std::to_string( port_ ) );

        Logger::getInstance()->add( "Client connected to the server at " + hostname_ + " at port: " + std::to_string( port_ ) );

        threads_.emplace_back( &Client::send, this );
        threads_.emplace_back( &Client::receive, this );
    }
    catch ( std::exception& e )
    {
        Logger::getInstance()->add( e );
    }

    joinThreads();
}

Client::Client( std::string host, uint16_t port )
    : hostname_( host ),
      port_( port ) { }

void Client::send()
{
    char message;
    do
    {
        message = getRandomChar( LETTERS_RANGE, LOWERCASE_LETTER );
        sendSign( message );
    }
    while( !finish_ && message != LOWER_QUIT );
    sendSign( LOWER_QUIT );
    finish_ = true;
}

void Client::receive()
{
    char message;
    do
    {
        stream_.get( message );
        Logger::getInstance()->add( "Server message: " + std::string( 1, message ) );
    }
    while( !stream_.eof() && !finish_ && message != UPPER_QUIT );

    if( message == UPPER_QUIT )
        Logger::getInstance()->add( "Server finished connection" );

    finish_ = true;
}
