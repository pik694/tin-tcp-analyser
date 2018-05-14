//
// Created by Daniel Bigos on 14.05.18.
//

#include <utils/system_api/options/Timestamps.h>
#include "OptionsFactory.h"

using namespace tcp_analyser::utils::system_api;
using namespace tcp_analyser::utils::system_api::options;

OptionsFactory* OptionsFactory::instance_ = nullptr;

OptionsFactory& OptionsFactory::getInstance()
{
    if( !instance_ )
        instance_ = new OptionsFactory();

    return *instance_;
}

OptionsFactory::~OptionsFactory()
{
    if( instance_ )
        delete( instance_ );

    instance_ = nullptr;
}

std::unique_ptr< TCPOption > OptionsFactory::getOption( TCPOptions_E option )
{
    return factoryOptions_.at( option )();
}