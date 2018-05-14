//
// Created by Daniel Bigos on 14.05.18.
//

#ifndef UNIX_TCP_ANALYSER_OPTIONSFACTORY_H
#define UNIX_TCP_ANALYSER_OPTIONSFACTORY_H

#include "options/TCPOptions.h"

namespace tcp_analyser::system_api
{
    class OptionsFactory
    {
    public:
        static OptionsFactory &getInstance();
        OptionsFactory( const OptionsFactory& ) = delete;
        OptionsFactory &operator=( const OptionsFactory& ) = delete;

        std::shared_ptr< tcp_analyser::system_api::options::Option > getOption( tcp_analyser::system_api::options::TCPOptions_E );

    private:
        OptionsFactory();

        static OptionsFactory* instance_;
    };
}

#endif //UNIX_TCP_ANALYSER_OPTIONSFACTORY_H
