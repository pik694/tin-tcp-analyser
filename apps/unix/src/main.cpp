#include <iostream>
#include <runnable/client/Client.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;

    tcp_analyser::runnable::client::Client client ("localhost", 6969);

    return 0;
}