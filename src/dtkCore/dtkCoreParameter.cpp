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

dtkCoreParameter::dtkCoreParameter(const QString& label, const QString& doc) : m_label(label), m_doc(doc)
{

}

dtkCoreParameter::dtkCoreParameter(const dtkCoreParameter& o) : m_label(o.m_label), m_doc(o.m_doc)
{
    if (o.m_enable_share_connection) {
        m_connection = o.m_connection;
    }
}

void dtkCoreParameter::setLabel(const QString& label)
{
    this->m_label = label;
}

QString dtkCoreParameter::label(void) const
{
    return this->m_label;
}

void dtkCoreParameter::setDocumentation(const QString& doc)
{
    this->m_doc = doc;
}

QString dtkCoreParameter::documentation(void) const
{
    return this->m_doc;
}

void dtkCoreParameter::block(bool b)
{
    if (m_connection)
        m_connection->blockSignals(b);
}

void dtkCoreParameter::sync(void)
{
    if (m_connection) {
        emit m_connection->valueChanged(this->variant());
    }
}

void dtkCoreParameter::disconnect(void)
{
    if (m_connection) {
        if (m_connection.use_count() > 1) {
            m_connection = connection(nullptr);
        } else {
            for (auto c : m_connection->value_list) {
                if (c) {
                    m_connection->disconnect(c);
                }
            }
        }
    }
}

void dtkCoreParameter::syncFail(void)
{
    if (m_connection)
        emit m_connection->invalidValue();
}

void dtkCoreParameter::disconnectFail(void)
{
    if (m_connection) {
        if (m_connection.use_count() > 1) {
            m_connection = connection(nullptr);
        } else {
            for (auto c : m_connection->invalid_list) {
                if (c) {
                    m_connection->disconnect(c);
                }
            }
        }
    }
}

bool dtkCoreParameter::shareConnectionWith(dtkCoreParameter *source)
{
    m_enable_share_connection = false;
    if (!source || !source->m_connection) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter has no connection. Nothing is done.";
        return false;

    } else {
        if (this != source) {
            if (m_connection != source->m_connection) {
                m_connection = source->m_connection;
            }
            return true;
        }
        return true;
    }
}

dtkCoreParameter *dtkCoreParameter::create(const QVariantHash& map)
{
    if (map.empty()) {
        qDebug() << Q_FUNC_INFO << "Input variant does not contain a VariantHash. Nullptr is returned.";
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
    dtkCoreParameter *p = pv.value<dtkCoreParameter *>();

    if (!p) {
        qDebug() << Q_FUNC_INFO << "Cannot convert QVariant into dtkCoreParameter. Nullptr is returned.";
        return nullptr;
    }

    p->setValue(QVariant(map));
    return p;
}

//
// dtkCoreParameter.cpp ends here
