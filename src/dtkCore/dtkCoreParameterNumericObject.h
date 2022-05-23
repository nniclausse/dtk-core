// dtkCoreParameterNumericObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterNumeric.h"

class DTKCORE_EXPORT dtkCoreParameterNumericRealObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value    WRITE setValue    NOTIFY valueChanged)
    Q_PROPERTY(double max   READ max      WRITE setMax      NOTIFY maxChanged)
    Q_PROPERTY(double min   READ min      WRITE setMin      NOTIFY minChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)

public:
     dtkCoreParameterNumericRealObject(dtkCoreParameterNumeric<double> *);
    ~dtkCoreParameterNumericRealObject(void);

    void setValue(double);
    double value(void) const;

    void setMax(double);
    double max(void) const;

    void setMin(double);
    double min(void) const;

    void setDecimals(int);
    int decimals(void) const;

signals:
    void valueChanged(double);
    void maxChanged(double);
    void minChanged(double);
    void decimalsChanged(int);

public:
    dtkCoreParameterNumeric<double> *parameter(void) override;

private:
    dtkCoreParameterNumeric<double> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericIntObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qlonglong max   READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(qlonglong min   READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterNumericIntObject(dtkCoreParameterNumeric<qlonglong> *);
    ~dtkCoreParameterNumericIntObject(void);

    void setValue(qlonglong);
    qlonglong value(void) const;

    void setMax(qlonglong);
    qlonglong max(void) const;

    void setMin(qlonglong);
    qlonglong min(void) const;

signals:
    void valueChanged(qlonglong);
    void maxChanged(qlonglong);
    void minChanged(qlonglong);

public:
    dtkCoreParameterNumeric<qlonglong> *parameter(void) override;

private:
    dtkCoreParameterNumeric<qlonglong> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericUintObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(qulonglong value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qulonglong max   READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(qulonglong min   READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterNumericUintObject(dtkCoreParameterNumeric<qulonglong> *);
    ~dtkCoreParameterNumericUintObject(void);

    void setValue(qulonglong);
    qulonglong value(void) const;

    void setMax(qulonglong);
    qulonglong max(void) const;

    void setMin(qulonglong);
    qulonglong min(void) const;

signals:
    void valueChanged(qulonglong);
    void maxChanged(qulonglong);
    void minChanged(qulonglong);

public:
    dtkCoreParameterNumeric<qulonglong> *parameter(void) override;

private:
    dtkCoreParameterNumeric<qulonglong> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericCharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(char value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(char max   READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(char min   READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterNumericCharObject(dtkCoreParameterNumeric<char> *);
    ~dtkCoreParameterNumericCharObject(void);

    void setValue(char);
    char value(void) const;

    void setMax(char);
    char max(void) const;

    void setMin(char);
    char min(void) const;

signals:
    void valueChanged(char);
    void maxChanged(char);
    void minChanged(char);

public:
    dtkCoreParameterNumeric<char> *parameter(void) override;

private:
    dtkCoreParameterNumeric<char> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericUcharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(uchar value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(uchar max   READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(uchar min   READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterNumericUcharObject(dtkCoreParameterNumeric<uchar> *);
    ~dtkCoreParameterNumericUcharObject(void);

    void setValue(uchar);
    uchar value(void) const;

    void setMax(uchar);
    uchar max(void) const;

    void setMin(uchar);
    uchar min(void) const;

signals:
    void valueChanged(uchar);
    void maxChanged(uchar);
    void minChanged(uchar);

public:
    dtkCoreParameterNumeric<uchar> *parameter(void) override;

private:
    dtkCoreParameterNumeric<uchar> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericBoolObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(bool value READ value WRITE setValue NOTIFY valueChanged)

public:
     dtkCoreParameterNumericBoolObject(dtkCoreParameterNumeric<bool> *);
    ~dtkCoreParameterNumericBoolObject(void);

    void setValue(bool);
    bool value(void) const;

signals:
    void valueChanged(bool);

public:
    dtkCoreParameterNumeric<bool> *parameter(void) override;

private:
    dtkCoreParameterNumeric<bool> *m_param = nullptr;
};

//

template <typename T = void> class dtkCoreParameterNumericObject : public dtkCoreParameterObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<T> *p) : dtkCoreParameterObject(p) {}
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMin(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMax(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyDecimals(int) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class dtkCoreParameterNumericObject<double> : public dtkCoreParameterNumericRealObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<double> *p) : dtkCoreParameterNumericRealObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(double t) { emit valueChanged(t); }
    void notifyMin(double m) { emit minChanged(m); }
    void notifyMax(double m) { emit maxChanged(m); }
    void notifyDecimals(int d) { emit decimalsChanged(d); }
};

template <> class dtkCoreParameterNumericObject<qlonglong> : public dtkCoreParameterNumericIntObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<qlonglong> *p) : dtkCoreParameterNumericIntObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(qlonglong t) { emit valueChanged(t); }
    void notifyMin(qlonglong m) { emit minChanged(m); }
    void notifyMax(qlonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterNumericObject<qulonglong> : public dtkCoreParameterNumericUintObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<qulonglong> *p) : dtkCoreParameterNumericUintObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(qulonglong t) { emit valueChanged(t); }
    void notifyMin(qulonglong m) { emit minChanged(m); }
    void notifyMax(qulonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterNumericObject<char> : public dtkCoreParameterNumericCharObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<char> *p) : dtkCoreParameterNumericCharObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(char t) { emit valueChanged(t); }
    void notifyMin(char m) { emit minChanged(m); }
    void notifyMax(char m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterNumericObject<uchar> : public dtkCoreParameterNumericUcharObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<uchar> *p) : dtkCoreParameterNumericUcharObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(uchar t) { emit valueChanged(t); }
    void notifyMin(uchar m) { emit minChanged(m); }
    void notifyMax(uchar m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterNumericObject<bool> : public dtkCoreParameterNumericBoolObject
{
public:
     dtkCoreParameterNumericObject(dtkCoreParameterNumeric<bool> *p) : dtkCoreParameterNumericBoolObject(p) {};
    ~dtkCoreParameterNumericObject(void) = default;

    void notifyValue(bool t) { emit valueChanged(t); }
    void notifyMin(bool) {}
    void notifyMax(bool) {}
    void notifyDecimals(int) {}
};

//
// dtkCoreParameterNumericObject.h ends here
