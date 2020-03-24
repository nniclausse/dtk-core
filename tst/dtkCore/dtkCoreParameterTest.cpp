// dtkCoreParameterTest.cpp
//

#include "dtkCoreParameterTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreParameter>
#include <dtkCore/dtkCoreParameterPath>

#include <ciso646>

class dtkCoreParameterTestCasePrivate
{
public:
};

// ///////////////////////////////////////////////////////////////////
// example on how to use dtkCoreParameterSimple
// (see code at dtkCoreParameterTestCase::testText(void)
//)
// use std::string as dtkCoreParameter
// (dtk::d_string is implemented on QString and not on std::string)
//
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(dtkCoreParameterSimple<std::string>)
//
// ///////////////////////////////////////////////////////////////////

QDebug& operator << (QDebug &dbg, const std::string &p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.c_str();
    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

// ///////////////////////////////////////////////////////////////////


dtkCoreParameterTestCase::dtkCoreParameterTestCase(void) : d(new dtkCoreParameterTestCasePrivate)
{
    dtk::core::registerParameters();
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

void dtkCoreParameterTestCase::testLabel(void)
{
    QString label("Parameter label");

    dtk::d_real pr(label, 1., -1, 1);
    QCOMPARE(pr.label(), label);

    dtk::d_int pi;
    pi.setLabel(label);
    QCOMPARE(pi.label(), label);
}

void dtkCoreParameterTestCase::testDocumentation(void)
{
    QString doc("Documentation very documented");

    dtk::d_real pr("pr", 1., -1, 1, doc);
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

        pr.setValue(0.0);
        QCOMPARE(double(pr), 0.0);

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
        // check all default numeric bouds
        dtk::d_real r;
        auto&& bounds = r.bounds();
        QCOMPARE(bounds[0], std::numeric_limits<double>::lowest());
        QCOMPARE(bounds[1], std::numeric_limits<double>::max());
    }
    {
        dtk::d_uint ui;
        auto&& bounds = ui.bounds();
        QCOMPARE(bounds[0], std::numeric_limits<qulonglong>::lowest());
        QCOMPARE(bounds[1], std::numeric_limits<qulonglong>::max());
    }
    {
        dtk::d_int i;
        auto&& bounds = i.bounds();
        QCOMPARE(bounds[0], std::numeric_limits<qlonglong>::lowest());
        QCOMPARE(bounds[1], std::numeric_limits<qlonglong>::max());

    }
    {
        dtk::d_real r("r", 0., -std::sqrt(2)/2, std::sqrt(2)/2);
        auto&& bounds = r.bounds();
        QCOMPARE(bounds[0], -std::sqrt(2)/2);
        QCOMPARE(bounds[1], std::sqrt(2)/2);
    }
    {
        // do stupid things with values and bounds
        dtk::d_real r("r", 0.25, -1.0, 1.0);

        // do stupid things with the value
        r = 0.25;
        QCOMPARE( r.value(), 0.25 ); // back to normal

        //r = -3.0;    // r is outside the boundaries
        //QCOMPARE( r.value(), r.min()); // in this case, we stick to the min()

        //r =  3.0;    // r is outside the boundaries
        //QCOMPARE( r.value(), r.max()); // in this case, we stick to the max()
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

    dtk::d_real pr("pr", 0., -1, 1, 11);
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
    r = dtk::d_real("label", 0., -1, 1, 11);
    v = r.variant();
    pr.setValue(v);
    QCOMPARE(pr.min(), -1.);
    QCOMPARE(pr.max(), 1.);
    QCOMPARE(pr.decimals(), 11);

    // variant out of range
    dtk::d_real por("por", 10.0, 9.0, 11.0); // 10 in [9,11] interval
    r = dtk::d_real("label", 0., -1, 1, 11);
    v = r.variant();                  // r is out of range
    por.setValue(v);

}

void dtkCoreParameterTestCase::testCoreParameter(void)
{
    dtk::d_real p0(std::sqrt(2));
    dtk::d_int p1(7);
    dtk::d_string p2("toto");

    dtkCoreParameter *pp0 = &p0;
    dtkCoreParameter *pp1 = &p1;
    dtkCoreParameter *pp2 = &p2;

    {
        dtk::d_int i0 = 0;
        dtk::d_real c0 = pp0;
        dtk::d_int c1 = pp1;
        dtk::d_string c2 = pp2;

        QCOMPARE(c0, p0);
        QCOMPARE(c1, p1);
        QCOMPARE(c2, p2);
    }

    {
        dtk::d_real c0 = 2.;
        dtk::d_int c1 = 3;
        dtk::d_string c2 = dtk::d_string("tutu");

        c0 = pp0;
        c1 = pp1;
        c2 = pp2;

        QCOMPARE(c0, p0);
        QCOMPARE(c1, p1);
        QCOMPARE(c2, p2);
    }
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
    QString t_string = QString("string to test against");
    dtk::d_real   pro("pro", 1., 1-std::sqrt(2)/2, 1+std::sqrt(2)/2);
    dtk::d_int    pio("pio", 1, 0, 2);
    dtk::d_bool   pbo(true);
    dtk::d_string pso(t_string);

    QByteArray data;
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out << pro;
        out << pio;
        out << pbo;
        out << pso;
    }

    dtk::d_real   pri;
    dtk::d_int    pii;
    dtk::d_bool   pbi;
    dtk::d_string psi;
    {
        QDataStream in(data);
        in >> pri;
        in >> pii;
        in >> pbi;
        in >> psi;
    }

    QCOMPARE(pro, pri);
    QCOMPARE(pro.min(), pri.min());
    QCOMPARE(pro.max(), pri.max());
    QCOMPARE(pro.decimals(), pri.decimals());

    QCOMPARE(pio, pii);
    QCOMPARE(pio.min(), pii.min());
    QCOMPARE(pio.max(), pii.max());
    QCOMPARE(pio.decimals(), pii.decimals());

    QCOMPARE(pbo == pbi, true);

    QCOMPARE(pso == psi, true);

    data.clear();
    QVariant vro = pro.variant();
    QVariant vio = pio.variant();
    QVariant vbo = pbo.variant();
    QVariant vso = pso.variant();
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out << vro;
        out << vio;
        out << vbo;
        out << vso;
    }
    QVariant vri;
    QVariant vii;
    QVariant vbi;
    QVariant vsi;
    {
        QDataStream in(data);
        in >> vri;
        in >> vii;
        in >> vbi;
        in >> vsi;
    }
    pri.setValue(vri);
    pii.setValue(vii);
    pbi.setValue(vbi);
    psi.setValue(vsi);

    QCOMPARE(pro, pri);
    QCOMPARE(pro.min(), pri.min());
    QCOMPARE(pro.max(), pri.max());
    QCOMPARE(pro.decimals(), pri.decimals());

    QCOMPARE(pio, pii);
    QCOMPARE(pio.min(), pii.min());
    QCOMPARE(pio.max(), pii.max());
    QCOMPARE(pio.decimals(), pii.decimals());

    QCOMPARE(pbo == pbi, true);

    QCOMPARE(pso == psi, true);
    QCOMPARE(psi , pso);
    QVERIFY(pso.value() == psi.value());
    QVERIFY(pso.value() != psi.value()+"toto");
}

