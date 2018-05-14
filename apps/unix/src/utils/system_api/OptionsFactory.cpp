//
// Created by Daniel Bigos on 14.05.18.
//

#include "OptionsFactory.h"

using namespace tcp_analyser::system_api;
using namespace tcp_analyser::system_api::options;

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

shared_ptr< Option > OptionsFactory::getOption( TCPOPtions_E tcpoPtions_e )
{
    return nullptr;
}