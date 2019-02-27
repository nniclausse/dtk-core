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

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterString implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreParameterString::dtkCoreParameterString(const QString& s) : dtkCoreAbstractParameter(), m_value(s)
{

}

dtkCoreParameterString::dtkCoreParameterString(const QVariant& v) : dtkCoreAbstractParameter()
{
    if (v.canConvert<dtkCoreParameterString>()) {
        *this = v.value<dtkCoreParameterString>();

    } else {
        m_value = v.toString();
    }
}

dtkCoreParameterString::dtkCoreParameterString(const QString& s, const QString& doc) : dtkCoreAbstractParameter(doc), m_value(s)
{

}

dtkCoreParameterString::dtkCoreParameterString(const dtkCoreParameterString& o) : dtkCoreAbstractParameter(o.m_doc), m_value(o.m_value)
{

}

dtkCoreParameterString& dtkCoreParameterString::operator = (const QString& s)
{
    m_value = s;
    return *this;
}

dtkCoreParameterString& dtkCoreParameterString::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterString>()) {
        *this = v.value<dtkCoreParameterString>();

    } else if (v.canConvert<QString>()) {
        m_value = v.toString();
    }
    return *this;
}

dtkCoreParameterString& dtkCoreParameterString::operator = (const dtkCoreParameterString& o)
{
    if (this != &o) {
        m_value = o.m_value;
    }
    return *this;
}

dtkCoreParameterString::operator QString() const
{
    return m_value;
}

void dtkCoreParameterString::setValue(const QString& s)
{
    if (m_value != s) {
        m_value = s;
        emit valueChanged(this->variant());
    }
}

void dtkCoreParameterString::setValue(const QVariant &v)
{
    if (v.canConvert<dtkCoreParameterString>()) {
        *this = v.value<dtkCoreParameterString>();
        emit valueChanged(this->variant());

    } else if (v.canConvert<QString>()) {
        m_value = v.toString();
        emit valueChanged(this->variant());

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterString>())
                  << ". Nothing is done.";
        emit invalidValue();
    }
}

QString dtkCoreParameterString::value(void) const
{
    return m_value;
}

QVariant dtkCoreParameterString::variant(void) const
{
    return dtk::variantFromValue(*this);
}

//
// dtkCoreParameter.cpp ends here
