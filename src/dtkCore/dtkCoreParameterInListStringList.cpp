// dtkCoreParameterInListStringList.cpp
//

#include "dtkCoreParameterInListStringList.h"

#include "dtkCoreParameterInListStringListObject.h"

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

DTK_DEFINE_PARAMETER(dtk::d_inliststringlist, d_inliststringlist);

//
// dtkCoreParameterInListStringList.cpp ends here
