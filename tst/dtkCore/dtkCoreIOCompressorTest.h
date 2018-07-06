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

#include <dtkCoreConfig.h>

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
#if defined(DTK_HAVE_ZLIB)
    void testWrite(void);
    void testRead(void);
#endif
    void testCreator(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};


//
// dtkCoreIOCompressorTest.h ends here
