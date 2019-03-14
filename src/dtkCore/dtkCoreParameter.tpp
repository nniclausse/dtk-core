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

#include "dtkCoreMetaType.h"

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

template <typename F>
inline QMetaObject::Connection dtkCoreAbstractParameter::connect(F slot)
{
    m_enable_share_connection = false;
    if (!m_connection || m_connection.use_count() > 1) {
        m_connection = connection(new dtkCoreAbstractParameterConnection());
    }
    if (m_connection->value) {
        m_connection->disconnect(m_connection->value);
    }

    m_connection->value = QObject::connect(m_connection.get(), &dtkCoreAbstractParameterConnection::valueChanged, slot);
    return m_connection->value;
}

template <typename F>
inline QMetaObject::Connection dtkCoreAbstractParameter::connectFail(F slot)
{
    m_enable_share_connection = false;
    if (!m_connection || m_connection.use_count() > 1) {
        m_connection = connection(new dtkCoreAbstractParameterConnection());
    }
    if (m_connection->invalid) {
        m_connection->disconnect(m_connection->invalid);
    }

    m_connection->invalid = QObject::connect(m_connection.get(), &dtkCoreAbstractParameterConnection::invalidValue, slot);
    return m_connection->invalid;
}

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

template <typename Derive>
inline dtkCoreParameterBase<Derive>::dtkCoreParameterBase(const QString& label, const QString& doc) : dtkCoreAbstractParameter(label, doc)
{

}

template <typename Derive>
inline dtkCoreParameterBase<Derive>::dtkCoreParameterBase(const dtkCoreParameterBase& o) : dtkCoreAbstractParameter(o)
{

}

template <typename Derive>
inline QVariant dtkCoreParameterBase<Derive>::variant(void) const
{
    bool old = this->m_enable_share_connection;
    if (!old)
        this->m_enable_share_connection = true;
    QVariant res = dtk::variantFromValue(static_cast<const Derive&>(*this));
    this->m_enable_share_connection = old;
    return res;
}

template <typename Derive>
inline void dtkCoreParameterBase<Derive>::copyAndShare(dtkCoreAbstractParameter *source)
{
    if (!source) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter is null. Nothing is done";

    } else {
        if (this != source) {
            Derive *s = dynamic_cast<Derive *>(source);
            if (s) {
                Derive *self = static_cast<Derive *>(this);
                *self = *s;
                if (s->m_connection) {
                    self->m_connection = s->m_connection;
                } else {
                    dtkWarn() << Q_FUNC_INFO << "Input parameter has no connection. Only copy of values is done.";
                }

            } else {
                dtkWarn() << Q_FUNC_INFO << "Input parameter is not of same type than target one. Nothing is done";
            }
        }
    }
}

template <typename Derive>
inline void dtkCoreParameterBase<Derive>::copyAndShare(const QVariant& v)
{
    if (!v.canConvert<Derive>()) {
        dtkWarn() << Q_FUNC_INFO << "Input variant is not of type" << QMetaType::typeName(qMetaTypeId<Derive>()) << ". Nothing is done.";

    } else {
        Derive i = v.value<Derive>();
        Derive& self = static_cast<Derive&>(*this);
        self = i;
        if (i.m_connection) {
            self.m_connection = i.m_connection;
        } else {
            dtkWarn() << Q_FUNC_INFO << "Input parameter has no connection. Only copy of values is done.";
        }
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter simple version implementation
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameter>()
{
    if (v.canConvert<dtkCoreParameter>()) {
        auto o(v.value<dtkCoreParameter>());
        *this = o;

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();
    }
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const dtkCoreParameter& o) : dtkCoreParameterBase<dtkCoreParameter>(o), m_value(o.m_value)
{

}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const QString& label, const T& t, const QString& doc) : dtkCoreParameterBase<dtkCoreParameter>(label, doc), m_value(t)
{

}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const T& t) -> dtkCoreParameter&
{
    m_value = t;
    this->sync();
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T, Enable>>()) {
        *this = v.value<dtkCoreParameter<T, Enable>>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_value = map["value"].value<T>();

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const dtkCoreParameter& o) -> dtkCoreParameter&
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_value = o.m_value;
        this->sync();
    }
    return *this;
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::operator T() const
{
    return m_value;
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setValue(const T& t)
{
    if (m_value != t) {
        m_value = t;
        this->sync();
    }
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setValue(const QVariant &v)
{
    if (v.canConvert<dtkCoreParameter>()) {
        *this = v.value<dtkCoreParameter>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_value = map["value"].value<T>();

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameter<T, Enable>>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}

template <typename T, typename Enable>
inline T dtkCoreParameter<T, Enable>::value(void) const
{
    return m_value;
}

template <typename T>
inline dtk::parameter_not_arithmetic<T, QDataStream>& operator << (QDataStream& s, const dtkCoreParameter<T>& p)
{
    s << p.label();
    s << p.value();
    s << p.documentation();

    return s;
}

template <typename T>
inline dtk::parameter_not_arithmetic<T, QDataStream>& operator >> (QDataStream& s, dtkCoreParameter<T>& p)
{
    QString label; s >> label;
    T t; s >> t;
    QString doc; s >> doc;

    p = dtkCoreParameter<T>(label, t, doc);
    return s;
}

template <typename T>
inline dtk::parameter_not_arithmetic<T, QDebug>& operator << (QDebug& dbg, dtkCoreParameter<T> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label : " << p.label() << ", "
                  << "value : " << p.value() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter for numerical types implementation
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const T& t) : dtkCoreParameterBase<dtkCoreParameter>(), m_val(t)
{
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameter>()
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        auto o(v.value<dtkCoreParameter<T>>());
        *this = o;

    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();
    }
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const dtkCoreParameter& o) : dtkCoreParameterBase<dtkCoreParameter>(o), m_val(o.m_val), m_bounds(o.m_bounds), m_decimals(o.m_decimals)
{

}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const QString& label, const T& t, const T& min, const T& max, const QString& doc) : dtkCoreParameterBase<dtkCoreParameter>(label, doc), m_val(t), m_bounds({min, max})
{
}

template <typename T> template <typename U, typename>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const QString& label, const T& t, const T& min, const T& max, const int& decimals, const QString& doc) : dtkCoreParameterBase<dtkCoreParameter>(label, doc), m_val(t), m_bounds({min, max}), m_decimals(decimals)
{
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val = t;
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const dtkCoreParameter& o) -> dtkCoreParameter&
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_val = o.m_val;
        m_bounds = o.m_bounds;
        m_decimals = o.m_decimals;
        this->sync();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val = (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += t;
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this += v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val += v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= t;
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this -= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val -= v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= t;
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this *= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val *= v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= t;
    this->sync();
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this /= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val /= v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const U& t) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= t;
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const QVariant& v) -> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameter&>
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this %= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val %= v.value<T>();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= (T)(o);
    this->sync();
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator == (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == t);
}

