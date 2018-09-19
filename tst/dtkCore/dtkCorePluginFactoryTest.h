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

#pragma once

#include <dtkCoreTest>

class dtkCorePluginFactoryTestCase : public QObject
{
    Q_OBJECT

public:
    dtkCorePluginFactoryTestCase(void);
    ~dtkCorePluginFactoryTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testBasic(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkCorePluginFactoryTestCasePrivate *d;
};

//
// dtkCorePluginFactoryTest.h ends here
