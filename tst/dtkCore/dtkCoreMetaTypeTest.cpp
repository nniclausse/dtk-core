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

#include "dtkCoreMetaTypeTest.h"

#include <dtkCoreTest>

#include <dtkCore/dtkCoreMetaType>
#include <dtkCore/dtkCoreMetaContainerSequential>

// ///////////////////////////////////////////////////////////////////
// No Copyable Data concrete classes
// ///////////////////////////////////////////////////////////////////

class NoCopyableData
{
public:
             NoCopyableData(void) = default;
             NoCopyableData(const NoCopyableData&) = delete;
             NoCopyableData(const int& id, const QString& name) : m_id(id), m_name(name) {}
    virtual ~NoCopyableData(void) = default;

public:
    NoCopyableData& operator = (const NoCopyableData&) = delete;

    bool operator == (const NoCopyableData& o) const {
        if (m_id != o.m_id || m_name != o.m_name) return false;
        return true;
    }

public:
    void setId(const int& id) { m_id = id; }
    void setName(const QString& name) { m_name = name; }

    int id(void) const { return m_id; }
    QString name(void) const { return m_name; }

private:
    int m_id = -1;
    QString m_name = QString("No Name");
};

Q_DECLARE_METATYPE(NoCopyableData *);

QDebug operator << (QDebug dbg, NoCopyableData *data)
{
    dbg.nospace() << "NoCopyableData(" << data->id() << ", " << data->name() << ")"; return dbg.space();
}

// ///////////////////////////////////////////////////////////////////

class DeriveNoCopyableData : public NoCopyableData
{
public:
     DeriveNoCopyableData(void) = default;
     DeriveNoCopyableData(const DeriveNoCopyableData& o) = delete;
     DeriveNoCopyableData(const int& id, const QString& name, double value = 0) : NoCopyableData(id, name), m_value(value) {}
    ~DeriveNoCopyableData(void) = default;

public:
    DeriveNoCopyableData& operator = (const DeriveNoCopyableData&) = delete;
    bool operator == (const DeriveNoCopyableData& o) const {
        if (m_value != o.m_value) return false;
        return this->NoCopyableData::operator==(o);
    }

public:
    void setValue(double value) { m_value = value; }

    double value(void) const { return m_value; }

private:
    double m_value = -666;
};

Q_DECLARE_METATYPE(DeriveNoCopyableData *);

// ///////////////////////////////////////////////////////////////////
// Copyable Data concrete class
// ///////////////////////////////////////////////////////////////////

class Data
{
public:
    Data(void) = default;
    Data(const int& id, const QString& name) : m_id(id), m_name(name) {}
    Data(const Data& o) : m_id(o.m_id), m_name(o.m_name) {}
    virtual ~Data(void) = default;

public:
    Data& operator = (const Data& o) {
        m_id = o.m_id;
        m_name = o.m_name;
        return (*this);
    }
    bool operator == (const Data& o) const {
        if (m_id != o.m_id || m_name != o.m_name) return false;
        return true;
    }

public:
    void setId(const int& id) { m_id = id; }
    void setName(const QString& name) { m_name = name; }

    int id(void) const { return m_id; }
    QString name(void) const { return m_name; }

private:
    int m_id = -1;
    QString m_name = QString("No name");
};

Q_DECLARE_METATYPE(Data);
Q_DECLARE_METATYPE(Data *);

QDebug operator << (QDebug dbg, const Data& data)
{
    dbg.nospace() << "Data(" << data.id() << ", " << data.name() << ")"; return dbg.space();
}

QDebug operator << (QDebug dbg, Data *data)
{
    dbg.nospace() << "Data(" << data->id() << ", " << data->name() << ")"; return dbg.space();
}

// ///////////////////////////////////////////////////////////////////

