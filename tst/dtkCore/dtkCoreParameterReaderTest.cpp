// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkCoreParameterReaderTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreParameter>
#include <dtkCore/dtkCoreParameterPath>
#include <dtkCore/dtkCoreParameterReader>

dtkCoreParameterReaderTestCase::dtkCoreParameterReaderTestCase(void)
{
    dtk::core::registerParameters();
}

dtkCoreParameterReaderTestCase::~dtkCoreParameterReaderTestCase(void)
{
}

void dtkCoreParameterReaderTestCase::initTestCase(void)
{

}

void dtkCoreParameterReaderTestCase::init(void)
{
}

void dtkCoreParameterReaderTestCase::testRead(void)
{
    QString json_file(QFINDTESTDATA("../resources/parameters_def.json"));
    QString json_bad_file(QFINDTESTDATA("../resources/parameters_baddef.json"));

    dtkCoreParameterReader the_reader(json_file);
    dtkCoreParameterReader the_badreader(json_bad_file);

    auto resbad = the_badreader.parameters();
    QCOMPARE(resbad.count() , 0);

    auto res = the_reader.parameters();
    QCOMPARE(res.count() , 6);

    QCOMPARE(res["hyp"]->label() , QString("Porosity Model"));
    QCOMPARE(dtk::d_int(res["hyp"]->variant()).value(), 2);

    QCOMPARE(res["dif"]->documentation() , QString("diffusion Flag"));
    QCOMPARE(dtk::d_bool(res["dif"]->variant()).value() , false);
    QCOMPARE(dtk::d_real(res["toto"]->variant()).value() , 3.1415);
}


void dtkCoreParameterReaderTestCase::cleanupTestCase(void)
{

}

void dtkCoreParameterReaderTestCase::cleanup(void)
{

}

DTKCORETEST_MAIN_NOGUI(dtkCoreParameterReaderTest, dtkCoreParameterReaderTestCase);

//
// dtkCoreParameterReaderTest.cpp ends here
