// dtkCoreAsKeyValueRangeTest.cpp
//

#include "dtkCoreAsKeyValueRangeTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreAsKeyValueRange>
#include <dtkCore/dtkCoreParameterCollection>

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
    QMap<QString, double> map;
    map["One"] = 1;
    map["Two"] = 2;
    map["Three"] = 3;

    auto rit = map.begin();
    //for (auto [key, value] : dtk::core::asKeyValueRange(map)) {
    for (auto it : dtk::core::asKeyValueRange(map)) {
        qDebug() << Q_FUNC_INFO << it.first << it.second;
        QCOMPARE(rit.key(), it.first);
        QCOMPARE(rit.value(), it.second);
        ++rit;
    }
}

void dtkCoreAsKeyValueRangeTestCase::testHash(void)
{
    QHash<QString, double> h;
    h["One"] = 1;
    h["Two"] = 2;
    h["Three"] = 3;

    auto rit = h.begin();
    //for (auto [key, value] : dtk::core::asKeyValueRange(h)) {
    for (auto it : dtk::core::asKeyValueRange(h)) {
        qDebug() << Q_FUNC_INFO << it.first << it.second;
        QCOMPARE(rit.key(), it.first);
        QCOMPARE(rit.value(), it.second);
        ++rit;
    }
}

void dtkCoreAsKeyValueRangeTestCase::testParameterCollection(void)
{
    QString json_file(QFINDTESTDATA("../resources/parameters_def.json"));

    dtkCoreParameterCollection collection(dtk::core::readParameters(json_file));
    auto rit = collection.begin();
    //for (auto [key, value] : dtk::core::asKeyValueRange(h)) {
    for (auto it : dtk::core::asKeyValueRange(collection)) {
        qDebug() << Q_FUNC_INFO << it.first << it.second->documentation();
        QCOMPARE(rit.key(), it.first);
        QCOMPARE(rit.value(), it.second);
        ++rit;
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
