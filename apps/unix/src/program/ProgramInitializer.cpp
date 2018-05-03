//
// Created by Daniel Bigos on 03.05.18.
//

#include "ProgramInitializer.h"

using namespace program;
using namespace boost::program_options;

ProgramInitializer::ProgramInitializer( int argc, const char **argv )
        : infoOptions_("Info options"),
          runOptions_ ("Program arguments"),
          variablesMap_(),
          argc_(argc),
          argv_(argv)
{

    positionalOptions_.add( TCP_OPTIONS.c_str(), -1 );

    infoOptions_.add_options()
            ( command( HELP, "h" ).c_str(), "Show this help message" )
            ( command( VERSION, "v" ).c_str(), "Show program version" );
    runOptions_.add_options()
            ( command( MODE, "m" ).c_str(), value< ExecutionMode_E >( &executionMode_ )->required(), "Specifies program mode" );
}

std::string ProgramInitializer::command( std::string longCommand, std::string shortCommand ) const
{
    return ( longCommand + "," + shortCommand );
}

std::unique_ptr< program::Program > ProgramInitializer::getProgram()
{
    std::unique_ptr< Program > program = std::make_unique< Program >();
    try
    {
        parse();
    }
    catch ( boost::program_options::required_option &e )
    {
        if ( variablesMap_.count( HELP ) || variablesMap_.count( VERSION ) )
        {
            if ( variablesMap_.count( HELP ) )
            {
                program = std::make_unique< HelpProgram>( std::move( program ),
                                                          options_description().add( infoOptions_ ).add( runOptions_ ) );
            }
            if ( variablesMap_.count( VERSION ) )
            {
                program = std::make_unique< GetVersionProgram >( std::move( program ) );
            }

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

            case ExecutionMode_E::SERVER:
                break;
            case ExecutionMode_E::CLIENT:
                break;
            default:
                throw std::runtime_error("Undefined execution mode.");
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
    program::ExecutionMode_E lexical_cast< program::ExecutionMode_E >( const std::string &name )
    {

        using string_function_map_t = std::map<const std::string, program::ExecutionMode_E>;

        static const string_function_map_t map = {
                { std::to_string( static_cast< int >( program::ExecutionMode_E::SERVER ) ), program::ExecutionMode_E::SERVER },
                { std::to_string( static_cast< int >( program::ExecutionMode_E::CLIENT ) ), program::ExecutionMode_E::CLIENT }
        };

        if( map.find( name ) == map.end() )
            throw std::runtime_error( "Invalid execution mode" );

        return map.at(name);

    }
}