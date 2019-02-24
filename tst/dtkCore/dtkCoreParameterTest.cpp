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

#include "dtkCoreParameterTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreParameter>

class dtkCoreParameterTestCasePrivate
{
public:
};

// ///////////////////////////////////////////////////////////////////

dtkCoreParameterTestCase::dtkCoreParameterTestCase(void) : d(new dtkCoreParameterTestCasePrivate)
{

}

dtkCoreParameterTestCase::~dtkCoreParameterTestCase(void)
{
    delete d;
}

void dtkCoreParameterTestCase::initTestCase(void)
{

}

void dtkCoreParameterTestCase::init(void)
{
}

void dtkCoreParameterTestCase::testDocumentation(void)
{
    QString doc("Documentation very documented");

    dtk::d_real pr(1., -1, 1, doc);
    QCOMPARE(pr.documentation(), doc);

    dtk::d_int pi;
    pi.setDocumentation(doc);
    QCOMPARE(pi.documentation(), doc);
}

void dtkCoreParameterTestCase::testValue(void)
{
    {
        dtk::d_real pr;
        dtk::d_int pi;
        dtk::d_uint pu;

        QCOMPARE((double)pr, 0.);
        QCOMPARE((qlonglong)pi, (qlonglong)0);
        QCOMPARE((qulonglong)pu, (qulonglong)0);

        pr.setValue(std::sqrt(2));
        QCOMPARE(pr.value(), std::sqrt(2));

        pi = -7;
        QCOMPARE(pi.value(), (qlonglong)(-7));
    }
    {
        dtk::d_real pr(std::sqrt(2));
        dtk::d_int pi(-7);
        dtk::d_uint pu(11);

        QCOMPARE((double)pr, std::sqrt(2));
        QCOMPARE((qlonglong)pi, (qlonglong)-7);
        QCOMPARE((qulonglong)pu, (qulonglong)11);

        dtk::d_real cpr(pr);
        dtk::d_int cpi(pi);
        dtk::d_uint cpu(pu);

        QCOMPARE((double)cpr, std::sqrt(2));
        QCOMPARE((qlonglong)cpi, (qlonglong)-7);
        QCOMPARE((qulonglong)cpu, (qulonglong)11);

        pu = 121;
        cpu = pu;
        QCOMPARE((qulonglong)cpu, (qulonglong)121);

        cpi = pu;
        QCOMPARE((qlonglong)cpi, (qlonglong)121);
    }
}

void dtkCoreParameterTestCase::testBounds(void)
{
    {
        dtk::d_real r;
        auto&& bounds = r.bounds();
        QCOMPARE(bounds[0], std::numeric_limits<double>::min());
        QCOMPARE(bounds[1], std::numeric_limits<double>::max());
    }
    {
        dtk::d_real r(0., -std::sqrt(2)/2, std::sqrt(2)/2);
        auto&& bounds = r.bounds();
        QCOMPARE(bounds[0], -std::sqrt(2)/2);
        QCOMPARE(bounds[1], std::sqrt(2)/2);

        r.setMinimum(r.min() * 2);
        r.setMaximum(r.max() * 2);

        QCOMPARE(r.min(), -std::sqrt(2));
        QCOMPARE(r.max(), std::sqrt(2));

        r.setBounds(-std::sqrt(2)/2, std::sqrt(2)/2);
        QCOMPARE(bounds[0], -std::sqrt(2)/2);
        QCOMPARE(bounds[1], std::sqrt(2)/2);

        r.setBounds(r.min() * 2, r.max() * 2);
        QCOMPARE(r.min(), -std::sqrt(2));
        QCOMPARE(r.max(), std::sqrt(2));
    }
}

void dtkCoreParameterTestCase::testDecimals(void)
{
    dtk::d_int pi;
    QCOMPARE(pi.decimals(), 0);

    {
        dtk::d_real pr;
        QCOMPARE(pr.decimals(), (int)(std::numeric_limits<double>::max_digits10/1.75));

        pr.setDecimals(11);
        QCOMPARE(pr.decimals(), 11);
    }

    dtk::d_real pr(0., -1, 1, 11);
    QCOMPARE(pr.decimals(), 11);
}

void dtkCoreParameterTestCase::testVariant(void)
{
    // Builtin type in variant
    QVariant v(std::sqrt(2));
    dtk::d_real r(v);
    QCOMPARE((double)r, std::sqrt(2));
    r = 0;
    QCOMPARE((double)r, 0.);
    r.setValue(v);
    QCOMPARE((double)r, std::sqrt(2));

    // dtkCoreParameter in variant
    v = r.variant();
    dtk::d_real pr(v);
    QCOMPARE((double)pr, std::sqrt(2));

    // Bounds and decimals
    r = dtk::d_real(0., -1, 1, 11);
    v = r.variant();
    pr.setValue(v);
    QCOMPARE(pr.min(), -1.);
    QCOMPARE(pr.max(), 1.);
    QCOMPARE(pr.decimals(), 11);
}

