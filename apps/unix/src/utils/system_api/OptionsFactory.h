//
// Created by Daniel Bigos on 14.05.18.
//

#ifndef UNIX_TCP_ANALYSER_OPTIONSFACTORY_H
#define UNIX_TCP_ANALYSER_OPTIONSFACTORY_H

#include <memory>
#include <unordered_map>
#include <functional>
#include <utils/system_api/options/TCPOption.h>
#include <utils/system_api/options/Timestamps.h>
#include <utils/system_api/options/Sack.h>
#include <utils/system_api/options/DSack.h>
#include <utils/system_api/options/AllowedCongestionControl.h>
#include <utils/system_api/options/ABC.h>
#include <utils/system_api/options/FRTO.h>


using TCPOptionsEnum = tcp_analyser::utils::system_api::options::TCPOptions_E;
namespace tcp_analyser::utils::system_api
{
    class OptionsFactory
    {
    public:
        static OptionsFactory &getInstance();
        OptionsFactory( const OptionsFactory& ) = delete;
        OptionsFactory &operator=( const OptionsFactory& ) = delete;
        virtual ~OptionsFactory();

        std::unique_ptr< options::TCPOption > getOption( TCPOptionsEnum );

    private:
        OptionsFactory() = default;

        const std::unordered_map< TCPOptionsEnum, std::function< std::unique_ptr< options::TCPOption >() > > factoryOptions_ {
            { TCPOptionsEnum::TIMESTAMPS, [](){ return std::make_unique< options::Timestamps >(); } },
            { TCPOptionsEnum::SACK, [](){ return std::make_unique< options::Sack >(); } },
            { TCPOptionsEnum::DSACK, [](){ return std::make_unique< options::DSack >(); } },
            { TCPOptionsEnum::ALLOWED_CONGESTION_CONTROL, [](){ return std::make_unique< options::AllowedCongestionControl >(); } },
            { TCPOptionsEnum::ABC, [](){ return std::make_unique< options::ABC >(); } },
            { TCPOptionsEnum::FRTO, [](){ return std::make_unique< options::FRTO >(); } }
        };

        static OptionsFactory* instance_;
    };
}

#endif //UNIX_TCP_ANALYSER_OPTIONSFACTORY_H