void dtkCoreParameterTestCase::testBoolean(void)
{
    // one boolean
    dtk::d_bool b1;  // b1 <= false
    QCOMPARE( b1 == false, true);

    b1 = not(b1); // b1 <= true
    QCOMPARE( b1 == true, true);

    b1 = not(b1); // b1 <= false
    QCOMPARE( b1 == false, true);

    b1.setValue(true);
    QCOMPARE( b1 == true, true);
    QCOMPARE( b1.value(), true);

    b1.setValue(false);
    QCOMPARE( b1 == false, true);
    QCOMPARE( b1.value(), false);

    // one *bool
    dtk::d_bool *pb;

    pb = new dtk::d_bool();
    QCOMPARE( *pb == false, true);
    delete(pb);

    pb = new dtk::d_bool(true);
    QCOMPARE( *pb == true, true);
    delete(pb);

    QString doc("Stupid declaration");
    pb = new dtk::d_bool("pb", true, true, true, doc);
    QCOMPARE( *pb == true, true);
    QCOMPARE( pb->documentation(), doc);
    delete(pb);

    // two booleans
    dtk::d_bool b2(true); // b2 <= true
    QCOMPARE( b2 == true, true);
    QCOMPARE( b1 == b2, false);

    b1 = not(b1); // b1 <= true
    QCOMPARE( b1 == b2, true);

    // third variable
    dtk::d_bool b3;

    // OR
    b1 = true;
    b2 = true;
    b3 = b1 + b2 ; // true OR true
    QCOMPARE( b1 == true, true);
    QCOMPARE( b2 == true, true);
    QCOMPARE( b3 == true, true);

    b1 = true;
    b2 = false;
    b3 = b1 + b2 ; // true OR false
    QCOMPARE( b1 == true, true);
    QCOMPARE( b2 == false, true);
    QCOMPARE( b3 == true, true);

    b1 = false;
    b2 = false;
    b3 = b1 + b2 ; // false OR false
    QCOMPARE( b1 == false, true);
    QCOMPARE( b2 == false, true);
    QCOMPARE( b3 == false, true);

    // AND
    b1 = true;
    b2 = true;
    b3 = b1 * b2 ; // true AND true
    QCOMPARE( b2 == true, true);
    QCOMPARE( b3 == true, true);
    QCOMPARE( b1 == true, true);

    b1 = true;
    b2 = false;
    b3 = b1 * b2 ; // true AND false
    QCOMPARE( b1 == true, true);
    QCOMPARE( b2 == false, true);
    QCOMPARE( b3 == false, true);

    b1 = false;
    b2 = false;
    b3 = b1 * b2 ; // false AND false
    QCOMPARE( b1 == false, true);
    QCOMPARE( b2 == false, true);
    QCOMPARE( b3 == false, true);

    // NOT
    b1 = true;
    b2 = !b1;
    QCOMPARE( b1 == b2, false);

    b1 = false;
    b2 = !b1;
    QCOMPARE( b1 == b2, false);
}

