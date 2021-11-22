// dtkCoreAsKeyValueRangeTest.cpp
//

#include "dtkCoreAsKeyValueRangeTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreAsKeyValueRange>

#include <ciso646>

class dtkCoreAsKeyValueRangeTestCasePrivate
{
public:
};
// ///////////////////////////////////////////////////////////////////


dtkCoreAsKeyValueRangeTestCase::dtkCoreAsKeyValueRangeTestCase(void) : d(new dtkCoreAsKeyValueRangeTestCasePrivate)
{

}

dtkCoreAsKeyValueRangeTestCase::~dtkCoreAsKeyValueRangeTestCase(void)
{
    delete d;
}

void dtkCoreAsKeyValueRangeTestCase::initTestCase(void)
{

}

void dtkCoreAsKeyValueRangeTestCase::init(void)
{
}

void dtkCoreAsKeyValueRangeTestCase::testMap(void)
{
    {
        QMap<QString, double> map;
        map["One"] = 1;
        map["Two"] = 2;
        map["Three"] = 3;

        auto it = map.begin();
        for (auto [key, value] : dtk::core::asKeyValueRange(map)) {
            qDebug() << Q_FUNC_INFO << key << value;
            QCOMPARE(it.key(), key);
            QCOMPARE(it.value(), value);
            ++it;
        }
    }
}

void dtkCoreAsKeyValueRangeTestCase::cleanupTestCase(void)
{

}

void dtkCoreAsKeyValueRangeTestCase::cleanup(void)
{

}

DTKCORETEST_MAIN_NOGUI(dtkCoreAsKeyValueRangeTest, dtkCoreAsKeyValueRangeTestCase);

//
// dtkCoreAsKeyValueRangeTest.cpp ends here
