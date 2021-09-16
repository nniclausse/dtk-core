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

dtkCoreParameter *dtkCoreParameterObject::parameter(void)
{
    return m_parameter;
}

void dtkCoreParameterObject::notifyLabel(const QString& l)
{
    emit labelChanged(l);
}

void dtkCoreParameterObject::notifyDoc(const QString& d)
{
    emit docChanged(d);
}


//
// dtkCoreParameterObject.cpp ends here
