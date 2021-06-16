// dtkCoreParameterTest.h
//

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
    void testRegistration(void);
    void testCreation(void);
    void testLabel(void);
    void testDocumentation(void);
    void testValue(void);
    void testBounds(void);
    void testDecimals(void);
    void testVariant(void);
    void testCoreParameter(void);
    void testOperations(void);
    void testComparisons(void);
    void testDataStream(void);
    void testBoolean(void);
    void testConnection(void);
    void testText(void);
    void testRange(void);
    void testFile(void);
    void testReadParameters(void);
    void testReadParametersResources(void);
    void testToVariantHash(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkCoreParameterTestCasePrivate *d;
};

//
// dtkCoreParameterTest.h ends here
