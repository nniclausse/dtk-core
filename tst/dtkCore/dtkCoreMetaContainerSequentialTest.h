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

class dtkCoreMetaContainerSequentialTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreMetaContainerSequentialTestCase(void) = default;
    ~dtkCoreMetaContainerSequentialTestCase(void) = default;

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testConversion(void);
    void testBasics(void);
    void testQList(void);
    void testQVector(void);
    void testQVarLengthArray(void);
    void testStdList(void);
    void testStdVector(void);

    void testBenchVec(void);
    void testBenchMetaItemAt(void);
    void testBenchMetaVariantAt(void);
    void testBenchMetaConstIterators(void);
    void testBenchMetaIterators(void);
    void testBenchMetaIteratorsDirect(void);
    void testBenchMetaOperatorConst(void);
    void testBenchMetaOperator(void);
    void testBenchMetaRangeLoopConst(void);
    void testBenchMetaRangeLoop(void);

    void testBenchVecSetAt(void);
    void testBenchMetaSetAt(void);
    void testBenchMetaSetAtIterator(void);
    void testBenchMetaSetAtOperator(void);
    void testBenchMetaSetAtRange(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkCoreMetaContainerSequentialTest.h ends here
