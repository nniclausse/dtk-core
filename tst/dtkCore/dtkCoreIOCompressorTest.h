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

class dtkCoreIOCompressorTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreIOCompressorTestCase(void) = default;
    ~dtkCoreIOCompressorTestCase(void) = default;

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testWrite(void);
    void testRead(void);
    void testCreator(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};


//
// dtkCoreIOCompressorTest.h ends here