void dtkCoreParameterTestCase::testConnection(void)
{
    dtk::d_real pr("pr", 0.0, -10.0, 10.0);
    dtk::d_real default_value("default_value", 0.0, -10.0, 10.0);
    dtk::d_real bad_value(12345.6789);
    QVariant variant_good = QVariant(3.14);
    QVariant variant_bad  = QVariant(31415.957);

    int signal_count = 0;
    int error_count = 0;

    // check the signal capture for the next setValue( sqrt(2) ) ;

    auto f = [=, &signal_count] (QVariant v) {
                 //qDebug() << Q_FUNC_INFO << "Value changed catched for *pr* :" << v;  // keeped as a comment for purpose
                 QCOMPARE(v.value<dtk::d_real>().value(), std::sqrt(2));
                 signal_count++;
             };
    pr.connect(f);

    // catch invalid values setting
    pr.connectFail( [=, &error_count] () { ++error_count; } );

    pr.setValue(std::sqrt(2));  // this one is catched by the previous signal
    QCOMPARE(pr.value(), std::sqrt(2)); // same test out of the signal routine
    QCOMPARE(signal_count, 1);  // check that signal has been sent

    pr.sync();                  // resend the signal manually
    QCOMPARE(signal_count, 2);  // check that signal has really been sent

    pr.setValue(12345.6789);  // requested value out of range -> should emit a invalidValue signal
    QCOMPARE(pr.value(), std::sqrt(2)); // value unchanged
    QCOMPARE(error_count, 1);   // error count incremented
    QCOMPARE(signal_count, 2);  // valid_signal not catched

    pr.disconnect();  // disconnect the signal to avoid a false QCOMPARE


    pr.setValue(1.0);            // this one is not catched by the previous signal anymore
    QCOMPARE(pr.value(), 1.0); // value has been changed
    QCOMPARE(error_count, 1);   // error count not changed

    pr.setValue(default_value);
    QCOMPARE(pr.value(), 0.0); // value has been changed
    QCOMPARE(error_count, 1);   // error count not changed

    pr.setValue(bad_value);
    QCOMPARE(pr.value(), 0.0); // value has not been changed
    QCOMPARE(error_count, 2);   // error count incremented

    pr.setValue(variant_good);
    QCOMPARE(pr.value(), variant_good.toDouble());  // value has been changed
    QCOMPARE(error_count, 2);   // error count unchanged

    pr.setValue(variant_bad);
    QCOMPARE(pr.value(), variant_good.toDouble());  // value has not been changed
    QCOMPARE(error_count, 3);   // error count incremented

    // Test shared connection

    pr.setValue(std::sqrt(2));

    // No implicit connection
    dtk::d_real p_shared = pr;
    p_shared.sync();            // This call must not call lambda f
    QCOMPARE(signal_count, 2);  // valid_signal must be thus the same

    pr.connect(f);
    p_shared.shareConnectionWith(&pr);

    p_shared.sync();            // This call must call lambda f
    QCOMPARE(signal_count, 3);  // valid_signal must be thus incremented

    // No implicit sharing of connection
    dtk::d_real pp = p_shared;
    pp.sync();
    QCOMPARE(signal_count, 3);

    dtk::d_real ppp;
    ppp.copyAndShare(&pr);
    ppp.sync();
    QCOMPARE(signal_count, 4);

    auto vv = pr.variant();
    pp.copyAndShare(vv);
    pp.sync();
    QCOMPARE(signal_count, 5);

    ppp.disconnect();
    ppp.sync();
    QCOMPARE(signal_count, 5);
    pp.sync();
    QCOMPARE(signal_count, 6);

    int signal_bis_count = 0;
    auto fbis = [=, &signal_bis_count] (QVariant v) {
                    signal_bis_count++;
                };

    pp.disconnect(); // Needs explicit disconnection to forget previous connections
                     // without deleting them if they are shared.

    pr.sync(); // Checks that previous call does not delete the connection
    QCOMPARE(signal_count, 7);
    --signal_count;

    pp.connect(fbis);
    pp.sync();
    QCOMPARE(signal_count, 6);
    QCOMPARE(signal_bis_count, 1);
    pr.sync();
    QCOMPARE(signal_count, 7);
    QCOMPARE(signal_bis_count, 1);

    ppp.shareConnectionWith(&pp);
    ppp.sync();
    QCOMPARE(signal_count, 7);
    QCOMPARE(signal_bis_count, 2);

    // multi connection
    pp.connect(f); // pp is already connected to fbis so sync must increase both counters.
    pp.sync();
    QCOMPARE(signal_count, 8);
    QCOMPARE(signal_bis_count, 3);
}

