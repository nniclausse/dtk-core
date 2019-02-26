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

dtkCoreAbstractParameter::dtkCoreAbstractParameter(const QString& doc) : m_doc(doc)
{

}

dtkCoreAbstractParameter::dtkCoreAbstractParameter(const dtkCoreAbstractParameter& o) : m_doc(o.m_doc)
{

}

dtkCoreAbstractParameter::dtkCoreAbstractParameter(dtkCoreAbstractParameter&& o) : m_doc(std::move(o.m_doc))
{

}

dtkCoreAbstractParameter::~dtkCoreAbstractParameter(void)
{

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
