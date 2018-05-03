//
// Created by Daniel Bigos on 03.05.18.
//

#ifndef UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H
#define UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H

#include <string>
#include "Program.h"

namespace program
{
    class ProgramInitializer
    {
        using c_str = const std::string;

    public:

        ProgramInitializer( int argc, const char **argv );

        std::unique_ptr< Program > getProgram();

        virtual ~ProgramInitializer() = default;

    private:

        void parse();

        std::string command(std::string longCommand, std::string shortCommand) const;

        boost::program_options::options_description infoOptions_;
        boost::program_options::options_description runOptions_;
        boost::program_options::variables_map variablesMap_;
        boost::program_options::positional_options_description positionalOptions_;

        int argc_;
        const char **argv_;

        std::vector< int > tcpOptions_;
        ExecutionMode_E executionMode_;


        c_str HELP = "help";
        c_str VERSION = "version";
        c_str MODE = "mode";
        c_str TCP_OPTIONS = "tcp options";

    };
}

namespace boost
{
    template<>
    program::ExecutionMode_E lexical_cast< program::ExecutionMode_E >( const std::string &name );
}

#endif //UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H