void dtkCoreParameterTestCase::testText(void)
{
    {
        dtk::d_uchar uc;

        QVERIFY( uc.value() == 0);
        QVERIFY( uc.min()   == 0);
        QVERIFY( uc.max()   == 255);
    }

    {
        dtk::d_char c;

        QVERIFY( c.value() == 0);
        QVERIFY( c.min()   == -128);
        QVERIFY( c.max()   == +127);
    }

    {
        dtk::d_string ds;

        QVERIFY( ds.value() == QString());
        QCOMPARE( ds.documentation(), QString());
    }

    {
        QString doc = QString("Description of the parameter....");
        dtk::d_string ds("string_ds", "blabla", doc);

        QCOMPARE( ds.documentation(), doc);
    }

    {
        QString doc = QString("Cast float to string ?");
        dtk::d_string ds("string_ds", "", doc);

        dtk::d_real r = 3.14;
        ds.setValue(r.variant());

        //QVERIFY( ds.value() == "3.14" ); /// really ????
        QVERIFY( ds.value() == "" );
    }

    {
        //
        // example on how to use dtkCoreParameterSimple
        //

        // see also the necessary declaration at the beginning of the file
        // Q_DECLARE_METATYPE(dtkCoreParameterSimple<std::string>)
        // qDebug implementation
        dtkCoreParameterSimple<std::string> my_string_1;

        QVERIFY( my_string_1.value() == "" );

        QString      info  = QString("what's up doc ?");
        std::string  value = "toto le heros";
        dtkCoreParameterSimple<std::string> my_string_2("my_string_2", value, info);

        QVERIFY( my_string_2.value() == value);
        QVERIFY( my_string_2.documentation() == info);

        qDebug() << "String:" << my_string_2;
    }

}

void dtkCoreParameterTestCase::testCreation(void)
{
    dtk::d_real source("intensity", 3.14159, -1, 4, "Intensity of the light");

    QVariantHash map;
    map["type"] = QMetaType::typeName(qMetaTypeId<dtk::d_real>());
    map["label"] = source.label();
    map["doc"] = source.documentation();
    map["value"] = source.value();
    map["min"] = source.min();
    map["max"] = source.max();

    auto *target = dtkCoreParameter::create(map);

    QVERIFY(target);
    QCOMPARE(target->label(), source.label());
    QCOMPARE(target->documentation(), source.documentation());

    dtk::d_real& target_real = dynamic_cast<dtk::d_real&>(*target);

    QVERIFY(&target_real);
    QCOMPARE((double)source, (double)(target_real));
    QCOMPARE(source.min(), target_real.min());
    QCOMPARE(source.max(), target_real.max());
    QCOMPARE(source.decimals(), target_real.decimals());
}

