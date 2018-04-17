//
// Created by Piotr Żelazko on 17.04.2018.
//

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_DYN_LINK


BOOST_AUTO_TEST_SUITE(sample_test_suite)

    BOOST_AUTO_TEST_CASE(sample_test_case) {
        BOOST_CHECK_EQUAL(1,1);
    }

BOOST_AUTO_TEST_SUITE_END()