class DeriveData : public Data
{
public:
    DeriveData(void) = default;
    DeriveData(const int& id, const QString& name, double value = 0) : Data(id, name), m_value(value) {}
    DeriveData(const DeriveData& o) : Data(o), m_value(o.m_value) {}

public:
    bool operator == (const DeriveData& o) const {
        if (m_value != o.m_value) return false;
        return this->Data::operator==(o);
    }

public:
    void setValue(double value) { m_value = value; }

    double value(void) const { return m_value; }

private:
    double m_value = -777;
};

Q_DECLARE_METATYPE(DeriveData);
Q_DECLARE_METATYPE(DeriveData *);

// ///////////////////////////////////////////////////////////////////
// Abstract class
// ///////////////////////////////////////////////////////////////////

class MyAbstract
{
public:
             MyAbstract(void) = default;
    virtual ~MyAbstract(void) = default;

public:
    MyAbstract& operator = (const MyAbstract& o) {
        setId(o.id());
        setName(o.name());
        return (*this);
    }
    bool operator == (const MyAbstract& o) const {
        if (id() != o.id() || name() != o.name()) return false;
        return true;
    }

public:
    virtual void   setId(const int& id) = 0;
    virtual void setName(const QString& name) = 0;

    virtual int       id(void) const = 0;
    virtual QString name(void) const = 0;
};

QDebug operator << (QDebug dbg, MyAbstract *o)
{
    dbg.nospace() << "MyAbstract(" << o->id() << ", " << o->name() << ")"; return dbg.space();
}

Q_DECLARE_METATYPE(MyAbstract *);

// ///////////////////////////////////////////////////////////////////

class DeriveMyAbstract : public MyAbstract
{
public:
     DeriveMyAbstract(void) = default;
     DeriveMyAbstract(const DeriveMyAbstract& other) : MyAbstract(), m_id(other.m_id), m_name(other.m_name) {}
    ~DeriveMyAbstract(void) = default;

public:
    void setId(const int& id) override { m_id = id; }
    void setName(const QString& name) override { m_name = name; }

public:
    int id(void) const override { return m_id; }
    QString name(void) const override { return m_name; }

private:
    int m_id = -1;
    QString m_name = QString("No name");
};

Q_DECLARE_METATYPE(DeriveMyAbstract);
Q_DECLARE_METATYPE(DeriveMyAbstract *);

// ///////////////////////////////////////////////////////////////////
// Abstract QObject class
// ///////////////////////////////////////////////////////////////////

class VirtualObject : public QObject
{
    Q_OBJECT

public:
     VirtualObject(void) = default;
    ~VirtualObject(void) = default;

public:
    VirtualObject& operator = (const VirtualObject& o) {
        setId(o.id());
        setName(o.name());
        return (*this);
    }
    bool operator == (const VirtualObject& o) const {
        if (id() != o.id() || name() != o.name()) return false;
        return true;
    }

public:
    virtual void   setId(const int& id) = 0;
    virtual void setName(const QString& name) = 0;

    virtual int       id(void) const = 0;
    virtual QString name(void) const = 0;
};

QDebug operator << (QDebug dbg, VirtualObject *o)
{
    dbg.nospace() << "VirtualObject(" << o->id() << ", " << o->name() << ")"; return dbg.space();
}

Q_DECLARE_METATYPE(VirtualObject *);

// ///////////////////////////////////////////////////////////////////

class VirtualObject2 : public VirtualObject
{
    Q_OBJECT

public:
     VirtualObject2(void) = default;
    ~VirtualObject2(void) = default;

public:
    virtual QString identifier(void) { return "VirtualObject2"; }
};

Q_DECLARE_METATYPE(VirtualObject2 *);

// ///////////////////////////////////////////////////////////////////

class DeriveVirtualObject : public VirtualObject2
{
    Q_OBJECT

public:
     DeriveVirtualObject(void) = default;
     DeriveVirtualObject(const DeriveVirtualObject& other) : VirtualObject2(), m_id(other.m_id), m_name(other.m_name) {}
    ~DeriveVirtualObject(void) = default;

public:
    void setId(const int& id) { m_id = id; }
    void setName(const QString& name) { m_name = name; }

