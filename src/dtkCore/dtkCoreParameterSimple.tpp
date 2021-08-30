// dtkCoreParameterSimple.tpp
//

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter simple version implementation
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable>
inline dtkCoreParameterSimple<T, Enable>::dtkCoreParameterSimple(const dtkCoreParameter *p) : dtkCoreParameterBase<dtkCoreParameterSimple>()
{
    if (!p) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter is null. Nothing is done.";
        return;
    }
    *this = p->variant();
}

template <typename T, typename Enable>
inline dtkCoreParameterSimple<T, Enable>::dtkCoreParameterSimple(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterSimple>()
{
    if (v.canConvert<dtkCoreParameterSimple>()) {
        auto o(v.value<dtkCoreParameterSimple>());
        *this = o;

    } else if (v.canConvert<T>()) {
        m_value = v.value<T>();
    }
}

template <typename T, typename Enable>
inline dtkCoreParameterSimple<T, Enable>::dtkCoreParameterSimple(const dtkCoreParameterSimple& o) : dtkCoreParameterBase<dtkCoreParameterSimple>(o), m_value(o.m_value)
{

}

template <typename T, typename Enable>
inline dtkCoreParameterSimple<T, Enable>::dtkCoreParameterSimple(const QString& label, const T& t, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterSimple>(label, doc), m_value(t)
{

}

template <typename T, typename Enable>
inline auto dtkCoreParameterSimple<T, Enable>::operator = (const T& t) -> dtkCoreParameterSimple&
{
    m_value = t;
    this->sync();
    return *this;
}

template <typename T, typename Enable>
inline auto dtkCoreParameterSimple<T, Enable>::operator = (const dtkCoreParameter *p) -> dtkCoreParameterSimple&
{
    if (!p) {
        dtkWarn() << Q_FUNC_INFO << "Input parameter is null. Nothing is done.";
        return *this;
    }
    return *this = p->variant();
}

template <typename T, typename Enable>
inline auto dtkCoreParameterSimple<T, Enable>::operator = (const QVariant& v) -> dtkCoreParameterSimple&
{
    if (v.canConvert<dtkCoreParameterSimple<T, Enable>>()) {
        *this = v.value<dtkCoreParameterSimple<T, Enable>>();

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
inline auto dtkCoreParameterSimple<T, Enable>::operator = (const dtkCoreParameterSimple& o) -> dtkCoreParameterSimple&
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
inline dtkCoreParameterSimple<T, Enable>::operator T() const
{
    return m_value;
}

template <typename T, typename Enable>
inline void dtkCoreParameterSimple<T, Enable>::setValue(const T& t)
{
    if (m_value != t) {
        m_value = t;
        this->sync();
    }
}

template <typename T, typename Enable>
inline void dtkCoreParameterSimple<T, Enable>::setValue(const QVariant &v)
{
    if (v.canConvert<dtkCoreParameterSimple>()) {
        *this = v.value<dtkCoreParameterSimple>();

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
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterSimple<T, Enable>>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}


template <typename T, typename Enable>
inline QVariantHash dtkCoreParameterSimple<T, Enable>::toVariantHash(void) const
{
    QVariantHash hash = base_type::toVariantHash();
    hash.insert("value", QVariant::fromValue(m_value));

    return hash;
}

template <typename T, typename Enable>
inline T dtkCoreParameterSimple<T, Enable>::value(void) const
{
    return m_value;
}

template <typename T>
inline QDataStream& operator << (QDataStream& s, const dtkCoreParameterSimple<T>& p)
{
    s << p.label();
    s << p.value();
    s << p.documentation();

    return s;
}

template <typename T>
inline QDataStream& operator >> (QDataStream& s, dtkCoreParameterSimple<T>& p)
{
    QString label; s >> label;
    T t; s >> t;
    QString doc; s >> doc;

    p = dtkCoreParameterSimple<T>(label, t, doc);
    return s;
}

template <typename T>
inline QDebug operator << (QDebug dbg, dtkCoreParameterSimple<T> p)
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

//
// dtkCoreParameterSimple.tpp ends here
