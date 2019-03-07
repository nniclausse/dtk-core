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

dtkCoreAbstractParameter::dtkCoreAbstractParameter(const QString& label, const QString& doc) : m_label(label), m_doc(doc)
{

}

void dtkCoreAbstractParameter::setLabel(const QString& label)
{
    this->m_label = label;
}

QString dtkCoreAbstractParameter::label(void) const
{
    return this->m_label;
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