    int id(void) const { return m_id; }
    QString name(void) const { return m_name; }

private:
    int m_id = -1;
    QString m_name = QString("No name");
};

Q_DECLARE_METATYPE(DeriveVirtualObject);
Q_DECLARE_METATYPE(DeriveVirtualObject *);

// ///////////////////////////////////////////////////////////////////

class DeriveTwiceVirtualObject : public DeriveVirtualObject
{
    Q_OBJECT

public:
     DeriveTwiceVirtualObject(void) = default;
     DeriveTwiceVirtualObject(const DeriveVirtualObject& other) : DeriveVirtualObject(other) {}
    ~DeriveTwiceVirtualObject(void) = default;
};

Q_DECLARE_METATYPE(DeriveTwiceVirtualObject);
Q_DECLARE_METATYPE(DeriveTwiceVirtualObject *);

// ///////////////////////////////////////////////////////////////////
// Classes to test is_qobject trait
// ///////////////////////////////////////////////////////////////////

class Derived : public QObject
{
public:
};

class NoDerived
{
};

class DerivedTwice : public Derived
{
};

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaTypeTestCasePrivate declaration
// ///////////////////////////////////////////////////////////////////

class dtkCoreMetaTypeTestCasePrivate
{
public:
    int count = 0;

    NoCopyableData *no_copyable_data;
    DeriveNoCopyableData *derive_no_copyable_data;

    Data *data;
    DeriveData *derive_data;

    MyAbstract *abstract;

    VirtualObject *virtual_object;
    VirtualObject2 *virtual_object2;
};

// ///////////////////////////////////////////////////////////////////

dtkCoreMetaTypeTestCase::dtkCoreMetaTypeTestCase(void) : d(new dtkCoreMetaTypeTestCasePrivate)
{
    QMetaType::registerDebugStreamOperator<NoCopyableData *>();

    QMetaType::registerDebugStreamOperator<Data>();

    QMetaType::registerDebugStreamOperator<MyAbstract *>();

    qRegisterMetaType<DeriveVirtualObject>();
    qRegisterMetaType<DeriveVirtualObject *>();
    qRegisterMetaType<DeriveTwiceVirtualObject>();
    qRegisterMetaType<DeriveTwiceVirtualObject *>();

    QMetaType::registerDebugStreamOperator<VirtualObject *>();
}

dtkCoreMetaTypeTestCase::~dtkCoreMetaTypeTestCase(void)
{
    delete d;
}

void dtkCoreMetaTypeTestCase::initTestCase(void)
{

}

void dtkCoreMetaTypeTestCase::init(void)
{
    d->no_copyable_data = new NoCopyableData(d->count ++, "PNoCopyableData");
    d->derive_no_copyable_data = new DeriveNoCopyableData(d->count++, "PDeriveNoCopyableData", 5573.);

    d->data = new Data(d->count ++, "PData");
    d->derive_data = new DeriveData(d->count++, "PDeriveData", 0.879);

    d->abstract = new DeriveMyAbstract();
    d->abstract->setName("PDeriveMyAbstract");
    d->abstract->setId(d->count++);

    d->virtual_object = new DeriveVirtualObject();
    d->virtual_object->setName("PDeriveVirtualObject");
    d->virtual_object->setId(d->count++);

    d->virtual_object2 = new DeriveVirtualObject();
    d->virtual_object2->setName("PDeriveVirtualObject2");
    d->virtual_object2->setId(d->count++);
}

