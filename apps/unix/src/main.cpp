#include <iostream>
#include <runnable/program_initialization/ProgramInitializer.h>

int main(int argc, const char **argv) {

    tcp_analyser::runnable::program_initialization::ProgramInitializer programInitializer (argc, argv);
    auto program = programInitializer.getProgram();

    program->run();

    return 0;
}