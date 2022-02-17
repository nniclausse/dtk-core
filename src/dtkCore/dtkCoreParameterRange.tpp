// dtkCoreParameterRange.tpp
//

#include "dtkCoreParameterRangeObject.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterRange implementation
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange() : dtkCoreParameterBase<dtkCoreParameterRange>()
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::~dtkCoreParameterRange(void)
{
    delete m_object;
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(const std::array<T, 2>& t) : dtkCoreParameterBase<dtkCoreParameterRange>()
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
    if (t[0] <= t[1]) {
        m_val = t;

    } else {
        dtkWarn() << Q_FUNC_INFO << "Input values are not in increasing order. Nothing is done.";
    }
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(std::initializer_list<T> args) : dtkCoreParameterBase<dtkCoreParameterRange>()
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
    if (args.size() != 2) {
        dtkWarn() << Q_FUNC_INFO << "Wrong number of input values:" << args.size() << "instead of" << 2 << ". Nothing is done";
        this->syncFail();

    } else {
        auto v_min = *(args.begin());
        auto v_max = *(args.begin()+1);
        if (v_min <= v_max) {
            m_val[0] = v_min;
            m_val[1] = v_max;
        } else {
            dtkWarn() << Q_FUNC_INFO << "Input values are not in increasing order:" << v_min << ">" << v_max << ". Nothing is done.";
        }
    }
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterRange>()
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
    if (v.canConvert<dtkCoreParameterRange>()) {
        auto o(v.value<dtkCoreParameterRange>());
        *this = o;

    } else if (v.canConvert<std::array<T, 2>>()) {
        auto t = v.value<std::array<T, 2>>();
        if (t[0] <= t[1]) {
            m_val = t;
        } else {
            dtkWarn() << Q_FUNC_INFO << "Input values are not in increasing order. Nothing is done.";
        }
    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterRange>())
                  << ". Nothing is done.";
    }
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(const dtkCoreParameterRange& o) : dtkCoreParameterBase<dtkCoreParameterRange>(o), m_val(o.m_val), m_bounds(o.m_bounds), m_decimals(o.m_decimals)
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(const QString& label, const std::array<T, 2>& t, const T& min, const T& max, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterRange>(label, doc)
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
    if (min <= t[0] && t[0] <= t[1] && t[1] <= max) {
        m_val = t;
        m_bounds = {min , max};

    } else {
        dtkWarn() << Q_FUNC_INFO << "Input values and bounds are not correctly ordered. Nothing is done.";
    }
}

