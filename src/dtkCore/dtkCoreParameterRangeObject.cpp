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

void dtkCoreParameterRangeRealObject::setRmax(double m)
{
    m_param->setValueMax(m);

}

double dtkCoreParameterRangeRealObject::rmax(void) const
{
    return m_param->value()[1];
}

void dtkCoreParameterRangeRealObject::setRmin(double m)
{
    m_param->setValueMin(m);
}

double dtkCoreParameterRangeRealObject::rmin(void) const
{
    return m_param->value()[0];
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

dtkCoreParameterRange<double> *dtkCoreParameterRangeRealObject::parameter(void)
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

void dtkCoreParameterRangeIntObject::setRmax(qlonglong m)
{
    m_param->setValueMax(m);
}

qlonglong dtkCoreParameterRangeIntObject::rmax(void) const
{
    return m_param->value()[1];
}

void dtkCoreParameterRangeIntObject::setRmin(qlonglong m)
{
    m_param->setValueMin(m);
}

qlonglong dtkCoreParameterRangeIntObject::rmin(void) const
{
    return m_param->value()[0];
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

dtkCoreParameterRange<qlonglong> *dtkCoreParameterRangeIntObject::parameter(void)
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

void dtkCoreParameterRangeUintObject::setRmax(qulonglong m)
{
    m_param->setValueMax(m);
}

qulonglong dtkCoreParameterRangeUintObject::rmax(void) const
{
    return m_param->value()[1];
}

void dtkCoreParameterRangeUintObject::setRmin(qulonglong m)
{
    m_param->setValueMin(m);
}

qulonglong dtkCoreParameterRangeUintObject::rmin(void) const
{
    return m_param->value()[0];
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

dtkCoreParameterRange<qulonglong> *dtkCoreParameterRangeUintObject::parameter(void)
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

void dtkCoreParameterRangeCharObject::setRmax(char m)
{
    m_param->setValueMax(m);
}

char dtkCoreParameterRangeCharObject::rmax(void) const
{
    return m_param->value()[1];
}

void dtkCoreParameterRangeCharObject::setRmin(char m)
{
    m_param->setValueMin(m);
}

char dtkCoreParameterRangeCharObject::rmin(void) const
{
    return m_param->value()[0];
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

dtkCoreParameterRange<char> *dtkCoreParameterRangeCharObject::parameter(void)
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

void dtkCoreParameterRangeUcharObject::setRmax(uchar m)
{
    m_param->setValueMax(m);
}

uchar dtkCoreParameterRangeUcharObject::rmax(void) const
{
    return m_param->value()[1];
}

void dtkCoreParameterRangeUcharObject::setRmin(uchar m)
{
    m_param->setValueMin(m);
}

uchar dtkCoreParameterRangeUcharObject::rmin(void) const
{
    return m_param->value()[0];
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

dtkCoreParameterRange<uchar> *dtkCoreParameterRangeUcharObject::parameter(void)
{
    return m_param;
}


//
// dtkCoreParameterRangeObject ends here
