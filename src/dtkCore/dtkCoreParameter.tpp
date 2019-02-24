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

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const T& t) : dtkCoreAbstractParameter(), m_val(t)
{
    emit valueChanged();
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const QVariant& v) : dtkCoreAbstractParameter()
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
         *this = v.value<dtkCoreParameter<T>>();
    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();
    }
    emit valueChanged();
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const dtkCoreParameter& o) : dtkCoreAbstractParameter(o), m_val(o.m_val), m_bounds(o.m_bounds), m_decimals(o.m_decimals)
{
    emit valueChanged();
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(dtkCoreParameter&& o) : dtkCoreAbstractParameter(o), m_val(std::move(o.m_val)), m_bounds(std::move(o.m_bounds)), m_decimals(std::move(o.m_decimals))
{
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const T& t, const T& min, const T& max, const QString& doc) : dtkCoreAbstractParameter(doc), m_val(t), m_bounds({min, max})
{
    emit valueChanged();
}

template <typename T, typename Enable> template <typename U, typename>
inline dtkCoreParameter<T, Enable>::dtkCoreParameter(const T& t, const T& min, const T& max, const int& decimals, const QString& doc) : dtkCoreAbstractParameter(doc), m_val(t), m_bounds({min, max}), m_decimals(decimals)
{
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator = (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    if (t != m_val) {
        m_val = t;
        emit valueChanged();
    }
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
         *this = v.value<dtkCoreParameter<T>>();
         emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        if (t != m_val) {
            m_val = t;
            emit valueChanged();
        }
    }
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator = (const dtkCoreParameter& o) -> dtkCoreParameter&
{
    if (this != &o) {
        m_val = o.m_val;
        m_bounds = o.m_bounds;
        m_decimals = o.m_decimals;
        emit valueChanged();
    }

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator = (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    T t = o;
    if (t != m_val) {
        m_val = t;
        emit valueChanged();
    }

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator += (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += t;
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator += (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        m_val += t;
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        m_val += t;
        emit valueChanged();
    }
    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator += (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val += (T)(o);
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator -= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= t;
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator -= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        m_val -= t;
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        m_val -= t;
        emit valueChanged();
    }
    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator -= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val -= (T)(o);
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator *= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= t;
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator *= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        m_val *= t;
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        m_val *= t;
        emit valueChanged();
    }
    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator *= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val *= (T)(o);
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator /= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= t;
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameter<T, Enable>::operator /= (const QVariant& v) -> dtkCoreParameter&
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        m_val /= t;
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        m_val /= t;
        emit valueChanged();
    }
    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator /= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&>
{
    m_val /= (T)(o);
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator %= (const U& t) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= t;
    emit valueChanged();

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator %= (const QVariant& v) -> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameter&>
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        m_val %= t;
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        m_val %= t;
        emit valueChanged();
    }

    return *this;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator %= (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&>
{
    m_val %= (T)(o);
    emit valueChanged();

    return *this;
}


template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator == (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == t);
}

template <typename T, typename Enable>
inline bool dtkCoreParameter<T, Enable>::operator == (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        return (m_val == t);

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        return (m_val == t);
    }
    return false;
}

template <typename T, typename Enable> template <typename U>
inline auto  dtkCoreParameter<T, Enable>::operator == (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == (T)(o));
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator != (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != t);
                   }

template <typename T, typename Enable>
inline bool dtkCoreParameter<T, Enable>::operator != (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        T t = v.value<dtkCoreParameter<T>>();
        return (m_val != t);

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        return (m_val != t);
    }
    return true;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::operator != (const dtkCoreParameter<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != (T)(o));
}

template <typename T, typename Enable>
inline dtkCoreParameter<T, Enable>::operator T() const
{
    return m_val;
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setValue(const T& t)
{
    if (t != m_val) {
        m_val = t;
        emit valueChanged();
    }
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameter<T>>()) {
        *this = v.value<dtkCoreParameter<T>>();
        emit valueChanged();

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();
        if (t != m_val) {
            m_val = t;
            emit valueChanged();
        }
    }
}

template <typename T, typename Enable>
inline T dtkCoreParameter<T, Enable>::value(void) const
{
    return m_val;
}

template <typename T, typename Enable>
inline QVariant dtkCoreParameter<T, Enable>::variant(void) const
{
    return dtk::variantFromValue(*this);
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setMinimum(const T& t)
{
    this->m_bounds[0] = t;
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setMaximum(const T& t)
{
    this->m_bounds[1] = t;
}

template <typename T, typename Enable>
inline T dtkCoreParameter<T, Enable>::min(void) const
{
    return this->m_bounds[0];
}

template <typename T, typename Enable>
inline T dtkCoreParameter<T, Enable>::max(void) const
{
    return this->m_bounds[1];
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setBounds(const T& min, const T& max)
{
    this->m_bounds[0] = min;
    this->m_bounds[1] = max;
}

template <typename T, typename Enable>
inline void dtkCoreParameter<T, Enable>::setBounds(const std::array<T, 2>& r)
{
    this->m_bounds = r;
}

template <typename T, typename Enable>
inline const std::array<T, 2>& dtkCoreParameter<T, Enable>::bounds(void) const
{
    return this->m_bounds;
}

template <typename T, typename Enable> template <typename U>
inline auto dtkCoreParameter<T, Enable>::setDecimals(const int& d) -> std::enable_if_t<std::is_floating_point<U>::value>
{
    this->m_decimals = d;
}

template <typename T, typename Enable>
inline int dtkCoreParameter<T, Enable>::decimals(void) const
{
    return this->m_decimals;
}

template <typename T, typename Enable>
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameter<T, Enable>& p)
{
    s << p.value();
    s << p.min();
    s << p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

template <typename T, typename Enable, typename B>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T, Enable>& p)
{
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p.setValue(val);
    p.setBounds(min, max);
    p.setDecimals(dec);
    p.setDocumentation(doc);

    return s;
}

template <typename T, typename Enable, typename B, typename U>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameter<T, Enable>& p)
{
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p.setValue(val);
    p.setBounds(min, max);
    p.setDocumentation(doc);

    return s;
}

template <typename T, typename Enable>
inline QDebug& operator << (QDebug& dbg, dtkCoreParameter<T, Enable> p)
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

//
// dtkCoreParameter.tpp ends here
