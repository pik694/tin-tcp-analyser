//
// Created by Daniel Bigos on 03.05.18.
//

#ifndef UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H
#define UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H

#include <string>
#include <runnable/Runnable.h>

namespace tcp_analyser::runnable::program_initialization
{
    class ProgramInitializer {
        using c_str = const std::string;

    public:

        ProgramInitializer(int argc, const char **argv);

        std::unique_ptr<Runnable> getProgram();

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

        ExecutionMode_E executionMode_;
        uint16_t port_;
        std::string hostname_;
        std::string inputFile_;
        std::string outputFile_;


        c_str HELP = "help";
        c_str VERSION = "version";
        c_str MODE = "mode";
        c_str PORT = "port";
        c_str HOSTNAME = "hostname";
        c_str INPUT = "input filename";
        c_str OUTPUT = "output filename";
    };
}

namespace boost{
    template<>
    tcp_analyser::runnable::ExecutionMode_E lexical_cast<tcp_analyser::runnable::ExecutionMode_E>(const std::string &name);
}


#endif //UNIX_TCP_ANALYSER_PROGRAMINITIALIZER_H
