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

#pragma once

#include <dtkCoreExport>

#include "dtkCoreTypeTraits.h"

#include <QtCore>

#include <array>

namespace dtk {
    template <typename T, typename E = void>
    using parameter_arithmetic = std::enable_if_t<std::is_arithmetic<T>::value, E>;
    template <typename T, typename E = void>
    using parameter_not_arithmetic = std::enable_if_t<!std::is_arithmetic<T>::value, E>;
}

// ///////////////////////////////////////////////////////////////////
// Helper class managing connection
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreAbstractParameterConnection : public QObject
{
    Q_OBJECT

signals:
    void valueChanged(QVariant);
    void invalidValue(void);

public:
    QMetaObject::Connection value;
    QMetaObject::Connection invalid;
};

Q_DECLARE_METATYPE(std::shared_ptr<dtkCoreAbstractParameterConnection>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreAbstractParameter interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreAbstractParameter : public QObject
{
    Q_OBJECT

public:
    using connection = std::shared_ptr<dtkCoreAbstractParameterConnection>;

public:
     dtkCoreAbstractParameter(void) = default;
     dtkCoreAbstractParameter(const QString&, const QString& = QString());
     dtkCoreAbstractParameter(const dtkCoreAbstractParameter&);
    ~dtkCoreAbstractParameter(void) = default;

    void setLabel(const QString&);
    QString label(void) const;

    void setDocumentation(const QString&);
    QString documentation(void) const;

    virtual void setValue(const QVariant&) = 0;
    virtual QVariant variant(void) const = 0;

#pragma mark - Connection management

    void block(bool);
    void sync(void);
    template <typename F> QMetaObject::Connection connect(F);
    void disconnect(void);

    void syncFail(void);
    template <typename F> QMetaObject::Connection connectFail(F);
    void disconnectFail(void);

    bool shareConnectionWith(dtkCoreAbstractParameter *);

    virtual void copyAndShare(dtkCoreAbstractParameter *) = 0;
    virtual void copyAndShare(const QVariant&) = 0;

#pragma mark - Factory method

    static dtkCoreAbstractParameter *create(const QVariant&);

protected:
    QString m_label;
    QString m_doc;
    connection m_connection;

protected:
    mutable bool m_enable_share_connection = true;
};

Q_DECLARE_METATYPE(dtkCoreAbstractParameter *);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterBase CRTP class
// ///////////////////////////////////////////////////////////////////

template <typename Derive>
class DTKCORE_EXPORT dtkCoreParameterBase : public dtkCoreAbstractParameter
{
public:
     dtkCoreParameterBase(void) = default;
     dtkCoreParameterBase(const QString&, const QString& = QString());
     dtkCoreParameterBase(const dtkCoreParameterBase&);
     dtkCoreParameterBase(const QVariant&);
    ~dtkCoreParameterBase(void) = default;

public:
    QVariant variant(void) const final;
    void copyAndShare(dtkCoreAbstractParameter *) final;
    void copyAndShare(const QVariant&) final;
};

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter simple version
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
class DTKCORE_EXPORT dtkCoreParameter : public dtkCoreParameterBase<dtkCoreParameter<T, Enable>>
{
public:
     dtkCoreParameter(void) = default;
    ~dtkCoreParameter(void) = default;

    dtkCoreParameter(const QVariant&);
    dtkCoreParameter(const dtkCoreParameter&);

    dtkCoreParameter(const QString&, const T&, const QString& = QString());

    dtkCoreParameter& operator = (const T&);
    dtkCoreParameter& operator = (const QVariant&);
    dtkCoreParameter& operator = (const dtkCoreParameter&);

    operator T() const;

    void setValue(const T&);
    void setValue(const QVariant&) override;

    T value(void) const;

private:
    using dtkCoreAbstractParameter::m_label;
    using dtkCoreAbstractParameter::m_doc;

    T m_value;
};

template <typename T>
DTKCORE_EXPORT dtk::parameter_not_arithmetic<T, QDataStream>& operator << (QDataStream&, const dtkCoreParameter<T>&);
template <typename T>
DTKCORE_EXPORT dtk::parameter_not_arithmetic<T, QDataStream>& operator >> (QDataStream&, dtkCoreParameter<T>&);

template <typename T>
DTKCORE_EXPORT dtk::parameter_not_arithmetic<T, QDebug>& operator << (QDebug&, dtkCoreParameter<T>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter for arithmetic types
// ///////////////////////////////////////////////////////////////////

template <typename T>
class DTKCORE_EXPORT dtkCoreParameter<T, dtk::parameter_arithmetic<T>> : public dtkCoreParameterBase<dtkCoreParameter<T>>
{
public:
     dtkCoreParameter(void) = default;
    ~dtkCoreParameter(void) = default;

    dtkCoreParameter(const T&);
    dtkCoreParameter(const QVariant&);  // JLS: manque le doc pour la classe abstract ???
    dtkCoreParameter(const dtkCoreParameter&);

    dtkCoreParameter(const QString&, const T&, const T&, const T&, const QString& doc = QString());
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameter(const QString&, const T&, const T&, const T&, const int&, const QString& doc = QString());

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator = (const U&);
    dtkCoreParameter& operator = (const QVariant&);
    dtkCoreParameter& operator = (const dtkCoreParameter&);
    template <typename U> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator = (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator += (const U&);
    dtkCoreParameter& operator += (const QVariant&);
    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator += (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator -= (const U&);
    dtkCoreParameter& operator -= (const QVariant&);
    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator -= (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator *= (const U&);
    dtkCoreParameter& operator *= (const QVariant&);
    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator *= (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator /= (const U&);
    dtkCoreParameter& operator /= (const QVariant&);
    template <typename U> std::enable_if_t<std::is_arithmetic<U>::value, dtkCoreParameter&> operator /= (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&> operator %= (const U&);
    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameter&> operator %= (const QVariant&);
    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameter&> operator %= (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, bool> operator == (const U&);
    bool operator == (const QVariant&);
    template <typename U> std::enable_if_t<std::is_arithmetic<U>::value, bool> operator == (const dtkCoreParameter<U>&);

    template <typename U = T> std::enable_if_t<std::is_arithmetic<U>::value, bool> operator != (const U&);
    bool operator != (const QVariant&);
    template <typename U> std::enable_if_t<std::is_arithmetic<U>::value, bool> operator != (const dtkCoreParameter<U>&);

    operator T() const;

    void setValue(const T&);
    void setValue(const QVariant&) override;

    T value(void) const;

    T min(void) const;
    T max(void) const;

    const std::array<T, 2>& bounds(void) const;

    template <typename U = T> std::enable_if_t<std::is_floating_point<U>::value> setDecimals(const int&);

    int decimals(void) const;

protected:
    using dtkCoreAbstractParameter::m_label;
    using dtkCoreAbstractParameter::m_doc;

    T m_val = T(0);
    std::array<T, 2> m_bounds = {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
    int m_decimals = std::numeric_limits<T>::max_digits10/1.75; // 9 decimals for double, 5 for float
};

template <typename T>
DTKCORE_EXPORT dtk::parameter_arithmetic<T, QDataStream>& operator << (QDataStream&, const dtkCoreParameter<T>&);
template <typename T, typename E = dtk::parameter_arithmetic<T>, typename F = std::enable_if_t<std::is_floating_point<T>::value>>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameter<T>&);
template <typename T, typename E = dtk::parameter_arithmetic<T>, typename F = std::enable_if_t<!std::is_floating_point<T>::value>, typename U = T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameter<T>&);

template <typename T, typename E = dtk::parameter_arithmetic<T>>
DTKCORE_EXPORT QDebug& operator << (QDebug&, dtkCoreParameter<T>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter contained in a given list
// ///////////////////////////////////////////////////////////////////

template <typename T>
class DTKCORE_EXPORT dtkCoreParameterInList : public dtkCoreParameterBase<dtkCoreParameterInList<T>>
{
public:
     dtkCoreParameterInList(void) = default;
    ~dtkCoreParameterInList(void) = default;

    dtkCoreParameterInList(const T&);
    dtkCoreParameterInList(const QVariant&);
    dtkCoreParameterInList(const dtkCoreParameterInList&);

    dtkCoreParameterInList(const QString&, const T&, const QList<T>&, const QString& = QString());
    dtkCoreParameterInList(const QString&, int, const QList<T>&, const QString& = QString());
    dtkCoreParameterInList(const QString&, const QList<T>&, const QString& = QString());

    dtkCoreParameterInList& operator = (const dtkCoreParameterInList&);

    operator T() const;

    void setValueIndex(int);
    void setValue(const T&);
    void setValue(const QVariant&) override;

    int valueIndex(void) const;
    T value(void) const;
    QList<T> values(void) const;

private:
    using dtkCoreAbstractParameter::m_label;
    using dtkCoreAbstractParameter::m_doc;

    QList<T> m_values;
    int m_value_index = -1;
};

template <typename T>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterInList<T>&);
template <typename T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterInList<T>&);

template <typename T>
DTKCORE_EXPORT QDebug& operator << (QDebug&, dtkCoreParameterInList<T>);

// ///////////////////////////////////////////////////////////////////
// Typedef
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_uchar  = dtkCoreParameter<unsigned char>;
    using d_char   = dtkCoreParameter<char>;
    using d_uint   = dtkCoreParameter<qulonglong>;
    using d_int    = dtkCoreParameter<qlonglong>;
    using d_real   = dtkCoreParameter<double>;
    using d_bool   = dtkCoreParameter<bool>;

    using d_string = dtkCoreParameter<QString>;

    using d_inliststring = dtkCoreParameterInList<QString>;
}

// ///////////////////////////////////////////////////////////////////
// Registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(dtk::d_uchar);
Q_DECLARE_METATYPE(dtk::d_char);
Q_DECLARE_METATYPE(dtk::d_uint);
Q_DECLARE_METATYPE(dtk::d_int);
Q_DECLARE_METATYPE(dtk::d_real);
Q_DECLARE_METATYPE(dtk::d_bool);
Q_DECLARE_METATYPE(dtk::d_string);
Q_DECLARE_METATYPE(dtk::d_inliststring);

Q_DECLARE_METATYPE(dtk::d_uchar*);
Q_DECLARE_METATYPE(dtk::d_char*);
Q_DECLARE_METATYPE(dtk::d_uint*);
Q_DECLARE_METATYPE(dtk::d_int*);
Q_DECLARE_METATYPE(dtk::d_real*);
Q_DECLARE_METATYPE(dtk::d_bool*);
Q_DECLARE_METATYPE(dtk::d_string*);
Q_DECLARE_METATYPE(dtk::d_inliststring*);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameter.tpp"


//
// dtkCoreParameter.h ends here
