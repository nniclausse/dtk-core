// dtkCoreAsKeyValueRangeTest.h
//

#include <QtCore>

class dtkCoreAsKeyValueRangeTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreAsKeyValueRangeTestCase(void);
    ~dtkCoreAsKeyValueRangeTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testMap(void);
    void testHash(void);
    void testParameterCollection(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    class dtkCoreAsKeyValueRangeTestCasePrivate *d;
};

//
// dtkCoreAsKeyValueRangeTest.h ends here
