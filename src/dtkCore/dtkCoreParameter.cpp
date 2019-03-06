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

#include "dtkCoreParameter.h"

dtkCoreAbstractParameter::dtkCoreAbstractParameter(const QString& name, const QString& doc) : m_name(name), m_doc(doc)
{

}

void dtkCoreAbstractParameter::setName(const QString& name)
{
    this->m_name = name;
}

QString dtkCoreAbstractParameter::name(void) const
{
    return this->m_name;
}

void dtkCoreAbstractParameter::setDocumentation(const QString& doc)
{
    this->m_doc = doc;
}

QString dtkCoreAbstractParameter::documentation(void) const
{
    return this->m_doc;
}

void dtkCoreAbstractParameter::emitValueChanged(void)
{
    emit this->valueChanged(this->variant());
}

//
// dtkCoreParameter.cpp ends here
