// dtkCoreParameter.cpp
//

#include "dtkCoreParameter.h"
#include "dtkCoreParameterPath.h"

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

dtkCoreParameter *dtkCoreParameter::castToTop(void)
{
    return dynamic_cast<dtkCoreParameter *>(this);
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

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QStringList& v) : dtkCoreParameterBase<dtkCoreParameterInListStringList>()
{
    m_value = v;
    m_values = v;
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterInListStringList>()
{
    if (v.canConvert<dtkCoreParameterInListStringList>()) {
        auto o(v.value<dtkCoreParameterInListStringList>());
        *this = o;

    } else if (v.canConvert<QStringList>()) {
        m_values = v.value<QStringList>();
        m_value = QStringList();
    }
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const dtkCoreParameterInListStringList& o) : dtkCoreParameterBase<dtkCoreParameterInListStringList>(o), m_value(o.m_value), m_values(o.m_values)
{

}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QString& label, const QStringList& v, const QStringList& list, const QString& doc)  : dtkCoreParameterBase<dtkCoreParameterInListStringList>(label, doc), m_value(v), m_values(list)
{
}

dtkCoreParameterInListStringList& dtkCoreParameterInListStringList::operator = (const QStringList& list)
{
    m_value.clear();
    for (auto item : list) {
        if(m_values.contains(item)) {
            m_value << item;
        } else {
            dtkWarn() << Q_FUNC_INFO << "Value" << item << "is not part of the admissible ones." << m_values;
            this->syncFail();
            return *this;
        }
    }
    this->sync();
    return *this;
}

dtkCoreParameterInListStringList& dtkCoreParameterInListStringList::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterInListStringList>()) {
        *this = v.value<dtkCoreParameterInListStringList>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_value.clear();
        auto list = map["value"].toList();
        for (auto item : list) {
            m_value << item.value<QString>();
        }

        m_values.clear();
        list = map["values"].toList();
        for (auto item : list) {
            m_values << item.value<QString>();
        }

    } else if (v.canConvert<QStringList>()) {
        QStringList list = v.value<QStringList>();
        m_value.clear();
        for (auto item : list) {
            if(m_values.contains(item)) {
                m_value << item;
            } else {
                dtkWarn() << Q_FUNC_INFO << "Value" << item << "is not part of the admissible ones." << m_values;
                this->syncFail();
                return *this;
            }
        }
    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterInListStringList>())
                  << ". Nothing is done.";
        this->syncFail();
        return *this;
    }
    this->sync();
    return *this;
}

dtkCoreParameterInListStringList& dtkCoreParameterInListStringList::operator = (const dtkCoreParameterInListStringList& o)
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_values = o.m_values;
        m_value = o.m_value;
        this->sync();
    }
    return *this;
}

int dtkCoreParameterInListStringList::size(void) const
{
    return m_values.size();
}
QStringList dtkCoreParameterInListStringList::value(void) const
{
    return m_value;
}
QStringList dtkCoreParameterInListStringList::values(void) const
{
    return m_values;
}

void dtkCoreParameterInListStringList::addValue(const QString& val)
{
    if (!m_values.contains(val)) {
        m_values.append(val);
    };
}

void dtkCoreParameterInListStringList::removeValue(const QString& val)
{
    m_values.removeAll(val);
    m_value.removeAll(val);
}


void dtkCoreParameterInListStringList::setValues(const QStringList& val)
{
    m_values.clear();
    for (const auto& v : val) {
        if (!m_values.contains(v)) {
            m_values.append(v);
        }
    }

    for (const auto& v : m_value) {
        if (!m_values.contains(v)) {
            m_value.removeAll(v);
        }
    }

    this->sync();
}

void dtkCoreParameterInListStringList::setValue(const QStringList& value)
{
    m_value.clear();
    for (const auto& v : value) {
        if (m_values.contains(v)) {
            m_value.append(v);
        }
    }

    this->sync();
}

void dtkCoreParameterInListStringList::setValue(const QVariant& v)
{
    QStringList val = v.toStringList();
    this->setValue(val);
}

QVariantHash dtkCoreParameterInListStringList::toVariantHash(void) const
{
    QVariantHash hash = base_type::toVariantHash();

    QList<QVariant> l; l.reserve(m_value.size());
    for (auto v : m_value){
        l << QVariant::fromValue(v);
    }
    QVariant ll(l);
    hash.insert("value", ll);


    QList<QVariant> l2; l2.reserve(m_values.size());
    for (auto v : m_values){
        l2 << QVariant::fromValue(v);
    }
    QVariant ll2(l2);
    hash.insert("values", ll2);

    return hash;
}

DTKCORE_EXPORT QDataStream& operator << (QDataStream& s, const dtkCoreParameterInListStringList& p)
{
    s << p.label();
    s << p.value().size();
    for (auto&& val : p.value()) {
        s << val;
    }
    s << p.values().size();
    for (auto&& val : p.values()) {
        s << val;
    }
    s << p.documentation();

    return s;
}

DTKCORE_EXPORT QDataStream& operator >> (QDataStream& s, dtkCoreParameterInListStringList& p)
{
    QString label; s >> label;
    int size; s >> size;
    QStringList value;
    for (int i = 0; i < size; ++i) {
        QString t; s >> t;
        value << t;
    }

    s >> size;
    QStringList values;
    for (int i = 0; i < size; ++i) {
        QString t; s >> t;
        values << t;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterInListStringList(label, value, values, doc);
    return s;
}

DTKCORE_EXPORT QDebug operator << (QDebug dbg, dtkCoreParameterInListStringList p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "value [";
    for (int i = 0; i < p.value().size(); ++i) {
        if (i)
            dbg.nospace() << ", ";
        dbg.nospace() << p.value().at(i);
    }

    dbg.nospace() << "] , "
                  << "values [";
    for (int i = 0; i < p.values().size(); ++i) {
        if (i)
            dbg.nospace() << ", ";
        dbg.nospace() << p.values().at(i);
    }
    dbg.nospace() << "], "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}




// ///////////////////////////////////////////////////////////////////
// Registration of parameters at runtime
// ///////////////////////////////////////////////////////////////////

DTK_DEFINE_PARAMETER(dtk::d_uchar, d_uchar);
DTK_DEFINE_PARAMETER(dtk::d_char, d_char);
DTK_DEFINE_PARAMETER(dtk::d_uint, d_uint);
DTK_DEFINE_PARAMETER(dtk::d_int, d_int);
DTK_DEFINE_PARAMETER(dtk::d_real, d_real);
DTK_DEFINE_PARAMETER(dtk::d_bool, d_bool);
DTK_DEFINE_PARAMETER(dtk::d_string, d_string);

DTK_DEFINE_PARAMETER(dtk::d_inliststring, d_inliststring);
DTK_DEFINE_PARAMETER(dtk::d_inliststringlist, d_inliststringlist);
DTK_DEFINE_PARAMETER(dtk::d_inlistreal, d_inlistreal);
DTK_DEFINE_PARAMETER(dtk::d_inlistint, d_inlistint);

DTK_DEFINE_PARAMETER(dtk::d_range_uchar, d_range_uchar);
DTK_DEFINE_PARAMETER(dtk::d_range_char, d_range_char);
DTK_DEFINE_PARAMETER(dtk::d_range_uint, d_range_uint);
DTK_DEFINE_PARAMETER(dtk::d_range_int, d_range_int);
DTK_DEFINE_PARAMETER(dtk::d_range_real, d_range_real);

//
// dtkCoreParameter.cpp ends here
