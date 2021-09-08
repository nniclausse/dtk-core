// dtkCoreParameterNumericObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterNumeric.h"

class DTKCORE_EXPORT dtkCoreParameterNumericRealObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(double value    READ value    WRITE setValue    NOTIFY valueChanged)
    Q_PROPERTY(double max      READ max      WRITE setMax      NOTIFY maxChanged)
    Q_PROPERTY(double min      READ min      WRITE setMin      NOTIFY minChanged)
    Q_PROPERTY(double decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)

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
    dtkCoreParameterNumeric<double> *parameter(void) const override;

private:
    dtkCoreParameterNumeric<double> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterNumericIntegerObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(qlonglong max   READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(qlonglong min   READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterNumericIntegerObject(dtkCoreParameterNumeric<qlonglong> *);
    ~dtkCoreParameterNumericIntegerObject(void);

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
    dtkCoreParameterNumeric<qlonglong> *parameter(void) const override;

private:
    dtkCoreParameterNumeric<qlonglong> *m_param = nullptr;
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
    dtkCoreParameterNumeric<char> *parameter(void) const override;

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
    dtkCoreParameterNumeric<uchar> *parameter(void) const override;

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
    dtkCoreParameterNumeric<bool> *parameter(void) const override;

private:
    dtkCoreParameterNumeric<bool> *m_param = nullptr;
};

//
// dtkCoreParameterNumericObject.h ends here
