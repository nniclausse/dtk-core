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

class dtkMetaTypeTestCase : public QObject
{
    Q_OBJECT

public:
     dtkMetaTypeTestCase(void);
    ~dtkMetaTypeTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testIsQObject(void);
    void testVariantFromValue(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkMetaTypeTestCasePrivate *d;
};

//
// dtkMetaTypeTest.h ends here
