//
// Created by Daniel Bigos on 03.05.18.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "Runnable.h"
using namespace tcp_analyser::runnable;


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

std::string Runnable::getSystemDate()
{
    std::ostringstream stream;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t( now );
    stream << std::put_time( std::localtime( &now_c ), "%F %T" );
    return stream.str();
}
