// dtkCoreParameterInListStringListObject.cpp
//

#include "dtkCoreParameterInListStringListObject.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterInListStringListObject implementation
// ///////////////////////////////////////////////////////////////////


dtkCoreParameterInListStringListObject::dtkCoreParameterInListStringListObject(dtkCoreParameterInListStringList *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterInListStringListObject::~dtkCoreParameterInListStringListObject(void)
{
    m_param = nullptr;
}

QStringList dtkCoreParameterInListStringListObject::value(void) const
{
    return m_param->value();
}

void dtkCoreParameterInListStringListObject::setValue(const QStringList& v)
{
    m_param->setValue(v);
}

QStringList dtkCoreParameterInListStringListObject::list(void) const
{
    m_param->values();
}

void dtkCoreParameterInListStringListObject::setList(const QStringList& l)
{
    m_param->setValues(l);
}

int dtkCoreParameterInListStringListObject::size(void) const
{
    return m_param->size();
}

void dtkCoreParameterInListStringListObject::notifyValue(const QStringList& v)
{
    emit valueChanged(v);
}

void dtkCoreParameterInListStringListObject::notifyList(const QStringList& l)
{
    emit listChanged(l);
}

dtkCoreParameterInListStringList *dtkCoreParameterInListStringListObject::parameter(void)
{
    return m_param;
}

//
// dtkCoreParameterInListStringListObject.h ends here
