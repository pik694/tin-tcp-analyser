//
// Created by Piotr Żelazko on 03.05.2018.
//

#ifndef UNIX_TCP_ANALYSER_LOGGER_HPP
#define UNIX_TCP_ANALYSER_LOGGER_HPP

#include <string>

namespace tcp_analyser::utils {

    enum class LogLevel{
        info,
        warning,
        error
    };

    class Logger {
    public:

        static Logger &getInstance();

        void log(const std::string & log, LogLevel level = LogLevel::info);

    private:

        static Logger* instance_;
    };
}


#endif //UNIX_TCP_ANALYSER_LOGGER_HPP
