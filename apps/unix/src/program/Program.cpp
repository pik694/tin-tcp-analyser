//
// Created by Daniel Bigos on 03.05.18.
//

#include <iostream>
#include <fstream>
#include "Program.h"
using namespace program;

void GetVersionProgram::run()
{
//    std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
    ProgramDecorator::run();
}

void HelpProgram::run()
{
    std::cout << description_ << std::endl;
    std::ifstream manual( "manual.txt" );
    if( manual.is_open() )
    {
        std::cout << manual.rdbuf() << std::endl;
        manual.close();
    }

    ProgramDecorator::run();
}

void ErrorInfoProgram::run()
{
    std::cerr << errorMessage_ << std::endl;
    ProgramDecorator::run();
}