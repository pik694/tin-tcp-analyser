//
// Created by Piotr Żelazko on 04.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <runnable/client/Client.h>

using tcp_analyser::runnable::client::Client;

BOOST_AUTO_TEST_SUITE(client_test)

    BOOST_AUTO_TEST_CASE(cannot_connect) {

        std::string hostname = "localhost";

        Client client(hostname, 6969);

        BOOST_REQUIRE_THROW(client.run(), std::runtime_error);

    }

BOOST_AUTO_TEST_SUITE_END()


#endif

