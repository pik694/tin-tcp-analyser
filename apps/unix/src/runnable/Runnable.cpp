//
// Created by Daniel Bigos on 03.05.18.
//

#include <iostream>
#include <fstream>
#include <utils/logger/Logger.hpp>
#include "Runnable.h"

using namespace tcp_analyser::runnable;
using namespace tcp_analyser::utils::logger;

void HelpProgram::run() {
    std::cout << description_ << std::endl;
    std::ifstream manual( "../../resources/manual.txt" );
    if( manual.is_open() ) {
        std::cout << manual.rdbuf() << std::endl;
        manual.close();
    }

    RunnableDecorator::run();
}

void ErrorInfoProgram::run() {
    std::cerr << errorMessage_ << std::endl;
    RunnableDecorator::run();
}

void RunnableDecorator::run() {
    program_->run();
}

void Runnable::getQuitSignal()
{
    char signal;
    do
    {
        std::cin >> signal;
    }
    while( signal != LOWER_QUIT && signal != UPPER_QUIT );

    Logger::getInstance()->add( "Received quit signal" );
    finish_ = true;
}

void Runnable::joinThreads()
{
    for( size_t i = 0; i < threads_.size(); ++i  )
    {
        if( i == 1 )
            Logger::getInstance()->close();

        threads_[ i ].join();
    }
}

char Runnable::getRandomChar( size_t range, size_t offset )
{
    std::srand( std::time( nullptr ) );
    return ( char )( std::rand() % range + offset );
}

void Runnable::sendSign( char sign )
{
    stream_ << sign;
    sleep( SLEEP_TIME );
}
