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
// dtkCoreParameter simple version implementation
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const QVariant& v) : dtkCoreAbstractParameter()
{
    if (v.canConvert<dtkCoreParameter>()) {
        *this = v.value<dtkCoreParameter>();

    } else {
        m_value = v.toString();
    }
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const dtkCoreParameter& o) : dtkCoreAbstractParameter(o.m_doc), m_value(o.m_value)
{

}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const T& t, const QString& doc) : dtkCoreAbstractParameter(doc), m_value(t)
{

}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const T& t) -> dtkCoreParameter&
{
    m_value = t;
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T, Enable>>()) {
        *this = v.value<dtkCoreParameter<T, Enable>>();

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();
    }
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const dtkCoreParameter& o) -> dtkCoreParameter&
{
    if (this != &o) {
        m_doc = o.m_doc;
        m_value = o.m_value;
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
        emit valueChanged(this->variant());
    }
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setValue(const QVariant &v)
{
    if (v.canConvert<dtkCoreParameter>()) {
        *this = v.value<dtkCoreParameter>();
        emit valueChanged(this->variant());

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();
        emit valueChanged(this->variant());

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameter<T, Enable>>())
                  << ". Nothing is done.";
        emit invalidValue();
    }
}

template <typename T, typename Enable>
inline T dtkCoreParameter<T, Enable>::value(void) const
{
    return m_value;
}

template <typename T, typename Enable>
inline QVariant dtkCoreParameter<T, Enable>::variant(void) const
{
    return dtk::variantFromValue(*this);
}



// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter for numerical types implementation
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const T& t) : dtkCoreAbstractParameter(), m_val(t)
{
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const QVariant& v) : dtkCoreAbstractParameter()
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();
    }
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const dtkCoreParameter& o) : dtkCoreAbstractParameter(o.m_doc), m_val(o.m_val), m_bounds(o.m_bounds), m_decimals(o.m_decimals)
{
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(dtkCoreParameter&& o) : dtkCoreAbstractParameter(o.m_doc), m_val(std::move(o.m_val)), m_bounds(std::move(o.m_bounds)), m_decimals(std::move(o.m_decimals))
{
}

template <typename T>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const T& t, const T& min, const T& max, const QString& doc) : dtkCoreAbstractParameter(doc), m_val(t), m_bounds({min, max})
{
}

template <typename T> template <typename U, typename>
inline dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::dtkCoreParameter(const T& t, const T& min, const T& max, const int& decimals, const QString& doc) : dtkCoreAbstractParameter(doc), m_val(t), m_bounds({min, max}), m_decimals(decimals)
{
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val = t;
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();
    }
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const dtkCoreParameter& o) -> dtkCoreParameter&
{
    if (this != &o) {
        m_doc = o.m_doc;
        m_val = o.m_val;
        m_bounds = o.m_bounds;
        m_decimals = o.m_decimals;
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator = (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val = (T)(o);
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += t;
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this += v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val += v.value<T>();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator += (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += (T)(o);
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= t;
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this -= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val -= v.value<T>();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator -= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= (T)(o);
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= t;
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this *= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val *= v.value<T>();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator *= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= (T)(o);
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= t;
    return *this;
}

template <typename T>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this /= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val /= v.value<T>();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator /= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= (T)(o);
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const U& t) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= t;
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const QVariant& v) -> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameter&>
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this %= v.value<dtkCoreParameter<T>>();

    } else if (v.canConvert<T>()) {
        m_val %= v.value<T>();
    }
    return *this;
}

template <typename T> template <typename U>
inline auto dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::operator %= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= (T)(o);
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
        emit invalidValue();

    } else if (t != m_val) {
        m_val = t;
        emit valueChanged(this->variant());
    }
}

template <typename T>
inline void dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();
        // value is copied, do not check bounds
        emit valueChanged(this->variant());

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();

        if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
            dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            emit invalidValue();

        } else if (t != m_val) {
            m_val = t;
            emit valueChanged(this->variant());
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameter<T, dtk::parameter_arithmetic<T>>>())
                  << ". Nothing is done.";
        emit invalidValue();
    }
}

