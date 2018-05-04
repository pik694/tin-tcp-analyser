//
// Created by Daniel Bigos on 03.05.18.
//

#include <runnable/client/Client.hpp>
#include <runnable/server/Server.hpp>
#include "runnable/program_initialization/ProgramInitializer.h"

using namespace tcp_analyser::runnable;
using namespace tcp_analyser::runnable::program_initialization;
using namespace tcp_analyser::runnable::client;
using namespace tcp_analyser::runnable::server;
using namespace boost::program_options;
using namespace tcp_analyser::utils::system_api;

ProgramInitializer::ProgramInitializer( int argc, const char **argv ) :
        infoOptions_( "Info options" ),
        runOptions_ ( "Program arguments" ),
        variablesMap_(),
        argc_( argc ),
        argv_( argv )
{
    positionalOptions_.add( TCP_OPTIONS.c_str(), -1 );

    infoOptions_.add_options()
            ( command( HELP, "h" ).c_str(), "Show this help message" );
    runOptions_.add_options()
            ( command( MODE, "m" ).c_str(), value< ExecutionMode_E >( &executionMode_ )->required(), "Specifies program mode" )
            ( command( PORT, "p" ).c_str(), value< uint16_t >( &port_ )->required(), "Specifies port number" )
            ( command( HOSTNAME, "a" ).c_str(), value< std::string >( &hostname_ )->default_value( "" ), "Specifies server hostname" )
            ( command( TCP_OPTIONS, "t" ).c_str(), value< std::vector< TCPOptions_E > >( &TCPOptions_ )->multitoken(), "Specifies epoch count" )
            ( command( INPUT, "i" ).c_str(), value< std::string >( &inputFile_ )->default_value( "" ), "Specifies input file" )
            ( command( OUTPUT, "o" ).c_str(), value< std::string >( &outputFile_ )->default_value( "" ), "Specifies output file" );
}

std::string ProgramInitializer::command( std::string longCommand, std::string shortCommand ) const
{
    return ( longCommand + "," + shortCommand );
}

std::unique_ptr< Runnable > ProgramInitializer::getProgram()
{
    std::unique_ptr< Runnable > program = std::make_unique< Runnable >();
    try
    {
        parse();
    }
    catch( boost::program_options::required_option &e )
    {
        if( variablesMap_.count( HELP ) )
        {       program = std::make_unique< HelpProgram >( std::move( program ),
                                                          options_description().add( infoOptions_ ).add( runOptions_ ) );

            return program;
        }
        else
            return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
    }
    catch ( std::exception& e )
    {
        return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
    }


    try
    {
        switch ( executionMode_ )
        {
            case ExecutionMode_E::CLIENT:
                if( hostname_.length() == 0 )
                    throw std::invalid_argument( "No hostname specified" );

                return std::make_unique< Client >( hostname_, port_ );

            case ExecutionMode_E::SERVER:
                return std::make_unique< Server >( port_ );
        }
    }
    catch ( std::exception& e )
    {
        return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
    }

}

void ProgramInitializer::parse()
{

    options_description all;
    all.add( infoOptions_ );
    all.add( runOptions_ );

    store( parse_command_line( argc_, argv_, all ), variablesMap_ );

    notify( variablesMap_ );
}


namespace boost
{
    template<>
    tcp_analyser::runnable::ExecutionMode_E lexical_cast< tcp_analyser::runnable::ExecutionMode_E >( const std::string &name )
    {

        using string_function_map_t = std::map< const std::string, tcp_analyser::runnable::ExecutionMode_E >;

        static const string_function_map_t map = {
                { std::to_string(
                        static_cast< int >( tcp_analyser::runnable::ExecutionMode_E::SERVER ) ),
                        tcp_analyser::runnable::ExecutionMode_E::SERVER },
                { std::to_string(
                        static_cast< int >( tcp_analyser::runnable::ExecutionMode_E::CLIENT ) ),
                        tcp_analyser::runnable::ExecutionMode_E::CLIENT }
        };

        if( map.find( name ) == map.end() )
            throw std::invalid_argument( "Invalid execution mode" );

        return map.at(name);

    }

    template<>
    tcp_analyser::utils::system_api::TCPOptions_E lexical_cast< tcp_analyser::utils::system_api::TCPOptions_E >( const std::string &name )
    {

        using string_function_map_t = std::map< const std::string, tcp_analyser::utils::system_api::TCPOptions_E >;

        static const string_function_map_t map = {
                { std::to_string(
                        static_cast< int >( tcp_analyser::utils::system_api::TCPOptions_E::SACK ) ),
                        tcp_analyser::utils::system_api::TCPOptions_E::SACK }
        };

        if( map.find( name ) == map.end() )
            throw std::invalid_argument( "Invalid TCP option" );

        return map.at( name );

    }
}