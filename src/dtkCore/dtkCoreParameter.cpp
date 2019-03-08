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

void dtkCoreAbstractParameter::block(bool b)
{
    this->blockSignals(b);
}

void dtkCoreAbstractParameter::sync(void)
{
    emit this->valueChanged(this->variant());
}

dtkCoreAbstractParameter *dtkCoreAbstractParameter::create(const QVariant& v)
{
    auto map = v.toHash();
    if (map.empty()) {
        qDebug() << Q_FUNC_INFO << "Input variant does not contain a VraiantHash. Nullptr is returned.";
        return nullptr;
    }
    QString p_type_name = map["type"].toString();
    int p_type_id = QMetaType::type(qPrintable(p_type_name));

    if (p_type_id == QMetaType::UnknownType) {
        qDebug() << Q_FUNC_INFO << "Cannot create parameter of type"
                  << p_type_name << ". Nullptr is returned.";
        return nullptr;
    }

    void *ptr = QMetaType::create(p_type_id);
    if (!ptr) {
        qDebug() << Q_FUNC_INFO << "Parameter of type" << p_type_name << "cannot be created. Nullptr is returned.";
        return nullptr;
    }
    p_type_id = QMetaType::type(qPrintable(p_type_name + "*"));
    if (p_type_id == QMetaType::UnknownType) {
        qDebug() << Q_FUNC_INFO << "Cannot embed pointer to a parameter of type"
                  << p_type_name << "into a QVariant. Please check that the type has been registered at runtime to QMetaType system. Nullptr is returned.";
        return nullptr;
    }
    QVariant pv = QVariant(p_type_id, &ptr, 1);
    dtkCoreAbstractParameter *p = pv.value<dtkCoreAbstractParameter *>();

    if (!p) {
        qDebug() << Q_FUNC_INFO << "Cannot convert QVariant into dtkCoreAbstractParameter. Nullptr is returned.";
        return nullptr;
    }

    p->setValue(v);
    return p;
}

//
// dtkCoreParameter.cpp ends here