void dtkCoreMetaTypeTestCase::testIsQObject(void)
{
    QVERIFY(dtk::is_qobject<QObject>::value);
    QVERIFY(dtk::is_qobject<QObject&>::value);
    QVERIFY(dtk::is_qobject<const QObject&>::value);
    QVERIFY(dtk::is_qobject<QObject&&>::value);
    QVERIFY(dtk::is_qobject<QObject *>::value);
    QVERIFY(dtk::is_qobject<const QObject *>::value);
    QVERIFY(dtk::is_qobject<QObject *&>::value);
    QVERIFY(dtk::is_qobject<const QObject *&>::value);
    QVERIFY(dtk::is_qobject<volatile QObject>::value);
    QVERIFY(dtk::is_qobject<const volatile QObject>::value);
    QVERIFY(dtk::is_qobject<volatile QObject *>::value);
    QVERIFY(dtk::is_qobject<const volatile QObject *>::value);

    QVERIFY(dtk::is_qobject<Derived>::value);
    QVERIFY(dtk::is_qobject<Derived&>::value);
    QVERIFY(dtk::is_qobject<const Derived&>::value);
    QVERIFY(dtk::is_qobject<Derived&&>::value);
    QVERIFY(dtk::is_qobject<Derived *>::value);
    QVERIFY(dtk::is_qobject<const Derived *>::value);
    QVERIFY(dtk::is_qobject<Derived *&>::value);
    QVERIFY(dtk::is_qobject<const Derived *&>::value);
    QVERIFY(dtk::is_qobject<volatile Derived>::value);
    QVERIFY(dtk::is_qobject<const volatile Derived>::value);
    QVERIFY(dtk::is_qobject<volatile Derived *>::value);
    QVERIFY(dtk::is_qobject<const volatile Derived *>::value);

    QVERIFY(!dtk::is_qobject<NoDerived>::value);
    QVERIFY(!dtk::is_qobject<NoDerived&>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived&>::value);
    QVERIFY(!dtk::is_qobject<NoDerived&&>::value);
    QVERIFY(!dtk::is_qobject<NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<NoDerived *&>::value);
    QVERIFY(!dtk::is_qobject<const NoDerived *&>::value);
    QVERIFY(!dtk::is_qobject<volatile NoDerived>::value);
    QVERIFY(!dtk::is_qobject<const volatile NoDerived>::value);
    QVERIFY(!dtk::is_qobject<volatile NoDerived *>::value);
    QVERIFY(!dtk::is_qobject<const volatile NoDerived *>::value);

    QVERIFY(dtk::is_qobject<DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice&>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice&>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice&&>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<DerivedTwice *&>::value);
    QVERIFY(dtk::is_qobject<const DerivedTwice *&>::value);
    QVERIFY(dtk::is_qobject<volatile DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<const volatile DerivedTwice>::value);
    QVERIFY(dtk::is_qobject<volatile DerivedTwice *>::value);
    QVERIFY(dtk::is_qobject<const volatile DerivedTwice *>::value);
}

