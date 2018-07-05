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

#include "dtkMetaTypeTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkMetaType>

class Derived : public QObject
{
};

class NoDerived
{
};

class DerivedTwice : public Derived
{
};

// ///////////////////////////////////////////////////////////////////

class dtkMetaTypeTestCasePrivate
{
public:
};

// ///////////////////////////////////////////////////////////////////

dtkMetaTypeTestCase::dtkMetaTypeTestCase(void) : d(new dtkMetaTypeTestCasePrivate)
{
}

dtkMetaTypeTestCase::~dtkMetaTypeTestCase(void)
{
    delete d;
}

void dtkMetaTypeTestCase::initTestCase(void)
{

}

void dtkMetaTypeTestCase::init(void)
{

}

void dtkMetaTypeTestCase::testIsQObject(void)
{
    QVERIFY(dtk::is_qobject<QObject>::value);
    QVERIFY(dtk::is_qobject<QObject&>::value);
    QVERIFY(dtk::is_qobject<const QObject&>::value);
    QVERIFY(dtk::is_qobject<QObject&&>::value);
    QVERIFY(dtk::is_qobject<QObject *>::value);
    QVERIFY(dtk::is_qobject<const QObject *>::value);
    QVERIFY(dtk::is_qobject<QObject *&>::value);
    QVERIFY(dtk::is_qobject<const QObject *&>::value);
    QVERIFY(dtk::is_qobject<volatile QObject>::value);
    QVERIFY(dtk::is_qobject<const volatile QObject>::value);
    QVERIFY(dtk::is_qobject<volatile QObject *>::value);
    QVERIFY(dtk::is_qobject<const volatile QObject *>::value);

    QVERIFY(dtk::is_qobject<Derived>::value);
    QVERIFY(dtk::is_qobject<Derived&>::value);
    QVERIFY(dtk::is_qobject<const Derived&>::value);
    QVERIFY(dtk::is_qobject<Derived&&>::value);
    QVERIFY(dtk::is_qobject<Derived *>::value);
    QVERIFY(dtk::is_qobject<const Derived *>::value);
    QVERIFY(dtk::is_qobject<Derived *&>::value);
    QVERIFY(dtk::is_qobject<const Derived *&>::value);
    QVERIFY(dtk::is_qobject<volatile Derived>::value);
    QVERIFY(dtk::is_qobject<const volatile Derived>::value);
    QVERIFY(dtk::is_qobject<volatile Derived *>::value);
    QVERIFY(dtk::is_qobject<const volatile Derived *>::value);

    QVERIFY(!dtk::is_qobject<NoDerived>::value);
    QVERIFY(!dtk::is_qobject<NoDerived&>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived&>::value);
    QVERIFY(!dtk::is_qobject<NoDerived&&>::value);
    QVERIFY(!dtk::is_qobject<NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<NoDerived *&>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived *&>::value);
    QVERIFY(!dtk::is_qobject<volatile NoDerived>::value);
    QVERIFY(!dtk::is_qobject<const volatile NoDerived>::value);
    QVERIFY(!dtk::is_qobject<volatile NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<const volatile NoDerived *>::value);

    QVERIFY(dtk::is_qobject<DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice&>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice&>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice&&>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice *&>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice *&>::value);
    QVERIFY(dtk::is_qobject<volatile DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<const volatile DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<volatile DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<const volatile DerivedTwice *>::value);
}

void dtkMetaTypeTestCase::cleanupTestCase(void)
{

}

void dtkMetaTypeTestCase::cleanup(void)
{

}

DTKCORETEST_MAIN_NOGUI(dtkMetaTypeTest, dtkMetaTypeTestCase);

//
// dtkMetaTypeTest.cpp ends here
