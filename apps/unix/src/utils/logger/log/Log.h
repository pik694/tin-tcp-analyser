//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_LOG_H
#define UNIX_TCP_ANALYSER_LOG_H

#include <string>

namespace tcp_analyser::utils::logger::log
{
    enum class LogLevel
    {
        info,
        warning,
        error
    };

    class Log
    {
    public:
        Log( std::string &message );
        virtual ~Log() = default;

        virtual void show() = 0;

        std::string getMessage();

    protected:
        std::string message_;
    };
}

#endif //UNIX_TCP_ANALYSER_LOG_H