void dtkCoreMetaTypeTestCase::testCanConvert(void)
{
    // Non QObject No Copyable Data pointer
    QVERIFY(!dtk::canConvert<NoCopyableData *>(QList<int>({QMetaType::type("DeriveNoCopyableData*")})));

    QVERIFY(!dtk::canConvert<DeriveNoCopyableData *>(QList<int>({QMetaType::type("NoCopyableData*")})));
    QMetaType::registerConverter<DeriveNoCopyableData *, NoCopyableData *>();
    QVERIFY(dtk::canConvert<DeriveNoCopyableData *>(QList<int>({QMetaType::type("NoCopyableData*")})));


    // Non QObject Data pointer
    QVERIFY(!dtk::canConvert<Data *>(QList<int>({QMetaType::type("DeriveData*")})));

    QVERIFY(!dtk::canConvert<DeriveData *>(QList<int>({QMetaType::type("Data*")})));
    QMetaType::registerConverter<DeriveData *, Data *>();
    QVERIFY(dtk::canConvert<DeriveData *>(QList<int>({QMetaType::type("Data*")})));


    // Non QObject Abstract class
    QVERIFY(!dtk::canConvert<MyAbstract *>(QList<int>({QMetaType::type("DeriveMyAbstract*")})));

    QVERIFY(!dtk::canConvert<DeriveMyAbstract *>(QList<int>({QMetaType::type("MyAbstract*")})));
    QMetaType::registerConverter<DeriveMyAbstract *, MyAbstract *>();
    QVERIFY(dtk::canConvert<DeriveMyAbstract *>(QList<int>({QMetaType::type("MyAbstract*")})));


    // QObject Abstract class
    QVERIFY(dtk::canConvert<DeriveVirtualObject *>(QList<int>({QMetaType::type("VirtualObject*")})));

    QVERIFY(!dtk::canConvert<DeriveVirtualObject *>(QList<int>({QMetaType::type("VirtualObject2*")})));
    qRegisterMetaType<VirtualObject2 *>();
    QVERIFY(dtk::canConvert<DeriveVirtualObject *>(QList<int>({QMetaType::type("VirtualObject2*")})));

    QVERIFY(!dtk::canConvert<VirtualObject2 *>(QList<int>({QMetaType::type("VirtualObject *")})));
    QMetaType::registerConverter<VirtualObject2 *, VirtualObject *>();
    QVERIFY(dtk::canConvert<VirtualObject2 *>(QList<int>({QMetaType::type("VirtualObject*")})));

    qDebug() << std::is_abstract<VirtualObject2>::value;
    qDebug() << std::is_abstract<VirtualObject2 *>::value;
}

void dtkCoreMetaTypeTestCase::testVariantFromValue(void)
{
    // Non QObject No copyable Data pointer
    {
        NoCopyableData *d0 = d->no_copyable_data;
        QVariant v_d0 = dtk::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "NoCopyableData*");
        QCOMPARE(*(v_d0.value<NoCopyableData *>()), *d0);

        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        QVariant v_dd0 = dtk::variantFromValue(dd0);
        QVERIFY(v_dd0.isValid());
        QCOMPARE(v_dd0.typeName(), "DeriveNoCopyableData*");
        QCOMPARE(*(v_dd0.value<DeriveNoCopyableData *>()), *dd0);
        QVERIFY(v_dd0.canConvert(v_d0.userType()));

        NoCopyableData *d1 = dd0;
        QVariant v_d1 = dtk::variantFromValue(d1);
        QVERIFY(v_d1.isValid());
        QVERIFY(v_d1.userType() != v_dd0.userType());
        QCOMPARE(v_d1.typeName(), "NoCopyableData*");

        NoCopyableData *d2 = v_dd0.value<NoCopyableData *>();
        QCOMPARE(*d1, *d2);
    }

    // Non QObject Data
    {
        Data d0 = *d->data;
        QVariant v_d0 = dtk::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "Data");
        QCOMPARE(v_d0.value<Data>(), d0);
    }

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        QVariant v_d0 = dtk::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "Data*");
        QCOMPARE(*(v_d0.value<Data *>()), *d0);

        DeriveData *dd0 = d->derive_data;
        QVariant v_dd0 = dtk::variantFromValue(dd0);
        QVERIFY(v_dd0.isValid());
        QCOMPARE(v_dd0.typeName(), "DeriveData*");
        QCOMPARE(*(v_dd0.value<DeriveData *>()), *dd0);
        QVERIFY(v_dd0.canConvert(v_d0.userType()));

        Data *d1 = dd0;
        QVariant v_d1 = dtk::variantFromValue(d1);
        QVERIFY(v_d1.isValid());
        QVERIFY(v_d1.userType() != v_dd0.userType());
        QCOMPARE(v_d1.typeName(), "Data*");

        Data *d2 = v_dd0.value<Data *>();
        QCOMPARE(*d1, *d2);
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;

        QVariant v_a0 = dtk::variantFromValue(a0);
        QVERIFY(v_a0.isValid());
        QCOMPARE(v_a0.typeName(), "MyAbstract*");
        QCOMPARE(*(v_a0.value<MyAbstract *>()), *a0);

        DeriveMyAbstract *b0 = dynamic_cast<DeriveMyAbstract *>(a0);
        QVariant v_b0 = dtk::variantFromValue(b0);
        QVERIFY(v_b0.isValid());
        QCOMPARE(v_b0.typeName(), "DeriveMyAbstract*");
        QCOMPARE(*(v_b0.value<DeriveMyAbstract *>()), *b0);

        QVERIFY(v_b0.canConvert(v_a0.userType()));
        QVERIFY(v_b0.convert(v_a0.userType()));
    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;

        // As DeriveVirtualObject* type has been registered, the
        // created variant is of the lowest type even if it is created
        // from the abstract class.
        QVariant v_a0 = dtk::variantFromValue(a0);
        QVERIFY(v_a0.isValid());
        QCOMPARE(v_a0.typeName(), "DeriveVirtualObject*");
        QCOMPARE(*(v_a0.value<VirtualObject *>()), *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        QVariant vv_b1 = QVariant::fromValue(b1);
        QVERIFY(vv_b1.canConvert(qMetaTypeId<VirtualObject *>()));
        QVERIFY(vv_b1.convert(qMetaTypeId<VirtualObject *>()));
        QCOMPARE(*(vv_b1.value<VirtualObject *>()), *(dynamic_cast<VirtualObject *>(b1)));
    }

    // QObject Concrete class
    {
        DeriveTwiceVirtualObject b;
        const DeriveVirtualObject& a = b;

        QVariant v_a = dtk::variantFromValue(a);
        QVERIFY(v_a.isValid());
        QCOMPARE(v_a.typeName(), "DeriveTwiceVirtualObject");
        QCOMPARE(v_a.value<DeriveVirtualObject>(), a);
        QCOMPARE(v_a.value<DeriveTwiceVirtualObject>(), b);
    }
}

