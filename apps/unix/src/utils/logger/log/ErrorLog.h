//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_ERRORLOG_H
#define UNIX_TCP_ANALYSER_ERRORLOG_H

#include <string>
#include "Log.h"

namespace tcp_analyser::utils::logger::log
{
    class ErrorLog : public Log
    {
    public:
        ErrorLog( std::string &message );
        virtual ~ErrorLog() = default;

        void show() override;
    };
}

#endif //UNIX_TCP_ANALYSER_ERRORLOG_H