template <typename T, typename E> template <typename U, typename>
inline dtkCoreParameterRange<T, E>::dtkCoreParameterRange(const QString& label, const std::array<T, 2>& t, const T& min, const T& max, const int& decimals, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterRange>(label, doc)
{
    m_object = new dtkCoreParameterRangeObject<T>(this);
    if (min <= t[0] && t[0] <= t[1] && t[1] <= max) {
        m_val = t;
        m_bounds = {min , max};
        m_decimals = decimals;

    } else {
        dtkWarn() << Q_FUNC_INFO << "Input values and bounds are not correctly ordered. Nothing is done.";
    }
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>& dtkCoreParameterRange<T, E>::operator = (const std::array<T, 2>& t)
{
    if (m_bounds[0] <= t[0] && t[0] <= t[1] && t[1] <= m_bounds[1]) {
        m_val = t;
        this->sync();
        m_object->notifyRmin(m_val[0]);
        m_object->notifyRmax(m_val[1]);

    } else {
        dtkWarn() << Q_FUNC_INFO << "Values (" << t[0] << "," << t[1] << ") not setted because not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();
    }
    return *this;
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>& dtkCoreParameterRange<T, E>::operator = (std::initializer_list<T> args)
{
    if (args.size() != 2) {
        dtkWarn() << Q_FUNC_INFO << "Wrong number of input values:" << args.size() << "instead of" << 2 << ". Nothing is done";
        this->syncFail();

    } else {
        auto v_min = *(args.begin());
        auto v_max = *(args.begin()+1);
        if (m_bounds[0] <= v_min && v_min <= v_max && v_max <= m_bounds[1]) {
            m_val[0] = v_min;
            m_val[1] = v_max;
            this->sync();
            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);

        } else {
            dtkWarn() << Q_FUNC_INFO << "Input values not setted because they are not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            this->syncFail();
        }
    }
    return *this;
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>& dtkCoreParameterRange<T, E>::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterRange>()) {
        auto o(v.value<dtkCoreParameterRange>());
        *this = o;

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        T min, max;
        if (map.contains("min")) min = map["min"].value<T>();
        else                     min = std::numeric_limits<T>::lowest();

        if (map.contains("max")) max = map["max"].value<T>();
        else                     max = std::numeric_limits<T>::max();

        auto list = map["values"].toList();
        auto v_min = list[0].value<T>();
        auto v_max = list[1].value<T>();

        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);

        if (min <= v_min && v_min <= v_max && v_max <= max) {
            m_bounds = {min, max};
            m_val = {v_min, v_max};
            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);
            m_object->notifyMin(min);
            m_object->notifyMax(max);

        } else {
            dtkWarn() << Q_FUNC_INFO << "Values and bouns in VariantHash are not correctly ordered. Nothing is done";
            this->syncFail();
            return *this;
        }

    } else if (v.canConvert<std::array<T, 2>>()) {
        auto t = v.value<std::array<T, 2>>();
         if (m_bounds[0] <= t[0] && t[0] <= t[1] && t[1] <= m_bounds[1]) {
            m_val = t;
            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);

         } else {
             dtkWarn() << Q_FUNC_INFO << "Values (" << t[0] << "," << t[1] << ") not setted because not correctly ordred or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
             this->syncFail();
             return *this;
         }
    }
    this->sync();
    return *this;
}

