// dtkCoreParameter.cpp
//

#include "dtkCoreParameter.h"

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
// helper functions
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    namespace core {

        dtkCoreParameters readParameters(const QString& filename)
        {
            QFile definition_file(filename);

            dtkCoreParameters parameters;
            dtkCoreParameters dummy;

            if(!definition_file.open(QFile::ReadOnly)) {
                dtkWarn() << Q_FUNC_INFO << "input file" << filename << "cannot be opened in ReadOnly mode.";
                return dummy;
            }

            QJsonParseError definition_error;
            QJsonDocument definition_document = QJsonDocument::fromJson(definition_file.readAll(), &definition_error);

            if(definition_error.error != QJsonParseError::NoError) {
                dtkWarn() << Q_FUNC_INFO << "Error :" << definition_error.errorString() << "parsing" << filename << "offset :" << definition_error.offset << ".";
                return dummy;
            }

            QJsonObject definition_object = definition_document.object();
            if(!definition_object.contains("contents")) {
                dtkWarn() << Q_FUNC_INFO << "The nature parameters file should contain a first json object with key 'contents'. The file cannot be processed any further.";
                return dummy;
            }

            QJsonValue definition_contents = definition_object["contents"];
            QJsonObject definitions;
            if (definition_contents.isObject()) {
                definitions = definition_contents.toObject();
            } else {
                dtkWarn() << Q_FUNC_INFO << "The first object with key 'contents' must be an object.";
            }

            QStringList keys = definitions.keys();
            for (auto it = definitions.begin(); it != definitions.end(); ++it) {
                QString uid = keys.takeFirst();
                if (it->isObject()) {
                    QJsonObject content_object = it->toObject();

                    QString type = content_object["type"].toString();

                    QVariantHash map = content_object.toVariantHash();
                    //map.insert("type", type);

                    dtkCoreParameter *parameter = dtkCoreParameter::create(map);
                    if (!parameter) {
                        dtkWarn() << Q_FUNC_INFO << "fail to create parameter" << type << map;
                        return dummy;
                    }

                    parameter->setUid(uid);

                    parameters.insert(uid, parameter);

                } else {
                    dtkWarn() << Q_FUNC_INFO << "'contents' sections are expected to contain objects only. Non object entry is ignored.";
                }
            }
            return parameters;
        }
        bool writeParameters(const dtkCoreParameters& map, const QString& filename)
        {
            QJsonObject parametersObject;
            parametersObject["contents"] = toJson(map);

            QJsonDocument savedoc(parametersObject);

            QFile output_file(filename);
            if (!output_file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
                dtkWarn() << Q_FUNC_INFO << "output file" << filename << "cannot be opened in WriteOnly mode.";
                return false;
            }

            output_file.write(savedoc.toJson());
            output_file.close();

            return true;
        }

        QJsonObject toJson(const dtkCoreParameters& map)
        {
            QVariantHash target_map;
            for (auto it = map.begin(); it != map.end(); ++it) {
                target_map[it.key()] = QVariant(it.value()->toVariantHash());
            }

            QJsonObject parametersObject = QJsonObject::fromVariantHash(target_map);

            return parametersObject;
        }

    }
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreParameter::dtkCoreParameter(const QString& label, const QString& doc) : m_label(label), m_doc(doc)
{

}

dtkCoreParameter::dtkCoreParameter(const dtkCoreParameter& o) : m_label(o.m_label), m_doc(o.m_doc)
{
    if (o.m_enable_share_connection) {
        m_connection = o.m_connection;
    }
}

void dtkCoreParameter::setUid(const QString& uid)
{
    this->m_uid = uid;
}

const QString& dtkCoreParameter::uid(void) const
{
    return this->m_uid;
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
    if (m_connection) {
        m_connection->blockSignals(b);
    }
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
            m_connection->param_list.removeAll(this);
            m_connection = connection(nullptr);
        } else {
            for (auto c : m_connection->value_list) {
                if (c) {
                    m_connection->disconnect(c);
                }
            }
            m_connection->value_list.clear();
        }
    }
}

void dtkCoreParameter::disconnect(QMetaObject::Connection c)
{
    QObject::disconnect(c);
    if(m_connection) {
        m_connection->value_list.removeOne(c);
    }
}

void dtkCoreParameter::syncFail(void)
{
    if (m_connection) {
        emit m_connection->invalidValue();
    }
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
            m_connection->invalid_list.clear();
        }
    }
}

void dtkCoreParameter::shareValue(QVariant v)
{
    for (dtkCoreParameter *p: this->m_connection->param_list) {
        p->setValue(v);
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
