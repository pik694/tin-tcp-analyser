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

Server::Server( uint16_t port )
    : port_( port ) { }

void Server::run()
{
    std::thread thread( &Logger::log, Logger::getInstance() );
    try
    {
        std::string msg;
        io_context io_context;

        Logger::getInstance()->add( getSystemDate() + " : Server is listening on port: " + std::to_string( port_ ), log::LogLevel::info );

        tcp::endpoint endpoint( tcp::v4(), port_ );
        tcp::acceptor acceptor( io_context, endpoint);

        tcp::iostream stream;
        boost::system::error_code ec;
        acceptor.accept( stream.socket(), ec );
        if( !ec )
        {
            auto start = std::chrono::system_clock::now();
            Logger::getInstance()->add( getSystemDate() + " : Server accepted connection" );
            while( std::chrono::system_clock::now() - start < std::chrono::minutes( DURATION_IN_MIN ) )
            {
                stream << "Ping";
            }
        }

    }
    catch ( std::exception& e )
    {
        Logger::getInstance()->add( e );
    }

    Logger::getInstance()->add( getSystemDate() + " : Connection closed!" );
    Logger::getInstance()->close();

    thread.join();

}
