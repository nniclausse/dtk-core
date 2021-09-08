// dtkCoreParameter.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameters.h"
#include "dtkCoreTypeTraits.h"

#include <QtCore>

class dtkCoreParameter;

// ///////////////////////////////////////////////////////////////////
// MACRO TO REGISTER PARAMETER TO QMETATYPE SYSTEM
// ///////////////////////////////////////////////////////////////////

// MACRO IN HEADER FILE
#define DTK_DECLARE_PARAMETER(type) \
    Q_DECLARE_METATYPE(type)        \
    Q_DECLARE_METATYPE(type*)

// MACRO IN CPP FILE
#define DTK_DEFINE_PARAMETER(type, name_space)                          \
    namespace dtk {                                                     \
        namespace detail {                                              \
            namespace name_space {                                      \
                int m_dummy = dtkCoreParameter::registerToMetaType<type>(); \
            }                                                           \
        }                                                               \
    }

// ///////////////////////////////////////////////////////////////////
// Typetraits
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    template <typename U, typename V = void>
    using parameter_arithmetic = std::enable_if_t<std::is_arithmetic<U>::value, V>;
    template <typename U, typename V = void>
    using parameter_not_arithmetic = std::enable_if_t<!std::is_arithmetic<U>::value, V>;
    template <typename U, typename V = void>
    using is_core_parameter = std::enable_if_t<std::is_base_of<dtkCoreParameter, std::remove_pointer_t<std::decay_t<U>>>::value, V>;
}

namespace dtk {
    namespace core {
        DTKCORE_EXPORT dtkCoreParameters readParameters(const QString&);
        DTKCORE_EXPORT bool writeParameters(const dtkCoreParameters&, const QString&);
        DTKCORE_EXPORT QJsonObject toJson(const dtkCoreParameters&);

    }
}

// ///////////////////////////////////////////////////////////////////
// Helper class managing connection
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterConnection : public QObject
{
    Q_OBJECT

signals:
    void valueChanged(QVariant);
    void invalidValue(void);

public:
    QVector<QMetaObject::Connection> value_list;
    QVector<QMetaObject::Connection> invalid_list;
    QVector<dtkCoreParameter *>      param_list;
};

Q_DECLARE_METATYPE(std::shared_ptr<dtkCoreParameterConnection>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameter
{
public:
    using connection = std::shared_ptr<dtkCoreParameterConnection>;

public:
     dtkCoreParameter(void) = default;
     dtkCoreParameter(const QString&, const QString& = QString());
     dtkCoreParameter(const dtkCoreParameter&);
    ~dtkCoreParameter(void) = default;

    virtual QString typeName(void) const = 0;

    void setUid(const QString&);
    const QString& uid(void) const;

    void setLabel(const QString&);
    QString label(void) const;

    void setDocumentation(const QString&);
    QString documentation(void) const;

    virtual void setValue(const QVariant&) = 0;
    virtual QVariant variant(void) const = 0;
    virtual QVariantHash toVariantHash(void) const = 0;

#pragma mark - Connection management

    void block(bool);
    void sync(void);
    template <typename F> QMetaObject::Connection connect(F);
    void disconnect(void);
    void disconnect(QMetaObject::Connection);

    void syncFail(void);
    template <typename F> QMetaObject::Connection connectFail(F);
    void disconnectFail(void);

    bool shareConnectionWith(dtkCoreParameter *);
    void shareValue(QVariant);

    virtual void copyAndShare(dtkCoreParameter *) = 0;
    virtual void copyAndShare(const QVariant&) = 0;

#pragma mark - Factory method

public:
    template <typename T>
    static int registerToMetaType(void);
    static dtkCoreParameter *create(const QVariantHash&);

protected:
    QString m_uid;
    QString m_label;
    QString m_doc;
    connection m_connection;

    mutable bool m_enable_share_connection = true;
};

Q_DECLARE_METATYPE(dtkCoreParameter *);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterBase CRTP class
// ///////////////////////////////////////////////////////////////////

template <typename Derive>
class dtkCoreParameterBase : public dtkCoreParameter
{
public:
     dtkCoreParameterBase(void) = default;
     dtkCoreParameterBase(const QString&, const QString& = QString());
     dtkCoreParameterBase(const dtkCoreParameterBase&);
    ~dtkCoreParameterBase(void) = default;

public:
    QString typeName(void) const override;

    QVariant variant(void) const final;
    void copyAndShare(dtkCoreParameter *) final;
    void copyAndShare(const QVariant&) final;

    virtual QVariantHash toVariantHash(void) const override = 0;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameter.tpp"

//
// dtkCoreParameter.h ends here
