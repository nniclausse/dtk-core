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

class dtkCoreParameterReaderTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreParameterReaderTestCase(void);
    ~dtkCoreParameterReaderTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testRead(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkCoreParameterTest.h ends here
