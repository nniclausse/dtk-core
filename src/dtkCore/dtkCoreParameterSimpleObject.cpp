// dtkCoreParameterSimpleObject.cpp
//

#include "dtkCoreParameterSimpleObject.h"

dtkCoreParameterStringObject::dtkCoreParameterStringObject(dtkCoreParameterSimple<QString> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterStringObject::~dtkCoreParameterStringObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterStringObject::setValue(const QString& v)
{
    m_param->setValue(v);
}

QString dtkCoreParameterStringObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterSimple<QString> *dtkCoreParameterStringObject::parameter(void)
{
    return m_param;
}

//
// dtkCoreParameterStringObject.cpp ends here
