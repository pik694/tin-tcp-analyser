//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_WARNINGLOG_H
#define UNIX_TCP_ANALYSER_WARNINGLOG_H

#include "Log.h"

namespace tcp_analyser::utils::logger::log
{
    class WarningLog : public Log
    {
    public:
        WarningLog ( std::string &message );
        virtual ~WarningLog() = default;

        void show() override;

    };
}

#endif //UNIX_TCP_ANALYSER_WARNINGLOG_H
