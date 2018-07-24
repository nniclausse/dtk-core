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


#include "dtkCorePluginFactoryTest.h"

#include <dtkCoreTest>

#include <dtkAbstractCoreConcept.h>

#include <dtkCoreConceptFooPlugin/dtkCoreConceptFoo.h>
#include <dtkCoreConceptFooPlugin/dtkCoreConceptFoo_p.h>
#include <dtkCoreConceptFooPlugin/dtkCoreConceptFooPlugin.h>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class dtkCorePluginFactoryTestCasePrivate
{
public:
    dtkAbstractCoreConceptPluginFactory factory;
};

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

dtkCorePluginFactoryTestCase::dtkCorePluginFactoryTestCase(void) : d(new dtkCorePluginFactoryTestCasePrivate)
{

}

dtkCorePluginFactoryTestCase::~dtkCorePluginFactoryTestCase(void)
{
    delete d;
}

void dtkCorePluginFactoryTestCase::initTestCase(void)
{
    d->factory.record("TOTO", dtkCoreConceptFooCreator);
}

void dtkCorePluginFactoryTestCase::init(void)
{

}

void dtkCorePluginFactoryTestCase::testBasic(void)
{
    dtkAbstractCoreConcept *concept = d->factory.create("TOTO");
    QVERIFY(concept);

    QVariant var = concept->output();

    dtkCoreConceptFooData data = var.value<dtkCoreConceptFooData>();

    QCOMPARE(QString("dtkCoreConceptFooData"), data.name());
}

void dtkCorePluginFactoryTestCase::cleanup(void)
{

}

void dtkCorePluginFactoryTestCase::cleanupTestCase(void)
{

}

DTKCORETEST_MAIN_NOGUI(dtkCorePluginFactoryTest, dtkCorePluginFactoryTestCase)

//
// dtkCorePluginFactoryTest.cpp ends here