void dtkCoreParameterTestCase::testRange(void)
{
    dtk::d_range_uint::range values_ui = {0, 255};
    dtk::d_range_uint range_ui = dtk::d_range_uint( values_ui );

    dtk::d_range_int::range values_i = {-10, 10};
    dtk::d_range_int range_i = dtk::d_range_int( values_i );

    auto minimum = range_i.min();
    auto maximum = range_i.max();
    dtk::d_range_int::range bounds = range_i.bounds();
    dtk::d_range_int::range values = range_i.value();

    QCOMPARE(values[0], -10);
    QCOMPARE(values[1],  10);
    QCOMPARE(bounds[0], std::numeric_limits<qlonglong>::lowest());
    QCOMPARE(bounds[1], std::numeric_limits<qlonglong>::max());

    dtk::d_range_uchar::range values_uc = {0, 255};
    dtk::d_range_uchar range_uc = dtk::d_range_uchar( values_uc );

    dtk::d_range_char::range values_c = { 'a', 'z'};
    dtk::d_range_char range_c = dtk::d_range_char( values_c );

    dtk::d_range_real::range values_r1 = { -1.23456, 7.891011};
    dtk::d_range_real range_r1 = dtk::d_range_real( values_r1 );

    dtk::d_range_real::range values_r2 = { -1.23456, 7.891011};
    dtk::d_range_real range_r = dtk::d_range_real( QString("double range"), values_r2, -10.0, 10.0, QString("double range doc") );

    double a = 0.0;
    double b = 1.0;
    dtk::d_range_real range_r2 = dtk::d_range_real( { a, b} );
    a = 0.1;
    b = 0.2;
    range_r2.setValue( {a, b } );
}

void dtkCoreParameterTestCase::testFile(void)
{
    dtk::d_path source("file", "/pim/pam/poum/pipo.jpg", {"*.jpg", "*.png"},  "File parameter example");

    QVariantHash map;
    map["type"] = QMetaType::typeName(qMetaTypeId<dtk::d_path>());
    map["label"] = source.label();
    map["doc"] = source.documentation();
    map["path"] = source.path();
    map["filters"] = source.filters();

    auto *target = dtkCoreParameter::create(map);

    QVERIFY(target);
    QCOMPARE(target->label(), source.label());
    QCOMPARE(target->documentation(), source.documentation());

    dtk::d_path& target_file = dynamic_cast<dtk::d_path&>(*target);

    QVERIFY(&target_file);
    QCOMPARE(source.path(), target_file.path());
    QCOMPARE(source.dirName(), target_file.dirName());
    QCOMPARE(source.baseName(), target_file.baseName());
    QCOMPARE(source.filters(), target_file.filters());

    qDebug() << target_file;

    QByteArray data;
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out << source;
    }

    dtk::d_path destination;
    dtk::d_string psi;
    {
        QDataStream in(data);
        in >> destination;
    }

    QCOMPARE(source.path(), destination.path());
    QCOMPARE(source.dirName(), destination.dirName());
    QCOMPARE(source.baseName(), destination.baseName());
    QCOMPARE(source.filters(), destination.filters());
}

void dtkCoreParameterTestCase::testReadParameters(void)
{
    QString json_file(QFINDTESTDATA("../resources/parameters_def.json"));
    QString json_bad_file(QFINDTESTDATA("../resources/parameters_baddef.json"));

    {
        auto res = dtk::core::readParameters(json_file);
        QCOMPARE(res.count() , 6);

        QCOMPARE(res["hyp"]->label() , QString("Porosity Model"));
        QCOMPARE(dtk::d_int(res["hyp"]->variant()).value(), 2);

        QCOMPARE(res["dif"]->documentation() , QString("diffusion Flag"));
        QCOMPARE(dtk::d_bool(res["dif"]->variant()).value() , false);
        QCOMPARE(dtk::d_real(res["toto"]->variant()).value() , 3.1415);
    }

    {
        auto resbad = dtk::core::readParameters(json_bad_file);
        QCOMPARE(resbad.count() , 0);
    }
}

void dtkCoreParameterTestCase::testToVariantHash(void)
{
    dtk::d_real source("intensity", 3.14159, -1, 4, "Intensity of the light");

    auto *target = dtkCoreParameter::create(source.toVariantHash());

    QVERIFY(target);
    QCOMPARE(target->label(), source.label());
    QCOMPARE(target->documentation(), source.documentation());

    dtk::d_real& target_real = dynamic_cast<dtk::d_real&>(*target);

    QVERIFY(&target_real);
    QCOMPARE((double)source, (double)(target_real));
    QCOMPARE(source.min(), target_real.min());
    QCOMPARE(source.max(), target_real.max());
    QCOMPARE(source.decimals(), target_real.decimals());
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
