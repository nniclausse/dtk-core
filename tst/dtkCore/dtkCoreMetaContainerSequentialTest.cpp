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

#include "dtkCoreMetaContainerSequentialTest.h"
#include "dtkCoreMetaContainerSequentialTest.tpp"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreMetaType>
#include <dtkCore/dtkCoreMetaContainerSequential>

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequentialTestCase implementation
// ///////////////////////////////////////////////////////////////////

void dtkCoreMetaContainerSequentialTestCase::initTestCase(void)
{

}

void dtkCoreMetaContainerSequentialTestCase::init(void)
{

}

void dtkCoreMetaContainerSequentialTestCase::cleanup(void)
{

}

void dtkCoreMetaContainerSequentialTestCase::cleanupTestCase(void)
{

}

void dtkCoreMetaContainerSequentialTestCase::testConversion(void)
{
    QVariant var;

    QStringList slist;
    var = dtk::variantFromValue(&slist);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));

    QList<int> list;
    var = dtk::variantFromValue(&list);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));

    QVector<QString> vec;
    var = dtk::variantFromValue(&vec);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));

    QVarLengthArray<double> vla;
    var = dtk::variantFromValue(&vla);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));

    std::list<double> std_l;
    var = dtk::variantFromValue(&std_l);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));

    std::vector<double> std_v;
    var = dtk::variantFromValue(&std_v);
    QVERIFY(dtk::canConvert<dtkCoreMetaContainerSequential>(QList<int>({var.userType()})));
}

const int N = 1000000;
static double s = 0;

void dtkCoreMetaContainerSequentialTestCase::testBasics(void)
{
    typedef std::list<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < size; ++i) {
        c_i.push_back(0);
    }

    dtkCoreMetaContainerSequentialHandler *h = new dtkCoreMetaContainerSequentialHandlerTemplate<ArrayInt>(&c_i);
    dtkCoreMetaContainerSequential mc(h);

    QVERIFY(!mc.empty());
    QCOMPARE(size, mc.size());

    QVERIFY(mc.hasBiDirectionalIterator());
    QVERIFY(!mc.hasRandomAccessIterator());

    mc.reserve(size+1);
    mc.resize(size);

    for (int i = 0; i < size; ++i) {
        mc.setAt(i, values_i[i]);
    }

    int count = 0;

    for (int i : c_i) {
        QCOMPARE(i, values_i[count++]);
    }

    for (int i = 0; i < size; ++i) {
        QCOMPARE(mc.at<int>(i), values_i[i]);
    }

    auto cit  = mc.cbegin();
    auto cend = mc.cend();

    for (int i = 0; cit != cend; ++cit, ++i) {
        QCOMPARE((*cit).value<int>(), values_i[i]);
    }

    auto it  = mc.begin();
    auto end = mc.end();

    for (int i = 0; it != end; ++it, ++i) {
        QCOMPARE((it).value<int>(), values_i[i]);
    }
}

void dtkCoreMetaContainerSequentialTestCase::testQList(void)
{
    using ArrayInt = QList<int>;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(size, c_i.size());

    typedef QList<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(size, c_s.size());
}

void dtkCoreMetaContainerSequentialTestCase::testQVector(void)
{
    using ArrayInt = QVector<int>;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, c_i.size());

    typedef QVector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, c_s.size());
}

void dtkCoreMetaContainerSequentialTestCase::testQVarLengthArray(void)
{
    typedef QVarLengthArray<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, c_i.size());

    typedef QVarLengthArray<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, c_s.size());
}

void dtkCoreMetaContainerSequentialTestCase::testStdList(void)
{
    typedef std::list<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, (int)c_i.size());

    typedef std::list<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, (int)c_s.size());
}

void dtkCoreMetaContainerSequentialTestCase::testStdVector(void)
{
    typedef std::vector<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, (int)c_i.size());

    typedef std::vector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, (int)c_s.size());
}

void dtkCoreMetaContainerSequentialTestCase::testBenchVec(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QBENCHMARK {
        s = 0;

        for (int i = 0; i != N; ++i)
            s += vec[i];
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaItemAt(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaVariantAt(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (int i = 0; i != N; ++i)
            s += mvec.at(i).value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaConstIterators(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkCoreMetaContainerSequential::const_iterator it  = mvec.cbegin();
        dtkCoreMetaContainerSequential::const_iterator end = mvec.cend();

        for (; it != end; ++it)
        {
            s += (*it).value<double>();
        }
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaIterators(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkCoreMetaContainerSequential::iterator it  = mvec.begin();
        dtkCoreMetaContainerSequential::iterator end = mvec.end();

        for (; it != end; ++it)
        {
            s += (*it).value<double>();
        }
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaIteratorsDirect(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkCoreMetaContainerSequential::iterator it  = mvec.begin();
        dtkCoreMetaContainerSequential::iterator end = mvec.end();

        for (; it != end; ++it)
        {
            s += (it).value<double>();
        }
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaOperatorConst(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    const dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaOperator(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaRangeLoopConst(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    const dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (const QVariant& var : mvec)
            s += var.value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaRangeLoop(void)
{
    QVector<double> vec(N);

    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        s = 0;

        for (dtkCoreMetaContainerSequential::item& it : mvec)
            s += it.value<double>();
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchVecSetAt(void)
{
    QVector<double> vec(N);
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            vec[i] = i;
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaSetAt(void)
{
    QVector<double> vec(N);
    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            mvec.setAt(i, i);
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaSetAtIterator(void)
{
    QVector<double> vec(N);
    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        dtkCoreMetaContainerSequential::iterator it  = mvec.begin();
        dtkCoreMetaContainerSequential::iterator end = mvec.end();

        for (int i = 0; it != end; ++it, ++i)
        {
            *it = i;
        }
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaSetAtOperator(void)
{
    QVector<double> vec(N);
    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            mvec[i] = i;
    }
}

void dtkCoreMetaContainerSequentialTestCase::testBenchMetaSetAtRange(void)
{
    QVector<double> vec(N);
    QVariant vc = dtk::variantFromValue(&vec);
    dtkCoreMetaContainerSequential mvec = vc.value<dtkCoreMetaContainerSequential>();
    QBENCHMARK {
        int i = -1;

        for (dtkCoreMetaContainerSequential::item& it : mvec)
        {
            it = ++i;
        }
    }
}

DTKCORETEST_MAIN_NOGUI(dtkCoreMetaContainerSequentialTest, dtkCoreMetaContainerSequentialTestCase);

//
// dtkCoreMetaContainerSequentialTest.cpp ends here
