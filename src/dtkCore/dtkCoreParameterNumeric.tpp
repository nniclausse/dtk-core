// dtkCoreParameterNumeric.tpp
//

#include "dtkCoreParameterNumericObject.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterNumeric for numerical types implementation
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(void) : dtkCoreParameterBase<dtkCoreParameterNumeric>()
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::~dtkCoreParameterNumeric(void)
{
    delete m_object;
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const T& t) : dtkCoreParameterBase<dtkCoreParameterNumeric>(), m_val(t)
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E> template < typename U, typename V>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const U *p) : dtkCoreParameterBase<dtkCoreParameterNumeric>()
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
    if (!p) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter is null. Nothing is done.";
        return;
    }
    *this = p->variant();
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterNumeric>()
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this = v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<T>()) {
        m_val = v.value<T>();
    }
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const dtkCoreParameterNumeric& o) : dtkCoreParameterBase<dtkCoreParameterNumeric>(o), m_val(o.m_val), m_bounds(o.m_bounds), m_decimals(o.m_decimals)
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const QString& label, const T& t, const T& min, const T& max, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterNumeric>(label, doc), m_val(t), m_bounds({min, max})
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E> template <typename U, typename>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const QString& label, const T& t, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterNumeric>(label, doc), m_val(t)
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E> template <typename U, typename>
inline dtkCoreParameterNumeric<T, E>::dtkCoreParameterNumeric(const QString& label, const T& t, const T& min, const T& max, const int& decimals, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterNumeric>(label, doc), m_val(t), m_bounds({min, max}), m_decimals(decimals)
{
    m_object = new dtkCoreParameterNumericObject<T>(this);
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator = (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val = t;
    this->sync();
    m_object->notifyValue(m_val);
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator = (const U *p) -> dtk::is_core_parameter<U, dtkCoreParameterNumeric&>
{
    if (!p) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter is null. Nothing is done.";
        return *this;
    }
    return *this = p->variant();
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator = (const QVariant& v) -> dtkCoreParameterNumeric&
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this = v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_val = map["value"].value<T>();
        if(map.contains("min")) m_bounds[0] = map["min"].value<T>();
        else                    m_bounds[0] = std::numeric_limits<T>::lowest();

        if(map.contains("max")) m_bounds[1] = map["max"].value<T>();
        else                    m_bounds[1] = std::numeric_limits<T>::max();

        if (map.contains("decimals")) {
            m_decimals = map["decimals"].value<int>();
        }
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyValue(m_val);
        m_object->notifyMin(m_bounds[0]);
        m_object->notifyMax(m_bounds[1]);
        m_object->notifyDecimals(m_decimals);

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();

        if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
            dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            this->syncFail();
            return *this;

        } else if (t != m_val) {
            m_val = t;
            m_object->notifyValue(m_val);
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterNumeric>())
        << ". Nothing is done." << v;
        this->syncFail();
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator = (const dtkCoreParameterNumeric& o) -> dtkCoreParameterNumeric&
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_val = o.m_val;
        m_bounds = o.m_bounds;
        m_decimals = o.m_decimals;
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyValue(m_val);
        m_object->notifyMin(m_bounds[0]);
        m_object->notifyMax(m_bounds[1]);
        m_object->notifyDecimals(m_decimals);
        this->sync();
    }
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator = (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val = (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator += (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val += t;
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator += (const QVariant& v) -> dtkCoreParameterNumeric&
{
    if (v.canConvert<dtkCoreParameterNumeric<T, E>>()) {
        *this += v.value<dtkCoreParameterNumeric<T, E>>();

    } else if (v.canConvert<T>()) {
        m_val += v.value<T>();
        m_object->notifyValue(m_val);

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator += (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val += (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator -= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val -= t;
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator -= (const QVariant& v) -> dtkCoreParameterNumeric&
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this -= v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<T>()) {
        m_val -= v.value<T>();
        m_object->notifyValue(m_val);

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator -= (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val -= (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator *= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val *= t;
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator *= (const QVariant& v) -> dtkCoreParameterNumeric&
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this *= v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<T>()) {
        m_val *= v.value<T>();
        m_object->notifyValue(m_val);

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator *= (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val *= (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator /= (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val /= t;
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E>
inline auto dtkCoreParameterNumeric<T, E>::operator /= (const QVariant& v) -> dtkCoreParameterNumeric&
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this /= v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<T>()) {
        m_val /= v.value<T>();
        m_object->notifyValue(m_val);

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator /= (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameterNumeric&>
{
    m_val /= (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator %= (const U& t) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameterNumeric&>
{
    m_val %= t;
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator %= (const QVariant& v) -> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameterNumeric&>
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this %= v.value<dtkCoreParameterNumeric>();

    } else if (v.canConvert<T>()) {
        m_val %= v.value<T>();
        m_object->notifyValue(m_val);

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator %= (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameterNumeric&>
{
    m_val %= (T)(o);
    m_object->notifyValue(m_val);
    this->sync();
    return *this;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator == (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == t);
}

template <typename T, typename E>
inline bool dtkCoreParameterNumeric<T, E>::operator == (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        return (*this == v.value<dtkCoreParameterNumeric>());

    } else if (v.canConvert<T>()) {
        return (m_val == v.value<T>());
    }
    return false;
}

template <typename T, typename E> template <typename U>
inline auto  dtkCoreParameterNumeric<T, E>::operator == (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val == (T)(o));
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator != (const U& t) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != t);
}

template <typename T, typename E>
inline bool dtkCoreParameterNumeric<T, E>::operator != (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        return (*this != v.value<dtkCoreParameterNumeric>());

    } else if (v.canConvert<T>()) {
        return (m_val != v.value<T>());
    }
    return true;
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::operator != (const dtkCoreParameterNumeric<U>& o) -> std::enable_if_t<std::is_arithmetic<U>::value, bool>
{
    return (m_val != (T)(o));
}

template <typename T, typename E>
inline dtkCoreParameterNumeric<T, E>::operator T() const
{
    return m_val;
}

template <typename T, typename E>
inline void dtkCoreParameterNumeric<T, E>::setValue(const T& t)
{
    if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
        dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();

    } else if (t != m_val) {
        m_val = t;
        m_object->notifyValue(m_val);
        this->sync();
    }
}

template <typename T, typename E>
inline void dtkCoreParameterNumeric<T, E>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterNumeric>()) {
        *this = v.value<dtkCoreParameterNumeric>();
        // value is copied, do not check bounds

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();
        m_val = map["value"].value<T>();

        if(map.contains("min")) m_bounds[0] = map["min"].value<T>();
        else                    m_bounds[0] = std::numeric_limits<T>::lowest();

        if(map.contains("max")) m_bounds[1] = map["max"].value<T>();
        else                    m_bounds[1] = std::numeric_limits<T>::max();

        if (map.contains("decimals")) {
            m_decimals = map["decimals"].value<int>();
        }
        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyValue(m_val);
        m_object->notifyMin(m_bounds[0]);
        m_object->notifyMax(m_bounds[1]);
        m_object->notifyDecimals(m_decimals);

    } else if (v.canConvert<T>()) {
        T t = v.value<T>();

        if (( t < m_bounds[0] ) || ( t > m_bounds[1] )) {
            dtkWarn() << Q_FUNC_INFO << "Value (" << t << ") not setted because out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            this->syncFail();
            return;

        } else if (t != m_val) {
            m_val = t;
            m_object->notifyValue(m_val);
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterNumeric>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}

template <typename T, typename E>
inline QVariantHash dtkCoreParameterNumeric<T, E>::toVariantHash(void) const
{
    QVariantHash hash = base_type::toVariantHash();
    hash.insert("value", m_val);
    hash.insert("min", m_bounds[0]);
    hash.insert("max", m_bounds[1]);
    hash.insert("decimals", m_decimals);

    return hash;
}


template <typename T, typename E>
inline T dtkCoreParameterNumeric<T, E>::value(void) const
{
    return m_val;
}

template <typename T, typename E>
inline T dtkCoreParameterNumeric<T, E>::min(void) const
{
    return this->m_bounds[0];
}

template <typename T, typename E>
inline T dtkCoreParameterNumeric<T, E>::max(void) const
{
    return this->m_bounds[1];
}

template <typename T, typename E>
inline void dtkCoreParameterNumeric<T, E>::setMin(const T& min)
{
    if (this->m_bounds[0] == min)
        return;

    if (min > this->m_bounds[1]) {
        dtkWarn() << Q_FUNC_INFO << "Input min bound is greater than max bound:" << min << ">" << m_bounds[1] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[0] = min;
    if (m_val < min) {
        m_val = min;
        m_object->notifyValue(m_val);
    }
    m_object->notifyMin(m_bounds[0]);
    this->sync();
}

template <typename T, typename E>
inline void dtkCoreParameterNumeric<T, E>::setMax(const T& max)
{
    if (this->m_bounds[1] == max)
        return;

    if (max < this->m_bounds[0]) {
        dtkWarn() << Q_FUNC_INFO << "Input max bound is lower than min bound:" << max << "<" << m_bounds[0] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[1] = max;
    if (m_val > max) {
        m_val = max;
        m_object->notifyValue(m_val);
    }
    m_object->notifyMax(m_bounds[1]);
    this->sync();
}

template <typename T, typename E>
inline const std::array<T, 2>& dtkCoreParameterNumeric<T, E>::bounds(void) const
{
    return this->m_bounds;
}

template <typename T, typename E>
inline void dtkCoreParameterNumeric<T, E>::setBounds(const std::array<T, 2>& b)
{
    if (b[0] > b[1]) {
        dtkWarn() << Q_FUNC_INFO << "Input bounds are not correctly ordered:" << b[0] << ">" << b[1] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[0] = b[0];
    if (m_val < b[0]) {
        m_val = b[0];
        m_object->notifyValue(m_val);
    }

    this->m_bounds[1] = b[1];
    if (m_val > b[1]) {
        m_val = b[1];
        m_object->notifyValue(m_val);
    }
    m_object->notifyMin(m_bounds[0]);
    m_object->notifyMax(m_bounds[1]);
    this->sync();
}

template <typename T, typename E> template <typename U>
inline auto dtkCoreParameterNumeric<T, E>::setDecimals(const int& d) -> std::enable_if_t<std::is_floating_point<U>::value>
{
    this->m_decimals = d;
}

template <typename T, typename E>
inline int dtkCoreParameterNumeric<T, E>::decimals(void) const
{
    return this->m_decimals;
}

template <typename T>
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterNumeric<T>& p)
{
    s << p.label();
    s << p.value();
    s << p.min();
    s << p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

template <typename T, typename E>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterNumeric<T>& p)
{
    QString label; s >> label;
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameterNumeric<T>(label, val, min, max, dec, doc);
    return s;
}

template <typename T, typename E, typename U>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterNumeric<T>& p)
{
    QString label; s >> label;
    T val; s >> val;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameterNumeric<T>(label, val, min, max, doc);
    return s;
}

inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterNumeric<char>& p)
{
    s << p.label();
    s << (qint8)p.value();
    s << (qint8)p.min();
    s << (qint8)p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterNumeric<char>& p)
{
    QString label; s >> label;
    qint8 val; s >> val;
    qint8 min; s >> min;
    qint8 max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    p = dtkCoreParameterNumeric<char>(label, (char)val, (char)min, (char)max, doc);
    return s;
}

template <typename T>
inline QDebug operator << (QDebug dbg, dtkCoreParameterNumeric<T> p)
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

//
// dtkCoreParameterNumeric.tpp ends here