template <typename T>
inline bool dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator == (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        return (*this == v.value<dtkCoreParameter<T>>());

    } else if (v.canConvert<T>()) {
        return (m_val == v.value<T>());
    }
    return false;
}

template <typename T> template <typename U>
inline auto  dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator == (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == (T)(o));
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator != (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != t);
}

template <typename T>
inline bool dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator != (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        return (*this != v.value<dtkCoreParameter<T>>());

    } else if (v.canConvert<T>()) {
        return (m_val != v.value<T>());
    }
    return true;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator != (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != (T)(o));
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator T() const
{
    return m_val;
}

template <typename T>
inline void dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::setValue(const T& t)
{
    if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
        dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();

    } else if (t != m_val) {
        m_val = t;
        this->sync();
    }
}

template <typename T>
inline void dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();
        // value is copied, do not check bounds

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_val = map["value"].value<T>();
        m_bounds[0] = map["min"].value<T>();
        m_bounds[1] = map["max"].value<T>();

        if (map.contains("decimals")) {
            m_decimals = map["decimals"].value<int>();
        }

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();

        if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
            dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            this->syncFail();
            return;

        } else if (t != m_val) {
            m_val = t;
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameter<T, dtk::parameter_arithmetic<T>>>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}

template <typename T>
inline T dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::value(void) const
{
    return m_val;
}

template <typename T>
inline T dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::min(void) const
{
    return this->m_bounds[0];
}

template <typename T>
inline T dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::max(void) const
{
    return this->m_bounds[1];
}

template <typename T>
inline const std::array<T, 2>& dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::bounds(void) const
{
    return this->m_bounds;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::setDecimals(const int& d) -> std::enable_if_t<std::is_floating_point<U>::value>
{
    this->m_decimals = d;
}

template <typename T>
inline int dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::decimals(void) const
{
    return this->m_decimals;
}

template <typename T>
inline dtk::parameter_arithmetic<T, QDataStream>& operator << (QDataStream& s, const dtkCoreParameter<T>& p)
{
    s << p.label();
    s << p.value();
    s << p.min();
    s << p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

template <typename T, typename E, typename F>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T>& p)
{
    QString label; s >> label;
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameter<T, dtk::parameter_arithmetic<T>>(label, val, min, max, dec, doc);
    return s;
}

template <typename T, typename E, typename F, typename U>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T>& p)
{
    QString label; s >> label;
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameter<T, dtk::parameter_arithmetic<T>>(label, val, min, max, doc);
    return s;
}

template <typename T, typename E>
inline QDebug& operator << (QDebug& dbg, dtkCoreParameter<T> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label : " << p.label() << ", "
                  << "value : " << p.value() << ", "
                  << "bounds : [" << p.bounds()[0] << ", " << p.bounds()[1] << "], "
                  << "decimals : " << p.decimals() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterInList implementation
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const T& t) : dtkCoreParameterBase<dtkCoreParameterInList>()
{
    m_values << t;
    m_value_index = 0;
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterInList>()
{
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

}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, const T& t, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    m_value_index = m_values.indexOf(t);
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, int index, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values), m_value_index(index)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    Q_ASSERT_X(((index > -1) && (index < values.size())), Q_FUNC_INFO, "Input index is out of range");
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QString& label, const QList<T>& values, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterInList>(label, doc), m_values(values), m_value_index(0)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
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
        this->sync();
    }
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterInList<T>>()) {
        *this = v.value<dtkCoreParameterInList<T>>();

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

    } else if (v.canConvert<T>()) {
        int index = m_values.indexOf(v.value<T>());
        if (index < 0) {
            dtkWarn() << Q_FUNC_INFO << "Value is not part of the admissible ones.";
            this->syncFail();
            return;

        } else {
            m_value_index = index;
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterInList<T>>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
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
inline QDebug& operator << (QDebug& dbg, dtkCoreParameterInList<T> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label" << p.label() << ", "
                  << "value_index" << p.valueIndex() << ", "
                  << "values [";
    for (int i = 0; i < p.values.size(); ++i) {
        if (i)
            dbg.nospace() << ", ";
        dbg.nospace() << p.values.at(i);
    }
    dbg.nospace() << "], "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

//
// dtkCoreParameter.tpp ends here
