//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_INFOLOG_H
#define UNIX_TCP_ANALYSER_INFOLOG_H

#include <string>
#include "Log.h"

namespace tcp_analyser::utils::logger::log
{
    class InfoLog : public Log
    {
    public:
        InfoLog( std::string &message );
        virtual ~InfoLog() = default;

        void show() override;
    };
}

#endif //UNIX_TCP_ANALYSER_INFOLOG_H
