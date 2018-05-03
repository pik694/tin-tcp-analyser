//
// Created by Daniel Bigos on 03.05.18.
//

#ifndef UNIX_TCP_ANALYSER_PROGRAM_H
#define UNIX_TCP_ANALYSER_PROGRAM_H

#include <boost/program_options.hpp>

namespace program
{

    enum class ExecutionMode_E
    {
        SERVER = 1,
        CLIENT = 2
    };

    class Program
    {
    public:
        virtual ~Program() = default;

        virtual void run() = 0;

    };

    class ProgramDecorator : public Program
    {
    public:
        explicit ProgramDecorator( std::unique_ptr< Program > program ):
                program_( std::move( program ) ){}

        void run() override;

        virtual ~ProgramDecorator() = default;
    private:
        std::unique_ptr< Program > program_;
    };

    class GetVersionProgram : public ProgramDecorator
    {
    public:
        explicit GetVersionProgram( std::unique_ptr< Program > program ): ProgramDecorator( std::move( program ) ) {}

        void run() override;
        virtual ~GetVersionProgram() = default;
    };

    class HelpProgram : public ProgramDecorator
    {
    public:
        HelpProgram( std::unique_ptr<Program> program,
                     boost::program_options::options_description description ) :
                ProgramDecorator( std::move( program ) ),
                description_( std::move( description ) ) {}

        void run() override;

        virtual ~HelpProgram() = default;

    private:
        boost::program_options::options_description description_;
    };

    class ErrorInfoProgram : public ProgramDecorator
    {
    public:
        ErrorInfoProgram( const std::string& errorMessage, std::unique_ptr< Program > program ) :
                ProgramDecorator( std::move( program ) ),
                errorMessage_( errorMessage )
        {}

        void run() override;

        virtual ~ErrorInfoProgram() = default;

    private:
        const std::string errorMessage_;
    };

}
#endif //UNIX_TCP_ANALYSER_PROGRAM_H
