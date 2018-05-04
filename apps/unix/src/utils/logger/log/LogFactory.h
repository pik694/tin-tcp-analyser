//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_LOGFACTORY_H
#define UNIX_TCP_ANALYSER_LOGFACTORY_H

#include "ErrorLog.h"
#include "InfoLog.h"
#include "WarningLog.h"

namespace tcp_analyser::utils::logger::log
{

    class LogFactory
    {
    public:
        static LogFactory &getInstance();
        LogFactory( const LogFactory & ) = delete;
        LogFactory &operator=( const LogFactory & ) = delete;
        ~LogFactory();


        Log* getLog( std::string , LogLevel );

    private:
        LogFactory() = default;

        static LogFactory *instance_;
    };
}

#endif //UNIX_TCP_ANALYSER_LOGFACTORY_H
