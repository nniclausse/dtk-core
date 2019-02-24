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

#include <QtCore>

class dtkCoreParameterTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreParameterTestCase(void);
    ~dtkCoreParameterTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testDocumentation(void);
    void testValue(void);
    void testBounds(void);
    void testDecimals(void);
    void testVariant(void);
    void testOperations(void);
    void testComparisons(void);
    void testDataStream(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkCoreParameterTestCasePrivate *d;
};

//
// dtkCoreParameterTest.h ends here