template <typename T, typename E>
inline dtkCoreParameterRange<T, E>& dtkCoreParameterRange<T, E>::operator = (const dtkCoreParameterRange& o)
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_val = o.m_val;
        m_bounds = o.m_bounds;
        m_decimals = o.m_decimals;
        this->sync();

        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);
        m_object->notifyRmin(m_val[0]);
        m_object->notifyRmax(m_val[1]);
        m_object->notifyMin(m_bounds[0]);
        m_object->notifyMax(m_bounds[1]);
        m_object->notifyDecimals(m_decimals);

    }
    return *this;
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setRange(const std::array<T, 2>& t)
{
    if (m_bounds[0] <= t[0] && t[0] <= t[1] && t[1] <= m_bounds[1]) {
        m_val = t;
        this->sync();
        m_object->notifyRmin(m_val[0]);
        m_object->notifyRmax(m_val[1]);

    } else {
        dtkWarn() << Q_FUNC_INFO << "Values (" << t[0] << "," << t[1] << ") not setted because not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();
    }
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setRange(std::initializer_list<T> args)
{
    if (args.size() != 2) {
        dtkWarn() << Q_FUNC_INFO << "Wrong number of input values:" << args.size() << "instead of" << 2 << ". Nothing is done";
        this->syncFail();

    } else {
        auto v_min = *(args.begin());
        auto v_max = *(args.begin()+1);
        if (m_bounds[0] <= v_min && v_min <= v_max && v_max <= m_bounds[1]) {
            m_val[0] = v_min;
            m_val[1] = v_max;
            this->sync();
            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);

        } else {
            dtkWarn() << Q_FUNC_INFO << "Input values not setted because they are not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
            this->syncFail();
        }
    }
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setRange(const T& t1, const T& t2)
{
    this->setRange({t1, t2});
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setValue(const std::array<T, 2>& t)
{
    this->setRange(t);
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setValue(std::initializer_list<T> args)
{
    this->setRange(args);
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterRange>()) {
        *this = v.value<dtkCoreParameterRange>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_object->notifyLabel(m_label);
        m_object->notifyDoc(m_doc);

        T min, max;
        if (map.contains("min")) min = map["min"].value<T>();
        else                     min = std::numeric_limits<T>::lowest();

        if (map.contains("max")) max = map["max"].value<T>();
        else                     max = std::numeric_limits<T>::max();

        if (map.contains("decimals")) {
            m_decimals = map["decimals"].value<int>();
            m_object->notifyDecimals(m_decimals);
        }

        auto list = map["values"].toList();
        auto v_min = list[0].value<T>();
        auto v_max = list[1].value<T>();

        if (min <= v_min && v_min <= v_max && v_max <= max) {
            m_bounds = {min, max};
            m_val = {v_min, v_max};

            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);
            m_object->notifyMin(m_bounds[0]);
            m_object->notifyMax(m_bounds[1]);

        } else {
            dtkWarn() << Q_FUNC_INFO << "Values and bouns in VariantHash are not correctly ordered. Nothing is done";
            this->syncFail();
            return;
        }

    } else if (v.canConvert<std::array<T, 2>>()) {
        auto t = v.value<std::array<T, 2>>();
         if (m_bounds[0] <= t[0] && t[0] <= t[1] && t[1] <= m_bounds[1]) {
            m_val = t;
            m_object->notifyRmin(m_val[0]);
            m_object->notifyRmax(m_val[1]);

         } else {
             dtkWarn() << Q_FUNC_INFO << "Values (" << t[0] << "," << t[1] << ") not setted because not correctly ordred or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
             this->syncFail();
             return;
         }
    }
    this->sync();
}

template <typename T, typename E>
inline const std::array<T, 2>& dtkCoreParameterRange<T, E>::value(void) const
{
    return m_val;
}

template <typename T, typename E>
inline auto dtkCoreParameterRange<T, E>::operator[](int id) const -> value_type
{
    return m_val[id];
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setValueMax(const T& vmax)
{
    if(vmax <= m_bounds[1] && vmax >= m_bounds[0] && vmax >= m_val[0]) {
        m_val[1] = vmax;
        this->sync();
        m_object->notifyRmax(m_val[1]);
    }
    else {
        dtkWarn() << Q_FUNC_INFO << "Value max (" << vmax << ") not setted because not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();
    }
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setValueMin(const T& vmin)
{
    //dtkWarn() << Q_FUNC_INFO << "value is " << vmin;
    if(vmin >= m_bounds[0] && vmin <= m_bounds[1] && vmin <= m_val[1]) {
        m_val[0] = vmin;
        this->sync();
        m_object->notifyRmin(m_val[0]);
    }
    else {
        dtkWarn() << Q_FUNC_INFO << "Value min (" << vmin << ") not setted because not correctly ordered or out of bounds [" << m_bounds[0] << "," << m_bounds[1] << "]";
        this->syncFail();
    }
}

template <typename T, typename E>
inline T dtkCoreParameterRange<T, E>::min(void) const
{
    return m_bounds[0];
}

template <typename T, typename E>
inline T dtkCoreParameterRange<T, E>::max(void) const
{
    return m_bounds[1];
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setMin(const T& min)
{
    if (this->m_bounds[0] == min)
        return;

    if (min > this->m_bounds[1]) {
        dtkWarn() << Q_FUNC_INFO << "Input min bound is greater than max bound:" << min << ">" << m_bounds[1] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[0] = min;
    m_object->notifyMin(m_bounds[0]);
    if (m_val[0] < min) {
        m_val[0] = min;
        if (m_val[0] > m_val[1]) {
            m_val[1] = m_val[0];
            m_object->notifyRmax(m_val[1]);

        }
        m_object->notifyRmin(m_val[0]);
    }
    this->sync();
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setMax(const T& max)
{
    if (this->m_bounds[1] == max)
        return;

    if (max < this->m_bounds[0]) {
        dtkWarn() << Q_FUNC_INFO << "Input max bound is lower than min bound:" << max << "<" << m_bounds[0] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[1] = max;
    m_object->notifyMax(max);
    if (m_val[1] > max) {
        m_val[1] = max;
        if (m_val[1] < m_val[0]) {
            m_val[0] = m_val[1];
            m_object->notifyRmin(m_val[0]);
        }
        m_object->notifyRmax(m_val[1]);
    }
    this->sync();
}

template <typename T, typename E>
inline const std::array<T, 2>& dtkCoreParameterRange<T, E>::bounds(void) const
{
    return m_bounds;
}

template <typename T, typename E>
inline void dtkCoreParameterRange<T, E>::setBounds(const std::array<T, 2>& b)
{
    if (b[0] > b[1]) {
        dtkWarn() << Q_FUNC_INFO << "Input bounds are not correctly ordered:" << b[0] << ">" << b[1] << ". Nothing is done.";
        this->syncFail();
        return;
    }

    this->m_bounds[0] = b[0];
    if (m_val[0] < b[0]) {
        m_val[0] = b[0];
        if (m_val[0] > m_val[1]) {
            m_val[1] = m_val[0];
        }
    }

    this->m_bounds[1] = b[1];
    if (m_val[1] > b[1]) {
        m_val[1] = b[1];
        if (m_val[1] < m_val[0]) {
            m_val[0] = m_val[1];
        }
    }
    m_object->notifyRmin(m_val[0]);
    m_object->notifyRmax(m_val[1]);
    this->sync();
}

template <typename T, typename E>
template <typename U>
inline std::enable_if_t<std::is_floating_point<U>::value> dtkCoreParameterRange<T, E>::setDecimals(const int& decimals)
{
    m_decimals = decimals;
    m_object->notifyDecimals(m_decimals);
}

template <typename T, typename E>
inline int dtkCoreParameterRange<T, E>::decimals(void) const
{
    return m_decimals;
}

template <typename T, typename E>
inline QVariantHash dtkCoreParameterRange<T, E>::toVariantHash(void) const
{
    QVariantHash hash = base_type::toVariantHash();
    QList<QVariant> ll = {QVariant(m_val[0]), QVariant(m_val[1])};
    hash.insert("values", ll);
    hash.insert("min", m_bounds[0]);
    hash.insert("max", m_bounds[1]);
    hash.insert("decimals", m_decimals);

    return hash;
}

template <typename T, typename E>
inline dtkCoreParameterObject *dtkCoreParameterRange<T, E>::object(void)
{
    return this->m_object;
}

template <typename T>
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterRange<T>& p)
{
    s << p.label();
    s << p.value()[0];
    s << p.value()[1];
    s << p.min();
    s << p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

template <typename T, typename E>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterRange<T>& p)
{
    QString label; s >> label;
    T v_min; s >> v_min;
    T v_max; s >> v_max;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    std::array<T, 2> val = {v_min, v_max};

    p = dtkCoreParameterRange<T>(label, val, min, max, dec, doc);
    return s;
}

template <typename T, typename E, typename U>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterRange<T>& p)
{
    QString label; s >> label;
    T v_min; s >> v_min;
    T v_max; s >> v_max;
    T min; s >> min;
    T max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    std::array<T, 2> val = {v_min, v_max};

    p = dtkCoreParameterRange<T>(label, val, min, max, doc);
    return s;
}

inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterRange<char>& p)
{
    s << p.label();
    s << (qint8)p.value()[0];
    s << (qint8)p.value()[1];
    s << (qint8)p.min();
    s << (qint8)p.max();
    s << p.decimals();
    s << p.documentation();

    return s;
}

inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterRange<char>& p)
{
    QString label; s >> label;
    qint8 v_min; s >> v_min;
    qint8 v_max; s >> v_max;
    qint8 min; s >> min;
    qint8 max; s >> max;
    int dec; s >> dec;
    QString doc; s >> doc;

    std::array<char, 2> val = {(char)v_min, (char)v_max};

    p = dtkCoreParameterRange<char>(label, val, (char)min, (char)max, doc);
    return s;
}

template <typename T>
inline QDebug operator << (QDebug dbg, dtkCoreParameterRange<T> p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "values ["
                  << p.value()[0] << ","
                  << p.value()[1] << "], "
                  << "bounds ["
                  << p.min() << ","
                  << p.max() << "], "
                  << "decimals" << p.decimals() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

//
// dtkCoreParameterRange.tpp ends here
