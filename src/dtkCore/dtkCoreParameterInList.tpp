// dtkCoreParameterInList.tpp
//

#include "dtkCoreParameterInListObject.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterInList implementation
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList() : dtkCoreParameterBase<dtkCoreParameterInList>()
{
    m_object = new dtkCoreParameterInListObject<T>(this);
}

template <typename T>
inline dtkCoreParameterInList<T>::~dtkCoreParameterInList()
{
    delete m_object;
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const T& t) : dtkCoreParameterBase<dtkCoreParameterInList>()
{
    m_object = new dtkCoreParameterInListObject<T>(this);
    m_values << t;
    m_value_index = 0;
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterInList>()
{
    m_object = new dtkCoreParameterInListObject<T>(this);
    if (v.canConvert<dtkCoreParameterInList<T>>()) {
        auto o(v.value<dtkCoreParameterInList<T>>());
        *this = o;

    } else if (v.canConvert<T>()) {
        m_values << v.value<T>();
        m_value_index = 0;
    }
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const dtkCoreParameterInList& o) : dtkCoreParameterBase<dtkCoreParameterInList>(o), m_values(o.m_values), m_value_index(o.m_value_index)
{
    m_object = new dtkCoreParameterInListObject<T>(this);
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, const T& t, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values)
{
    m_object = new dtkCoreParameterInListObject<T>(this);
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    m_value_index = m_values.indexOf(t);
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, int index, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values), m_value_index(index)
{
    m_object = new dtkCoreParameterInListObject<T>(this);
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    Q_ASSERT_X(((index > -1) && (index < values.size())), Q_FUNC_INFO, "Input index is out of range");
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values), m_value_index(0)
{
    m_object = new dtkCoreParameterInListObject<T>(this);
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
}

template <typename T>
inline dtkCoreParameterInList<T>& dtkCoreParameterInList<T>::operator = (const T& t)
{
    int index = m_values.indexOf(t);
    if (index < 0) {
        dtkWarn() << Q_FUNC_INFO << "Value index (" << index << ") is out of range [" << 0 << "," << m_values.size()-1 << "]";
        this->syncFail();

    } else {
        m_value_index = index;
        m_object->notifyIndex(index);
        this->sync();
    }
    return *this;
}

template <typename T>
inline dtkCoreParameterInList<T>& dtkCoreParameterInList<T>::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterInList>()) {
        *this = v.value<dtkCoreParameterInList>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_value_index = map["index"].value<int>();

        m_values.clear();
        auto list = map["values"].toList();
        for (auto item : list) {
            m_values << item.value<T>();
        }
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyList(m_values);
        m_object->notifyIndex(m_value_index);

    } else if (v.canConvert<T>()) {
        int index = m_values.indexOf(v.value<T>());
        if (index < 0) {
            dtkWarn() << Q_FUNC_INFO << "Value is not part of the admissible ones.";
            this->syncFail();
            return *this;

        } else {
            m_value_index = index;
            m_object->notifyIndex(m_value_index);
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterInList>())
                  << ". Nothing is done.";
        this->syncFail();
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T>
inline dtkCoreParameterInList<T>& dtkCoreParameterInList<T>::operator = (const dtkCoreParameterInList& o)
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_values = o.m_values;
        m_value_index = o.m_value_index;
        this->sync();
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyList(m_values);
        m_object->notifyIndex(m_value_index);
    }
    return *this;
}

template <typename T>
inline dtkCoreParameterInList<T>::operator T() const
{
    return m_values.value(m_value_index);
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValueIndex(int index)
{
    if (index < 0 || index > m_values.size()-1) {
        dtkWarn() << Q_FUNC_INFO << "Value index (" << index << ") is out of range [" << 0 << "," << m_values.size()-1 << "]";
        this->syncFail();

    } else {
        m_value_index = index;
        m_object->notifyIndex(m_value_index);
        this->sync();
    }
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValue(const T& t)
{
    int index = m_values.indexOf(t);
    if (index < 0) {
        dtkWarn() << Q_FUNC_INFO << "Value index (" << index << ") is out of range [" << 0 << "," << m_values.size()-1 << "]";
        this->syncFail();

    } else {
        m_value_index = index;
        m_object->notifyIndex(m_value_index);
        this->sync();
    }
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValues(const QList<T>& l)
{
    m_values = l;
    m_value_index = 0;
    m_object->notifyList(m_values);
    m_object->notifyIndex(m_value_index);
    this->sync();
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterInList>()) {
        *this = v.value<dtkCoreParameterInList>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_value_index = map["index"].value<int>();

        m_values.clear();
        auto list = map["values"].toList();
        for(auto item : list) {
            m_values << item.value<T>();
        }
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyList(m_values);
        m_object->notifyIndex(m_value_index);

    } else if (v.canConvert<T>()) {
        int index = m_values.indexOf(v.value<T>());
        if (index < 0) {
            dtkWarn() << Q_FUNC_INFO << "Value is not part of the admissible ones.";
            this->syncFail();
            return;

        } else {
            m_value_index = index;
            m_object->notifyIndex(m_value_index);
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterInList>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}


template <typename T>
inline QVariantHash dtkCoreParameterInList<T>::toVariantHash(void) const
{
    QVariantHash hash = base_type::toVariantHash();
    hash.insert("index", m_value_index);
    QList<QVariant> l; l.reserve(m_values.size());
    for (auto v : m_values){
        l << QVariant::fromValue(v);
    }
    QVariant ll(l);
    hash.insert("values", ll);

    return hash;
}

template <typename T>
inline dtkCoreParameterObject * dtkCoreParameterInList<T>::object(void)
{
    return this->m_object;
}


template <typename T>
inline int dtkCoreParameterInList<T>::valueIndex(void) const
{
    return m_value_index;
}

template <typename T>
inline T dtkCoreParameterInList<T>::value(void) const
{
    return m_values.value(m_value_index);
}

template <typename T>
inline QList<T> dtkCoreParameterInList<T>::values(void) const
{
    return m_values;
}

template <typename T>
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterInList<T>& p)
{
    s << p.label();
    s << p.valueIndex();
    s << p.values().size();
    for (auto&& val : p.values()) {
        s << val;
    }
    s << p.documentation();

    return s;
}

template <typename T>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterInList<T>& p)
{
    QString label; s >> label;
    int index; s >> index;
    int size; s >> size;
    QList<T> values;
    for (int i = 0; i < size; ++i) {
        T t; s >> t;
        values << t;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterInList<T>(label, index, values, doc);
    return s;
}

template <typename T>
inline QDebug operator << (QDebug dbg, dtkCoreParameterInList<T> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "value_index " << p.valueIndex() << ", "
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

//
// dtkCoreParameterInList.tpp ends here
