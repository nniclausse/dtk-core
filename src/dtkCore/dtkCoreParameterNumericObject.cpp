// dtkCoreParameterNumericObject.cpp
//

#include "dtkCoreParameterNumericObject.h"

dtkCoreParameterNumericRealObject::dtkCoreParameterNumericRealObject(dtkCoreParameterNumeric<double> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericRealObject::~dtkCoreParameterNumericRealObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericRealObject::setValue(double v)
{
    m_param->setValue(v);
}

double dtkCoreParameterNumericRealObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterNumericRealObject::setMax(double m)
{
    m_param->setMax(m);
}

double dtkCoreParameterNumericRealObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterNumericRealObject::setMin(double m)
{
    m_param->setMin(m);
}

double dtkCoreParameterNumericRealObject::min(void) const
{
    return m_param->min();
}

void dtkCoreParameterNumericRealObject::setDecimals(int d)
{
    m_param->setDecimals(d);
}

int dtkCoreParameterNumericRealObject::decimals(void) const
{
    return m_param->decimals();
}

dtkCoreParameterNumeric<double> *dtkCoreParameterNumericRealObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterNumericIntObject::dtkCoreParameterNumericIntObject(dtkCoreParameterNumeric<qlonglong> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericIntObject::~dtkCoreParameterNumericIntObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericIntObject::setValue(qlonglong v)
{
    m_param->setValue(v);
}

qlonglong dtkCoreParameterNumericIntObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterNumericIntObject::setMax(qlonglong m)
{
    m_param->setMax(m);
}

qlonglong dtkCoreParameterNumericIntObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterNumericIntObject::setMin(qlonglong m)
{
    m_param->setMin(m);
}

qlonglong dtkCoreParameterNumericIntObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterNumeric<qlonglong> *dtkCoreParameterNumericIntObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterNumericUintObject::dtkCoreParameterNumericUintObject(dtkCoreParameterNumeric<qulonglong> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericUintObject::~dtkCoreParameterNumericUintObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericUintObject::setValue(qulonglong v)
{
    m_param->setValue(v);
}

qulonglong dtkCoreParameterNumericUintObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterNumericUintObject::setMax(qulonglong m)
{
    m_param->setMax(m);
}

qulonglong dtkCoreParameterNumericUintObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterNumericUintObject::setMin(qulonglong m)
{
    m_param->setMin(m);
}

qulonglong dtkCoreParameterNumericUintObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterNumeric<qulonglong> *dtkCoreParameterNumericUintObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterNumericCharObject::dtkCoreParameterNumericCharObject(dtkCoreParameterNumeric<char> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericCharObject::~dtkCoreParameterNumericCharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericCharObject::setValue(char v)
{
    m_param->setValue(v);
}

char dtkCoreParameterNumericCharObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterNumericCharObject::setMax(char m)
{
    m_param->setMax(m);
}

char dtkCoreParameterNumericCharObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterNumericCharObject::setMin(char m)
{
    m_param->setMin(m);
}

char dtkCoreParameterNumericCharObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterNumeric<char> *dtkCoreParameterNumericCharObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterNumericUcharObject::dtkCoreParameterNumericUcharObject(dtkCoreParameterNumeric<uchar> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericUcharObject::~dtkCoreParameterNumericUcharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericUcharObject::setValue(uchar v)
{
    m_param->setValue(v);
}

uchar dtkCoreParameterNumericUcharObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterNumericUcharObject::setMax(uchar m)
{
    m_param->setMax(m);
}

uchar dtkCoreParameterNumericUcharObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterNumericUcharObject::setMin(uchar m)
{
    m_param->setMin(m);
}

uchar dtkCoreParameterNumericUcharObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterNumeric<uchar> *dtkCoreParameterNumericUcharObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterNumericBoolObject::dtkCoreParameterNumericBoolObject(dtkCoreParameterNumeric<bool> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterNumericBoolObject::~dtkCoreParameterNumericBoolObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterNumericBoolObject::setValue(bool v)
{
    m_param->setValue(v);
}

bool dtkCoreParameterNumericBoolObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterNumeric<bool> *dtkCoreParameterNumericBoolObject::parameter(void) const
{
    return m_param;
}

//
// dtkCoreParameterNumericObject.cpp ends here
