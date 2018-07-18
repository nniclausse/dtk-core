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

#include <QtCore>

class dtkCoreMetaTypeTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreMetaTypeTestCase(void);
    ~dtkCoreMetaTypeTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testIsQObject(void);
    void testCanConvert(void);
    void testVariantFromValue(void);
    void testClone(void);
    void testCopy(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkCoreMetaTypeTestCasePrivate *d;
};

//
// dtkCoreMetaTypeTest.h ends here
