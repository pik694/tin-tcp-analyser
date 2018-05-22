//
// Created by Daniel Bigos on 16.05.18.
//

#include <utils/logger/Logger.hpp>
#include "Server.h"
#include <boost/asio.hpp>
#include <iostream>
#include <iomanip>


using namespace tcp_analyser::runnable::server;
using namespace tcp_analyser::utils::logger;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace tcp_analyser::utils::system_api::options;

Server::Server( uint16_t port, std::vector< TCPOptions_E > options )
    : port_( port )
{
    initOptions( options );
}

void Server::run()
{
    threads_.emplace_back( &Server::getQuitSignal, this );
    threads_.emplace_back( &Logger::log, Logger::getInstance() );
    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint( tcp::v4(), port_ );
        tcp::acceptor acceptor( io_context, endpoint );
        Logger::getInstance()->add( "Server is listening on port: " + std::to_string( port_ ), log::LogLevel::info );
        boost::system::error_code ec;
        acceptor.accept( stream_.socket(), ec );
        if( ec )
            throw std::runtime_error( "Cannot establish connection, error code: " + std::to_string( ec.value() ) );

        Logger::getInstance()->add( "Server accepted connection" );
        threads_.emplace_back( &Server::send, this );
        threads_.emplace_back( &Server::receive, this );
    }
    catch ( std::exception& e )
    {
        Logger::getInstance()->add( e );
    }

    joinThreads();
}

void Server::send()
{
    char message;
    do
    {
        message = getRandomChar( LETTERS_RANGE, UPPERCASE_LETTER );
        sendSign( message );
    }
    while( !finish_ && message != UPPER_QUIT );
    sendSign( UPPER_QUIT );
    finish_ = true;
}

void Server::receive()
{
    char message;
    do
    {
        stream_.get( message );
        Logger::getInstance()->add( "Client message: " + std::string( 1, message ) );
    }
    while( !stream_.eof() && !finish_ && message != LOWER_QUIT );

    if( message == LOWER_QUIT )
        Logger::getInstance()->add( "Client finished connection" );

    finish_ = true;
}
