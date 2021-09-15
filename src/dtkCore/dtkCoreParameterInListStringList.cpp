// dtkCoreParameterInListStringList.cpp
//

#include "dtkCoreParameterInListStringList.h"

#include "dtkCoreParameterInListStringListObject.h"


dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(void) : dtkCoreParameterBase<dtkCoreParameterInListStringList>()
{
    m_object = new dtkCoreParameterInListStringListObject(this);
}

dtkCoreParameterInListStringList::~dtkCoreParameterInListStringList(void)
{
    delete m_object;
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QStringList& v) : dtkCoreParameterBase<dtkCoreParameterInListStringList>()
{
    m_object = new dtkCoreParameterInListStringListObject(this);
    m_value = v;
    m_list = v;
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterInListStringList>()
{
    m_object = new dtkCoreParameterInListStringListObject(this);
    if (v.canConvert<dtkCoreParameterInListStringList>()) {
        auto o(v.value<dtkCoreParameterInListStringList>());
        *this = o;

    } else if (v.canConvert<QStringList>()) {
        m_list = v.value<QStringList>();
        m_value = QStringList();
    }
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const dtkCoreParameterInListStringList& o) : dtkCoreParameterBase<dtkCoreParameterInListStringList>(o), m_value(o.m_value), m_list(o.m_list)
{
    m_object = new dtkCoreParameterInListStringListObject(this);
}

dtkCoreParameterInListStringList::dtkCoreParameterInListStringList(const QString& label, const QStringList& v, const QStringList& list, const QString& doc)  : dtkCoreParameterBase<dtkCoreParameterInListStringList>(label, doc), m_value(v), m_list(list)
{
    m_object = new dtkCoreParameterInListStringListObject(this);
}

dtkCoreParameterInListStringList& dtkCoreParameterInListStringList::operator = (const QStringList& list)
{
    m_value.clear();
    bool must_notify = false;
    for (auto item : list) {
        if(m_list.contains(item)) {
            m_value << item;
        } else {
            dtkWarn() << Q_FUNC_INFO << "Value" << item << "is not part of the admissible ones." << m_list;
            this->syncFail();
            return *this;
        }
    }
    if (must_notify) {
        m_object->notifyValue(m_value);
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

        m_list.clear();
        list = map["values"].toList();
        for (auto item : list) {
            m_list << item.value<QString>();
        }

        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyList(m_list);
        m_object->notifyValue(m_value);

    } else if (v.canConvert<QStringList>()) {
        QStringList list = v.value<QStringList>();
        m_value.clear();
        bool must_notify = false;
        for (auto item : list) {
            if(m_list.contains(item)) {
                m_value << item;
            } else {
                dtkWarn() << Q_FUNC_INFO << "Value" << item << "is not part of the admissible ones." << m_list;
                this->syncFail();
                return *this;
            }
        }
        if (must_notify) {
            m_object->notifyValue(m_value);
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
        m_list = o.m_list;
        m_value = o.m_value;
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyList(m_list);
        m_object->notifyValue(m_value);
        this->sync();
    }
    return *this;
}

int dtkCoreParameterInListStringList::size(void) const
{
    return m_list.size();
}

QStringList dtkCoreParameterInListStringList::list(void) const
{
    return m_list;
}

QStringList dtkCoreParameterInListStringList::value(void) const
{
    return m_value;
}

void dtkCoreParameterInListStringList::addValue(const QString& val)
{
    if (!m_list.contains(val)) {
        m_list.append(val);
        m_object->notifyList(m_list);
    };
}

void dtkCoreParameterInListStringList::removeValue(const QString& val)
{
    int nl = m_list.removeAll(val);
    int nv = m_value.removeAll(val);

    if (nl != 0) m_object->notifyList(m_list);
    if (nv != 0) m_object->notifyValue(m_value);
}

void dtkCoreParameterInListStringList::setList(const QStringList& list)
{
    m_list.clear();
    bool must_notify = false;
    for (const auto& v : list) {
        if (!m_list.contains(v)) {
            m_list.append(v);
            must_notify = true;
        }
    }
    if (must_notify) {
        m_object->notifyList(m_list);
    }

    must_notify = false;
    for (const auto& v : m_value) {
        if (!m_list.contains(v)) {
            m_value.removeAll(v);
            must_notify = true;
        }
    }
    if (must_notify) {
        m_object->notifyValue(m_value);
    }

    this->sync();
}

void dtkCoreParameterInListStringList::setValue(const QStringList& value)
{
    m_value.clear();
    bool must_notify = false;
    for (const auto& v : value) {
        if (m_list.contains(v)) {
            m_value.append(v);
            must_notify = true;
        }
    }
    if (must_notify) {
        m_object->notifyValue(m_value);
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


    QList<QVariant> l2; l2.reserve(m_list.size());
    for (auto v : m_list){
        l2 << QVariant::fromValue(v);
    }
    QVariant ll2(l2);
    hash.insert("values", ll2);

    return hash;
}

dtkCoreParameterObject *dtkCoreParameterInListStringList::object(void)
{
    return m_object;
}

QStringList dtkCoreParameterInListStringList::values(void) const
{
    return this->list();
}

void dtkCoreParameterInListStringList::setValues(const QStringList& list)
{
    this->setList(list);
}

DTKCORE_EXPORT QDataStream& operator << (QDataStream& s, const dtkCoreParameterInListStringList& p)
{
    s << p.label();
    s << p.value().size();
    for (auto&& val : p.value()) {
        s << val;
    }
    s << p.list().size();
    for (auto&& val : p.list()) {
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
    QStringList list;
    for (int i = 0; i < size; ++i) {
        QString t; s >> t;
        list << t;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterInListStringList(label, value, list, doc);
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
                  << "list [";
    for (int i = 0; i < p.list().size(); ++i) {
        if (i)
            dbg.nospace() << ", ";
        dbg.nospace() << p.list().at(i);
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