void dtkCoreMetaTypeTestCase::testClone(void)
{
    // Non QObject No Copyable Data pointer
    {
        // Cloning return nullptr;
        NoCopyableData *d0 = d->no_copyable_data;
        NoCopyableData *c0 = dtk::clone(d0);
        QVERIFY(!c0);

        // Cloning return nullptr;
        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        DeriveNoCopyableData *cc0 = dtk::clone(dd0);
        QVERIFY(!cc0);

        // Cloning return nullptr;
        NoCopyableData *d1 = dd0;
        NoCopyableData *c1 = dtk::clone(d1);
        QVERIFY(!c1);
    }

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        Data *c0 = dtk::clone(d0);
        QCOMPARE(*d0, *c0);

        DeriveData *dd0 = d->derive_data;
        DeriveData *cc0 = dtk::clone(dd0);
        QCOMPARE(*dd0, *cc0);

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        Data *c1 = dtk::clone(d1);
        // The resulting copy is not a DeriveData object.
        QVERIFY(!dynamic_cast<DeriveData *>(c1));
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;
        QVERIFY(dynamic_cast<DeriveMyAbstract *>(a0));

        // Here again slicing occurs
        MyAbstract *c0 = dtk::clone(a0);
        QVERIFY(!dynamic_cast<DeriveMyAbstract *>(c0));
    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        VirtualObject *c0 = dtk::clone(a0);
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c0));
        QCOMPARE(*c0, *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        VirtualObject2 *c1 = dtk::clone(b1);
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c1));
        QCOMPARE(*c1, *b1);
    }

}
void dtkCoreMetaTypeTestCase::testCopy(void)
{
    // Non QObject No Copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        // Cloning return nullptr;
        NoCopyableData *d0 = d->no_copyable_data;
        NoCopyableData *c0 = new NoCopyableData(-12, "dummy");
        dtk::copy(d0, c0);
        QCOMPARE(QString("dummy"), c0->name());
        delete c0;

        // Cloning return nullptr;
        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        DeriveNoCopyableData *cc0 = new DeriveNoCopyableData(-12, "dummy", 3.14159);
        dtk::copy(dd0, cc0);
        QCOMPARE(3.14159, cc0->value());
        delete cc0;

    }
