//
// Created by Piotr Żelazko on 03.05.2018.
//

#include <iostream>
#include "Logger.hpp"


tcp_analyser::utils::Logger* tcp_analyser::utils::Logger::instance_ = nullptr;

tcp_analyser::utils::Logger &tcp_analyser::utils::Logger::getInstance() {

    if(instance_ == nullptr)
        instance_ = new Logger();

    return *instance_;

}

void tcp_analyser::utils::Logger::log(const std::string &log, tcp_analyser::utils::LogLevel level) {
    //TODO
    std::cerr << log << std::endl;
}
