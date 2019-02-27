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

// strings

dtkCoreParameterString::dtkCoreParameterString(void)
{
    m_value = QString();
}

dtkCoreParameterString::dtkCoreParameterString(QString v, QString doc) : dtkCoreAbstractParameter(doc)
{
    m_value = v;
}

dtkCoreParameterString::~dtkCoreParameterString(void)
{
}

QString dtkCoreParameterString::value(void)
{
    return m_value;
}

void dtkCoreParameterString::setValue(const QVariant &v)
{
    m_value = v.toString();
}

void dtkCoreParameterString::setValue(QString v)
{
    if ( m_value != v) {
        m_value = v;
        emit valueChanged(this->variant());
    }
}

QVariant dtkCoreParameterString::variant(void) const
{
    return QVariant(m_value);
}

//
// dtkCoreParameter.cpp ends here