#endif

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        Data *c0 = new Data();
        QVERIFY(dtk::copy(d0, c0));
        QCOMPARE(*d0, *c0);
        delete c0;

        DeriveData *dd0 = d->derive_data;
        DeriveData *cc0 = new DeriveData();
        dtk::copy(dd0, cc0);
        QCOMPARE(*dd0, *cc0);
        delete cc0;

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        Data *c1 = new DeriveData;
        dtk::copy(d1, c1);
        QVERIFY(!(*dd0 == *dynamic_cast<DeriveData *>(c1)));
        delete c1;
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;
        QVERIFY(dynamic_cast<DeriveMyAbstract *>(a0));

        // No slicing occurs since the Abstract class is copy
        // assignable at the top level and handles all the
        // members. But it is luck.
        MyAbstract *c0 = new DeriveMyAbstract;
        QVERIFY(dtk::copy(a0, c0));
        QCOMPARE(*a0, *c0);
        delete c0;
    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        VirtualObject *c0 = new DeriveVirtualObject;
        dtk::copy(a0, c0);
        QCOMPARE(*c0, *a0);
        delete c0;

        VirtualObject2 *b1 = d->virtual_object2;
        VirtualObject2 *c1 = new DeriveVirtualObject;
        dtk::copy(b1, c1);
        QCOMPARE(*c1, *b1);
        delete c1;
    }
}

void dtkCoreMetaTypeTestCase::testAssignments(void)
{
    {
        double lhs = 3.14159;
        double rhs = 10.5;
        double res = rhs;

        dtk::assign(lhs, rhs);
        QCOMPARE(res, lhs);
    }

    {
        double lhs = 3.14159;
        double rhs = 10.5;
        double res = lhs + rhs;

        dtk::addAssign(lhs, rhs);
        QCOMPARE(res, lhs);
    }

    {
        double lhs = 3.14159;
        double rhs = 10.5;
        double res = lhs - rhs;

        dtk::subAssign(lhs, rhs);
        QCOMPARE(res, lhs);
    }

    {
        double lhs = 3.14159;
        double rhs = 10.5;
        double res = lhs * rhs;

        dtk::mulAssign(lhs, rhs);
        QCOMPARE(res, lhs);
    }

    {
        double lhs = 3.14159;
        double rhs = 10.5;
        double res = lhs / rhs;

        dtk::divAssign(lhs, rhs);
        QCOMPARE(res, lhs);
    }
}