template <typename T>
inline T dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::value(void) const
{
    return m_val;
}

template <typename T>
inline QVariant dtkCoreParameter<T, dtk::parameter_arithmetic<T>>::variant(void) const
{
    return dtk::variantFromValue(*this);
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
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameter<T, dtk::parameter_arithmetic<T>>& p)
{
    s << p.value();
    s << p.min();
    s << p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

template <typename T, typename Enable>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T, dtk::parameter_arithmetic<T>>& p)
{
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameter<T, dtk::parameter_arithmetic<T>>(val, min, max, dec, doc);
    emit p.valueChanged(p.variant());
    return s;
}

template <typename T, typename Enable, typename U>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T, dtk::parameter_arithmetic<T>>& p)
{
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameter<T, dtk::parameter_arithmetic<T>>(val, min, max, doc);
    emit p.valueChanged(p.variant());

    return s;
}

template <typename T>
inline QDebug& operator << (QDebug& dbg, dtkCoreParameter<T, dtk::parameter_arithmetic<T>> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " { ";
    dbg.nospace() << "value : " << p.value() << ", "
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
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const T& t) : dtkCoreAbstractParameter()
{
    m_values << t;
    m_value_index = 0;
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QVariant& v) : dtkCoreAbstractParameter()
{
    if (v.canConvert<dtkCoreParameterInList<T>>()) {
        *this = v.value<dtkCoreParameterInList<T>>();

    } else if (v.canConvert<T>()) {
        m_values << v.value<T>();
        m_value_index = 0;
    }
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const dtkCoreParameterInList& o) : dtkCoreAbstractParameter(o.m_doc), m_values(o.m_values), m_value_index(o.m_value_index)
{

}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const T& t, const QList<T>& values, const QString& doc) : dtkCoreAbstractParameter(doc), m_values(values)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    m_value_index = m_values.indexOf(t);
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(int index, const QList<T>& values, const QString& doc) : dtkCoreAbstractParameter(doc), m_values(values), m_value_index(index)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
    Q_ASSERT_X(((index > -1) && (index < values.size())), Q_FUNC_INFO, "Input index is out of range");
}

template <typename T>
inline dtkCoreParameterInList<T>::dtkCoreParameterInList(const QList<T>& values, const QString& doc) : dtkCoreAbstractParameter(doc), m_values(values), m_value_index(0)
{
    Q_ASSERT_X(!m_values.empty(), Q_FUNC_INFO, "Input list cannot be empty");
}

template <typename T>
inline dtkCoreParameterInList<T>& dtkCoreParameterInList<T>::operator = (const dtkCoreParameterInList& o)
{
    if (this != &o) {
        m_doc = o.m_doc;
        m_values = o.m_values;
        m_value_index = o.m_value_index;
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
        emit invalidValue();

    } else {
        m_value_index = index;
        emit valueChanged(this->variant());
    }
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValue(const T& t)
{
    int index = m_values.indexOf(t);
    if (index < 0) {
        dtkWarn() << Q_FUNC_INFO << "Value index (" << index << ") is out of range [" << 0 << "," << m_values.size()-1 << "]";
        emit invalidValue();

    } else {
        m_value_index = index;
        emit valueChanged(this->variant());
    }
}

template <typename T>
inline void dtkCoreParameterInList<T>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterInList<T>>()) {
        *this = v.value<dtkCoreParameterInList<T>>();
        emit valueChanged(this->variant());

    } else if (v.canConvert<T>()) {
        int index = m_values.indexOf(v.value<T>());
        if (index < 0) {
            dtkWarn() << Q_FUNC_INFO << "Value is not part of the admissible ones.";
            emit invalidValue();

        } else {
            m_value_index = index;
            emit valueChanged(this->variant());
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterInList<T>>())
                  << ". Nothing is done.";
        emit invalidValue();
    }
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
inline QVariant dtkCoreParameterInList<T>::variant(void) const
{
    return dtk::variantFromValue(*this);
}

//
// dtkCoreParameter.tpp ends here
