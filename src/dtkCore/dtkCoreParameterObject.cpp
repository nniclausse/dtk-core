// dtkCoreParameterObject.cpp
//

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameter.h"

dtkCoreParameterObject::dtkCoreParameterObject(dtkCoreParameter *p) : QObject(), m_parameter(p)
{
    Q_ASSERT(m_parameter);
}

dtkCoreParameterObject::~dtkCoreParameterObject(void)
{
    m_parameter = nullptr;
}

void dtkCoreParameterObject::setLabel(const QString& label)
{
    if (label != m_parameter->label()) {
        m_parameter->setLabel(label);
    }
}

QString dtkCoreParameterObject::label(void) const
{
    return m_parameter->label();
}

void dtkCoreParameterObject::setUnit(const QString& unit)
{
    if (unit != m_parameter->unit()) {
        m_parameter->setUnit(unit);
    }
}

QString dtkCoreParameterObject::unit(void) const
{
    return m_parameter->unit();
}

void dtkCoreParameterObject::setDoc(const QString& doc)
{
    if (m_parameter->documentation() != doc) {
        m_parameter->setDocumentation(doc);
    }
}

QString dtkCoreParameterObject::doc(void) const
{
    return m_parameter->documentation();
}

QString dtkCoreParameterObject::type(void) const
{
    return m_parameter->typeName();
}

dtkCoreParameter *dtkCoreParameterObject::parameter(void)
{
    return m_parameter;
}

void dtkCoreParameterObject::notifyLabel(const QString& l)
{
    emit labelChanged(l);
}

void dtkCoreParameterObject::notifyUnit(const QString& u)
{
    emit unitChanged(u);
}

void dtkCoreParameterObject::notifyDoc(const QString& d)
{
    emit docChanged(d);
}


//
// dtkCoreParameterObject.cpp ends here
