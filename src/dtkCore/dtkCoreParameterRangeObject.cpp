// dtkCoreParameterRangeObject.cpp
//

#include "dtkCoreParameterRangeObject.h"


dtkCoreParameterRangeRealObject::dtkCoreParameterRangeRealObject(dtkCoreParameterRange<double> *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterRangeRealObject::~dtkCoreParameterRangeRealObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterRangeRealObject::setRange(const std::array<double, 2>& r)
{
    m_param->setValue(r);
}

const std::array<double, 2>& dtkCoreParameterRangeRealObject::range(void) const
{
    return m_param->value();
}

void dtkCoreParameterRangeRealObject::setMax(double m)
{
    m_param->setMax(m);
}

double dtkCoreParameterRangeRealObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterRangeRealObject::setMin(double m)
{
    m_param->setMin(m);
}

double dtkCoreParameterRangeRealObject::min(void) const
{
    return m_param->min();
}

void dtkCoreParameterRangeRealObject::setDecimals(int d)
{
    m_param->setDecimals(d);
}

int dtkCoreParameterRangeRealObject::decimals(void) const
{
    return m_param->decimals();
}

dtkCoreParameterRange<double> *dtkCoreParameterRangeRealObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterRangeIntObject::dtkCoreParameterRangeIntObject(dtkCoreParameterRange<qlonglong> *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterRangeIntObject::~dtkCoreParameterRangeIntObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterRangeIntObject::setRange(const std::array<qlonglong, 2>& r)
{
    m_param->setValue(r);
}

const std::array<qlonglong, 2>& dtkCoreParameterRangeIntObject::range(void) const
{
    return m_param->value();
}

void dtkCoreParameterRangeIntObject::setMax(qlonglong m)
{
    m_param->setMax(m);
}

qlonglong dtkCoreParameterRangeIntObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterRangeIntObject::setMin(qlonglong m)
{
    m_param->setMin(m);
}

qlonglong dtkCoreParameterRangeIntObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterRange<qlonglong> *dtkCoreParameterRangeIntObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterRangeUintObject::dtkCoreParameterRangeUintObject(dtkCoreParameterRange<qulonglong> *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterRangeUintObject::~dtkCoreParameterRangeUintObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterRangeUintObject::setRange(const std::array<qulonglong, 2>& r)
{
    m_param->setValue(r);
}

const std::array<qulonglong, 2>& dtkCoreParameterRangeUintObject::range(void) const
{
    return m_param->value();
}

void dtkCoreParameterRangeUintObject::setMax(qulonglong m)
{
    m_param->setMax(m);
}

qulonglong dtkCoreParameterRangeUintObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterRangeUintObject::setMin(qulonglong m)
{
    m_param->setMin(m);
}

qulonglong dtkCoreParameterRangeUintObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterRange<qulonglong> *dtkCoreParameterRangeUintObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterRangeCharObject::dtkCoreParameterRangeCharObject(dtkCoreParameterRange<char> *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterRangeCharObject::~dtkCoreParameterRangeCharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterRangeCharObject::setRange(const std::array<char, 2>& r)
{
    m_param->setValue(r);
}

const std::array<char, 2>& dtkCoreParameterRangeCharObject::range(void) const
{
    return m_param->value();
}

void dtkCoreParameterRangeCharObject::setMax(char m)
{
    m_param->setMax(m);
}

char dtkCoreParameterRangeCharObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterRangeCharObject::setMin(char m)
{
    m_param->setMin(m);
}

char dtkCoreParameterRangeCharObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterRange<char> *dtkCoreParameterRangeCharObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterRangeUcharObject::dtkCoreParameterRangeUcharObject(dtkCoreParameterRange<uchar> *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterRangeUcharObject::~dtkCoreParameterRangeUcharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterRangeUcharObject::setRange(const std::array<uchar, 2>& r)
{
    m_param->setValue(r);
}

const std::array<uchar, 2>& dtkCoreParameterRangeUcharObject::range(void) const
{
    return m_param->value();
}

void dtkCoreParameterRangeUcharObject::setMax(uchar m)
{
    m_param->setMax(m);
}

uchar dtkCoreParameterRangeUcharObject::max(void) const
{
    return m_param->max();
}

void dtkCoreParameterRangeUcharObject::setMin(uchar m)
{
    m_param->setMin(m);
}

uchar dtkCoreParameterRangeUcharObject::min(void) const
{
    return m_param->min();
}

dtkCoreParameterRange<uchar> *dtkCoreParameterRangeUcharObject::parameter(void) const
{
    return m_param;
}


//
// dtkCoreParameterRangeObject ends here
