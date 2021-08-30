// dtkCoreParameter.tpp
//

#include "dtkCoreMetaType.h"

// ///////////////////////////////////////////////////////////////////
// MetaType covariance
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    namespace detail
    {
        // Custom fallback to create QVariant from dtkCoreParameter
        template <typename T>
        struct variant_handler<T, dtk::is_core_parameter<T>, std::enable_if_t<!std::is_pointer<T>::value>>
        {
            static QVariant fromValue(const T& t) {
                int class_type = QMetaType::type(qPrintable(t.typeName()));
                if (class_type == QMetaType::UnknownType) {
                    return QVariant::fromValue(t);
                }
                return QVariant(class_type, &t);
            }
        };

        template <typename T>
        struct variant_handler<T, dtk::is_core_parameter<T>, std::enable_if_t<std::is_pointer<T>::value>>
        {
            static QVariant fromValue(T const & t) {
                int class_type = QMetaType::type(qPrintable(t->typeName() + "*"));
                if (class_type == QMetaType::UnknownType) {
                    return QVariant::fromValue(t);
                }
                return QVariant(class_type, &t, 1);
            }
        };
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter
// ///////////////////////////////////////////////////////////////////

template <typename F>
inline QMetaObject::Connection dtkCoreParameter::connect(F slot)
{
    m_enable_share_connection = false;
    if (!m_connection) {
        m_connection = connection(new dtkCoreParameterConnection());
    }

    auto c = QObject::connect(m_connection.get(), &dtkCoreParameterConnection::valueChanged, slot);
    if (c) {
        m_connection->value_list << c;
        if (!m_connection->param_list.contains(this)) {
            m_connection->param_list << this;
        }
    }
    return c;
}

template <typename F>
inline QMetaObject::Connection dtkCoreParameter::connectFail(F slot)
{
    m_enable_share_connection = false;
    if (!m_connection) {
        m_connection = connection(new dtkCoreParameterConnection());
    }

    auto c = QObject::connect(m_connection.get(), &dtkCoreParameterConnection::invalidValue, slot);
    if (c) {
        m_connection->invalid_list << c;
    }
    return c;
}

template <typename T>
inline int dtkCoreParameter::registerToMetaType(void)
{
    auto type = qMetaTypeId<T>();
    auto from = qMetaTypeId<T *>();
    auto to = qMetaTypeId<dtkCoreParameter *>();
    if (!QMetaType::hasRegisteredConverterFunction(from, to)) {
        QMetaType::registerConverter<T *, dtkCoreParameter *>();
        QMetaType::registerDebugStreamOperator<T>();
        qRegisterMetaTypeStreamOperators<T>(QMetaType::typeName(type));
    }
    return type;
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterBase implementation
// ///////////////////////////////////////////////////////////////////

template <typename Derive>
inline dtkCoreParameterBase<Derive>::dtkCoreParameterBase(const QString& label, const QString& doc) : dtkCoreParameter(label, doc)
{

}

template <typename Derive>
inline dtkCoreParameterBase<Derive>::dtkCoreParameterBase(const dtkCoreParameterBase& o) : dtkCoreParameter(o)
{

}

template <typename Derive>
inline QString dtkCoreParameterBase<Derive>::typeName(void) const
{
    return QMetaType::typeName(qMetaTypeId<Derive>());
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
inline void dtkCoreParameterBase<Derive>::copyAndShare(dtkCoreParameter *source)
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
                    if (!self->m_connection->param_list.contains(self)) {
                        self->m_connection->param_list << self;
                    }
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
            if (!self.m_connection->param_list.contains(&self)) {
                self.m_connection->param_list << &self;
            }
        } else {
            dtkWarn() << Q_FUNC_INFO << "Input parameter has no connection. Only copy of values is done.";
        }
    }
}

template <typename Derive>
inline QVariantHash dtkCoreParameterBase<Derive>::toVariantHash(void) const
{
    QVariantHash hash;
    auto type_name = QMetaType::typeName(qMetaTypeId<Derive>());
    hash.insert("type", type_name);
    hash.insert("label", m_label);
    hash.insert("doc", m_doc);
    return hash;
}

//
// dtkCoreParameter.tpp ends here
