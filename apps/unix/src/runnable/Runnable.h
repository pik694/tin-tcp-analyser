//
// Created by Daniel Bigos on 03.05.18.
//

#ifndef UNIX_TCP_ANALYSER_PROGRAM_H
#define UNIX_TCP_ANALYSER_PROGRAM_H

#include <boost/program_options.hpp>

namespace tcp_analyser::runnable {
    class Runnable {
    public:
        Runnable() = default;

        virtual ~Runnable() = default;

        virtual void run() = 0;

    };

    class RunnableDecorator : public Runnable {
    public:
        explicit RunnableDecorator(std::unique_ptr<Runnable> program) :
                program_(std::move(program)) {}

        void run() override;

        virtual ~RunnableDecorator() = default;

    private:
        std::unique_ptr<Runnable> program_;
    };

    class GetVersionProgram : public RunnableDecorator {
    public:
        explicit GetVersionProgram(std::unique_ptr<Runnable> program) : RunnableDecorator(std::move(program)) {}

        void run() override;

        virtual ~GetVersionProgram() = default;
    };

    class HelpProgram : public RunnableDecorator {
    public:
        HelpProgram(std::unique_ptr<Runnable> program,
                    boost::program_options::options_description description) :
                RunnableDecorator(std::move(program)),
                description_(std::move(description)) {}

        void run() override;

        virtual ~HelpProgram() = default;

    private:
        boost::program_options::options_description description_;
    };

    class ErrorInfoProgram : public RunnableDecorator {
    public:
        ErrorInfoProgram(const std::string &errorMessage, std::unique_ptr<Runnable> program) :
                RunnableDecorator(std::move(program)),
                errorMessage_(errorMessage) {}

        void run() override;

        virtual ~ErrorInfoProgram() = default;

    private:
        const std::string errorMessage_;
    };

}
#endif //UNIX_TCP_ANALYSER_PROGRAM_H