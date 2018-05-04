//
// Created by Daniel Bigos on 04.05.18.
//

#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>

#include "../../src/utils/logger/log/LogFactory.h"

BOOST_AUTO_TEST_SUITE( LogFactoryTests )

    using namespace tcp_analyser::utils::logger::log;

    BOOST_AUTO_TEST_CASE( GivenInfoTypeShoulReturnInfoLog )
    {
        std::string msg( "Info" );
        Log *log = LogFactory::getInstance().getLog( msg, LogLevel::info );
        BOOST_REQUIRE( log );
        InfoLog *infoLog;
        BOOST_REQUIRE( infoLog = dynamic_cast< InfoLog* >( log ) );
        BOOST_CHECK_EQUAL( infoLog->getMessage(), msg );
        delete( log );
    }

    BOOST_AUTO_TEST_CASE( GivenWarningTypeShoulReturnWarningLog )
    {
        std::string msg( "Warning" );
        Log *log = LogFactory::getInstance().getLog( msg, LogLevel::warning );
        BOOST_REQUIRE( log );
        WarningLog *warningLog;
        BOOST_REQUIRE( warningLog = dynamic_cast< WarningLog* >( log ) );
        BOOST_CHECK_EQUAL( warningLog->getMessage(), msg );
        delete( log );
    }

    BOOST_AUTO_TEST_CASE( GivenErrorTypeShoulReturnErrorLog )
    {
        std::string msg( "Error" );
        Log *log = LogFactory::getInstance().getLog( msg, LogLevel::error );
        BOOST_REQUIRE( log );
        ErrorLog *errorLog;
        BOOST_REQUIRE( errorLog = dynamic_cast< ErrorLog* >( log ) );
        BOOST_CHECK_EQUAL( errorLog->getMessage(), msg );
        delete( log );
    }

BOOST_AUTO_TEST_SUITE_END()
