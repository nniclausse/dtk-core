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

#include "dtkCoreSettingsTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreParameter>
#include <dtkCore/dtkCoreSettings>

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(dtkCoreParameter<std::string>)

// ///////////////////////////////////////////////////////////////////
// dtkCoreSettingsTestCase implementation
// ///////////////////////////////////////////////////////////////////

void dtkCoreSettingsTestCase::initTestCase(void)
{
    qRegisterMetaType<std::string>();

    qRegisterMetaTypeStreamOperators<dtk::d_bool>("dtk::d_bool");

    qRegisterMetaTypeStreamOperators<dtk::d_real>("dtk::d_real");
    qRegisterMetaTypeStreamOperators<dtk::d_int>("dtk::d_int");
    qRegisterMetaTypeStreamOperators<dtk::d_string>("dtk::d_string");

    QMetaType::registerDebugStreamOperator<dtk::d_real>();
    QMetaType::registerDebugStreamOperator<dtk::d_int>();
    QMetaType::registerDebugStreamOperator<dtk::d_bool>();
    QMetaType::registerDebugStreamOperator<dtk::d_string>();
}

void dtkCoreSettingsTestCase::init(void)
{

}

void dtkCoreSettingsTestCase::testTrack(void)
{
    QTemporaryFile file;

    QVERIFY(file.open());

    {
        dtkCoreSettings settings(file.fileName());

        dtk::d_real p("p", 5., -10., 10.);

        settings.track(&p);

        dtk::d_real p_s = settings.value("p");

        QVERIFY(p_s == p);
        QVERIFY(p_s.label() == p.label());

        p.setValue(4.);

        dtk::d_real p_s_s = settings.value("p");

        QVERIFY(p_s_s == 4.);

        p.setValue(6.);

    } // This scope makes sure the settings are destroyed (avoid using sync as Qt documents it).

    {
        dtkCoreSettings settings(file.fileName());

        dtk::d_real p = settings.restore("p");

        QVERIFY(p == 6.);
        QVERIFY(p.label() == "p");

        p.setValue(7.);

        dtk::d_real p_s = settings.value("p");

        QVERIFY(p_s == 6.); // p is not yet tracked

        settings.track(&p);

        p.setValue(8.);

        dtk::d_real p_s_s = settings.value("p");

        QVERIFY(p_s_s == 8.); // p is tracked
    }

    file.close();
}

void dtkCoreSettingsTestCase::cleanup(void)
{

}

void dtkCoreSettingsTestCase::cleanupTestCase(void)
{

}



DTKCORETEST_MAIN_NOGUI(dtkCoreSettingsTest, dtkCoreSettingsTestCase);

//
// dtkCoreSettingsTest.cpp ends here
