//
// Created by Daniel Bigos on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_LOGGER_HPP
#define UNIX_TCP_ANALYSER_LOGGER_HPP

#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <utils/logger/log/Log.h>
#include <queue>

typedef std::queue< std::unique_ptr< tcp_analyser::utils::logger::log::Log > > LogsQueue;

namespace tcp_analyser::utils::logger
{

    class Logger
    {
    public:

        static Logger &getInstance();
        ~Logger();

        Logger( const Logger & ) = delete;
        Logger &operator=( const Logger & ) = delete;


        void log();

        void add( const std::string & log,
                  tcp_analyser::utils::logger::log::LogLevel level = tcp_analyser::utils::logger::log::LogLevel::info );
        void add( std::exception &e );

        void close();

    private:
        Logger();

        static Logger* instance_;

        LogsQueue logsQueue_;

        bool shouldFinish_;
    };
}


#endif //UNIX_TCP_ANALYSER_LOGGER_HPP
