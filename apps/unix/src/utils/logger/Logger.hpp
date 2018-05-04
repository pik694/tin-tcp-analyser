//
// Created by Daniel Bigos on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_LOGGER_HPP
#define UNIX_TCP_ANALYSER_LOGGER_HPP

#include <string>
#include <utils/logger/log/Log.h>

namespace tcp_analyser::utils::logger
{

    class Logger
    {
    public:

        static Logger &getInstance();
        ~Logger();

        Logger( const Logger & ) = delete;
        Logger &operator=( const Logger & ) = delete;


        static void log();

        void add( const std::string & log,
                  tcp_analyser::utils::logger::log::LogLevel level = tcp_analyser::utils::logger::log::LogLevel::info );
        void add( std::exception &e );

    private:
        Logger() = default;

        static Logger* instance_;
    };
}


#endif //UNIX_TCP_ANALYSER_LOGGER_HPP
