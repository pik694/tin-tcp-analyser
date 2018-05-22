//
// Created by Daniel Bigos on 21.05.18.
//

#include <sys/stat.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <utils/logger/Logger.hpp>
#include "TCPOption.h"

using namespace tcp_analyser::utils::system_api::options;
using namespace tcp_analyser::utils::logger;

void TCPOption::getOption()
{
    // Create fifo
    umask( 0 );
    if( ( mknod( FIFO.c_str(), S_IFIFO | 0666, 0 ) < 0 && ( errno != EEXIST ) ) )
        Logger::getInstance()->add( "Could not create a FIFO", log::LogLevel::error );

    std::thread thread ( [&]()
                         {
                             std::string command = option_ + " > " + FIFO;
                             if ( std::system( command.c_str() ) )
                                 throw std::runtime_error( "Cannot get value: " + command );
                         } );

    std::ifstream stream( FIFO );
    char sign;
    do
    {
        stream.get( sign );
    }
    while( sign != '=' );
    stream >> std::scientific >> value_;
    if( value_ < 0 )
        throw std::runtime_error( "Option without value" + option_ );
    Logger::getInstance()->add( option_ + " was set to " + std::to_string( value_ ) );
    thread.join();
    //Clean up
    std::remove( FIFO.c_str() );
}

void TCPOption::setOption()
{
    if( std::system( ( option_ + "=" + std::to_string( ENABLE ) ).c_str() ) )
        throw std::runtime_error( "Cannot initialize option: " + option_ );

    Logger::getInstance()->add( option_ + " now set to 1" );
}

void TCPOption::revertOption()
{
    if( std::system( ( option_ + "=" + std::to_string( ENABLE ) ).c_str() ) )
        throw std::runtime_error( "Cannot deinitialize option: " + option_ );

    Logger::getInstance()->add( option_ + " reverted to " + std::to_string( value_ ) );
}

TCPOption::TCPOption( std::string option )
    : option_( option ) { }