void dtkCoreParameterTestCase::testOperations(void)
{
    double r0 = std::sqrt(2);
    double r1 = std::sqrt(3);
    double r2 = std::sqrt(5);

    dtk::d_real pr0(r0);
    dtk::d_real pr1(r1);
    dtk::d_real pr2(r2);

    {
        // auto cast to builtin type in basic operations
        auto pres = pr0 + pr1 / pr2;
        QCOMPARE(pres, (r0+r1/r2));
    }

    {
        // AddAssign
        pr0 = 0;
        pr0 += r0;
        QCOMPARE((double)pr0, r0);
        pr0 += pr1;
        QCOMPARE((double)pr0, r0+r1);
        pr0 += pr2.variant();
        QCOMPARE((double)pr0, (r0+r1+r2));
        pr0 = r0;
    }

    {
        // SubAssign
        pr0 = 0;
        pr0 -= r0;
        QCOMPARE((double)pr0, -r0);
        pr0 -= pr1;
        QCOMPARE((double)pr0, -r0-r1);
        pr0 -= pr2.variant();
        QCOMPARE((double)pr0, (-r0-r1-r2));
        pr0 = r0;
    }

    {
        // MulAssign
        pr0 = 1;
        pr0 *= r0;
        QCOMPARE((double)pr0, r0);
        pr0 *= pr1;
        QCOMPARE((double)pr0, r0*r1);
        pr0 *= pr2.variant();
        QCOMPARE((double)pr0, (r0*r1*r2));
        pr0 = r0;
    }

    {
        // DivAssign
        pr0 = 1;
        pr0 /= r0;
        QCOMPARE((double)pr0, 1./r0);
        pr0 /= pr1;
        QCOMPARE((double)pr0, 1./(r0*r1));
        pr0 /= pr2.variant();
        QCOMPARE((double)pr0, 1./(r0*r1*r2));
        pr0 = r0;
    }

    // Modulo
    qulonglong ui0 = 27;
    qulonglong ui1 = 3;
    dtk::d_uint pui0(ui0);
    dtk::d_uint pui1(ui1);

    QCOMPARE(pui0 % pui1, ui0 % ui1);

    pui0 %= ui1;
    QCOMPARE((qulonglong)pui0, ui0 % ui1);
    pui0 = ui0;

    pui0 %= pui1;
    QCOMPARE((qulonglong)pui0, ui0 % ui1);
    pui0 = ui0;

    pui0 %= pui1.variant();
    QCOMPARE((qulonglong)pui0, ui0 % ui1);
    pui0 = ui0;

    pui0 %= QVariant(ui1);
    QCOMPARE((qulonglong)pui0, ui0 % ui1);
}

void dtkCoreParameterTestCase::testComparisons(void)
{
    double r0 = std::sqrt(2);
    double r1 = std::sqrt(3);
    double r2 = std::sqrt(5);

    dtk::d_real pr0(r0);
    dtk::d_real pr1(r1);
    dtk::d_real pr2(r2);

    QVERIFY(pr0 == r0);
    QVERIFY(pr1 == r1);
    QVERIFY(pr2 == r2);

    pr0 = r1;
    QVERIFY(pr0 == r1);
    QVERIFY(pr0 == pr1);
    QVERIFY(pr0 == pr1.variant());

    QVERIFY(pr0 != r2);
    QVERIFY(pr0 != pr2);
    QVERIFY(pr0 != pr2.variant());

    qlonglong i = 121;
    dtk::d_int pi = i;
    pr0 = pi;
    QVERIFY(pr0 == i);
    QVERIFY(pr0 == pi);
    //QVERIFY(pr0 == pi.variant()); // Fails since no explicit conversions between parameters of different types

    pr0 = r0;
    QVERIFY(pr0 <= r0);
    QVERIFY(pr0 < r1);
    QVERIFY(pr2 > r1);
    QVERIFY(pr1 >= r1);

    QVERIFY(pr0 <= pr0);
    QVERIFY(pr0 < pr1);
    QVERIFY(pr2 > pr1);
    QVERIFY(pr2 >= pr2);

    QVERIFY(pr0 < pi);
}

void dtkCoreParameterTestCase::testDataStream(void)
{
    dtk::d_real pro(1., 1-std::sqrt(2)/2, 1+std::sqrt(2)/2);
    dtk::d_int pio(1, 0, 2);

    QByteArray data;
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out << pro;
        out << pio;
    }

    dtk::d_real pri;
    dtk::d_int pii;
    {
        QDataStream in(data);
        in >> pri;
        in >> pii;
    }

    QCOMPARE(pro, pri);
    QCOMPARE(pro.min(), pri.min());
    QCOMPARE(pro.max(), pri.max());
    QCOMPARE(pro.decimals(), pri.decimals());
    QCOMPARE(pio, pii);
    QCOMPARE(pio.min(), pii.min());
    QCOMPARE(pio.max(), pii.max());
    QCOMPARE(pio.decimals(), pii.decimals());

    data.clear();
    QVariant vro = pro.variant();
    QVariant vio = pio.variant();
    qRegisterMetaTypeStreamOperators<dtk::d_real>("dtk::d_real");
    qRegisterMetaTypeStreamOperators<dtk::d_int>("dtk::d_int");
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out << vro;
        out << vio;
    }
    QVariant vri;
    QVariant vii;
    {
        QDataStream in(data);
        in >> vri;
        in >> vii;
    }
    pri.setValue(vri);
    pii.setValue(vii);

    QCOMPARE(pro, pri);
    QCOMPARE(pro.min(), pri.min());
    QCOMPARE(pro.max(), pri.max());
    QCOMPARE(pro.decimals(), pri.decimals());
    QCOMPARE(pio, pii);
    QCOMPARE(pio.min(), pii.min());
    QCOMPARE(pio.max(), pii.max());
    QCOMPARE(pio.decimals(), pii.decimals());
}

void dtkCoreParameterTestCase::cleanupTestCase(void)
{

}

void dtkCoreParameterTestCase::cleanup(void)
{

}

DTKCORETEST_MAIN_NOGUI(dtkCoreParameterTest, dtkCoreParameterTestCase);

//
// dtkCoreParameterTest.cpp ends here