void dtkCoreMetaTypeTestCase::testCloneContent(void)
{
    // Non QObject Data pointer
    {
        int a = 67;
        QVariant v = dtk::variantFromValue(a);

        QVariant vv = dtk::cloneContent(v);

        QCOMPARE(vv.toInt(), v.toInt());
    }

    {
        // QObject *o = new QObject();
        // QVariant v = QVariant::fromValue(o);
        // qDebug() << v << QMetaType::TypeFlags(v.userType());

    }

    // Non QObject No copyable Data pointer
    {
        NoCopyableData *d0 = d->no_copyable_data;
        QVariant v = dtk::variantFromValue(d0);
        QVariant vv = dtk::cloneContent(v);
        NoCopyableData *c0 = vv.value<NoCopyableData *>();
        QVERIFY(!c0);

        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        v = dtk::variantFromValue(dd0);

        if (QMetaType::type("DeriveNoCopyableData*") == QMetaType::UnknownType)
            qRegisterMetaType<DeriveNoCopyableData *>();

        vv = dtk::cloneContent(v);
        DeriveNoCopyableData *cc0 = vv.value<DeriveNoCopyableData *>();
        QVERIFY(!cc0);
    }

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        QVariant v = dtk::variantFromValue(d0);
        QVariant vv = dtk::cloneContent(v);
        Data *c0 = vv.value<Data *>();
        QVERIFY(static_cast<void *>(d0) != static_cast<void *>(c0));
        QCOMPARE(*d0, *c0);

        DeriveData *dd0 = d->derive_data;
        v = dtk::variantFromValue(dd0);

        if (QMetaType::type("DeriveData") == QMetaType::UnknownType)
            qRegisterMetaType<DeriveData>();

        vv = dtk::cloneContent(v);
        DeriveData *cc0 = vv.value<DeriveData *>();
        QVERIFY(static_cast<void *>(dd0) != static_cast<void *>(cc0));
        QCOMPARE(*dd0, *cc0);

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        v = dtk::variantFromValue(d1);
        vv = dtk::cloneContent(v);
        Data *c1 = vv.value<Data *>();
        // The resulting copy is not a DeriveData object.
        QVERIFY(!dynamic_cast<DeriveData *>(c1));
    }

    // // Non QObject Abstract class
    // {
    //     MyAbstract *a0 = d->abstract;
    //     QVERIFY(dynamic_cast<DeriveMyAbstract*>(a0));

    //     // Here again slicing occurs
    //     QVariant v = dtk::variantFromValue(a0);
    //     QVariant vv = dtk::cloneContent(v);
    //     MyAbstract *c0 = vv.value<MyAbstract *>();
    //     QVERIFY(!dynamic_cast<DeriveMyAbstract*>(c0));
    // }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        QVariant v = dtk::variantFromValue(a0);
        QVariant vv = dtk::cloneContent(v);
        VirtualObject *c0 = vv.value<VirtualObject *>();
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c0));
        QCOMPARE(*c0, *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        v = dtk::variantFromValue(b1);
        vv = dtk::cloneContent(v);
        VirtualObject2 *c1 = vv.value<VirtualObject2 *>();
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c1));
        QCOMPARE(*c1, *b1);
    }
}

void dtkCoreMetaTypeTestCase::testCreateEmptyContainer(void)
{
    {
        QVector<double> vec(5, 3.14159);
        QVariant var = dtk::variantFromValue(vec);
        var.clear();
        var = dtk::variantFromValue(&vec);
        QVERIFY(var.canConvert<dtkCoreMetaContainerSequential>());

        QVariant res = dtk::createEmptyContainer(var);
        QVector<double> *v_res = res.value<QVector<double> *>();
        QVERIFY(v_res);
        QVERIFY(v_res->size() == 0);
        delete v_res;
    }

    {
        QList<double> list;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;

        QVariant var = dtk::variantFromValue(list);
        var.clear();
        var = dtk::variantFromValue(&list);
        QVERIFY(var.canConvert<dtkCoreMetaContainerSequential>());

        QVariant res = dtk::createEmptyContainer(var);
        QList<double> *l_res = res.value<QList<double> *>();
        QVERIFY(l_res);
        QVERIFY(l_res->size() == 0);
        delete l_res;
    }
}

void dtkCoreMetaTypeTestCase::testDestroyPointer(void)
{
    {
        QVector<double> *vec = nullptr;
        QVariant var = dtk::variantFromValue(vec);
        QVERIFY(var.canConvert<dtkCoreMetaContainerSequential>());
        QVERIFY(!dtk::destroyPointer(var));

        vec = new QVector<double>(5, 3.14159);
        var = dtk::variantFromValue(vec);
        QVERIFY(dtk::destroyPointer(var));
    }
}

void dtkCoreMetaTypeTestCase::cleanupTestCase(void)
{

}

void dtkCoreMetaTypeTestCase::cleanup(void)
{
    delete d->no_copyable_data;
    delete d->derive_no_copyable_data;

    delete d->data;
    delete d->derive_data;

    delete d->abstract;

    delete d->virtual_object;
    delete d->virtual_object2;
}

DTKCORETEST_MAIN_NOGUI(dtkCoreMetaTypeTest, dtkCoreMetaTypeTestCase);

#include "dtkCoreMetaTypeTest.moc"

//
// dtkCoreMetaTypeTest.cpp ends here
