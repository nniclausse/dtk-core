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

class DTKCORE_EXPORT dtkCoreParameterConnection : public QObject
{
    Q_OBJECT

signals:
    void valueChanged(QVariant);
    void invalidValue(void);

public:
    QMetaObject::Connection value;
    QMetaObject::Connection invalid;
};

Q_DECLARE_METATYPE(std::shared_ptr<dtkCoreParameterConnection>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameter : public QObject
{
    Q_OBJECT

public:
    using connection = std::shared_ptr<dtkCoreParameterConnection>;

public:
     dtkCoreParameter(void) = default;
     dtkCoreParameter(const QString&, const QString& = QString());
     dtkCoreParameter(const dtkCoreParameter&);
    ~dtkCoreParameter(void) = default;

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

    bool shareConnectionWith(dtkCoreParameter *);

    virtual void copyAndShare(dtkCoreParameter *) = 0;
    virtual void copyAndShare(const QVariant&) = 0;

#pragma mark - Factory method

public:
    static dtkCoreParameter *create(const QVariantHash&);

protected:
    QString m_label;
    QString m_doc;
    connection m_connection;

protected:
    mutable bool m_enable_share_connection = true;
};

Q_DECLARE_METATYPE(dtkCoreParameter *);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterBase CRTP class
// ///////////////////////////////////////////////////////////////////

template <typename Derive>
class DTKCORE_EXPORT dtkCoreParameterBase : public dtkCoreParameter
{
public:
     dtkCoreParameterBase(void) = default;
     dtkCoreParameterBase(const QString&, const QString& = QString());
     dtkCoreParameterBase(const dtkCoreParameterBase&);
    ~dtkCoreParameterBase(void) = default;

public:
    QVariant variant(void) const final;
    void copyAndShare(dtkCoreParameter *) final;
    void copyAndShare(const QVariant&) final;
};

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter simple version
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
class DTKCORE_EXPORT dtkCoreParameterSimple : public dtkCoreParameterBase<dtkCoreParameterSimple<T>>
{
public:
     dtkCoreParameterSimple(void) = default;
    ~dtkCoreParameterSimple(void) = default;

    dtkCoreParameterSimple(const QVariant&);
    dtkCoreParameterSimple(const dtkCoreParameterSimple&);

    dtkCoreParameterSimple(const QString&, const T&, const QString& = QString());

    dtkCoreParameterSimple& operator = (const T&);
    dtkCoreParameterSimple& operator = (const QVariant&);
    dtkCoreParameterSimple& operator = (const dtkCoreParameterSimple&);

    operator T() const;

    void setValue(const T&);
    void setValue(const QVariant&) override;

    T value(void) const;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    T m_value;
};

template <typename T>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterSimple<T>&);
template <typename T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterSimple<T>&);

template <typename T>
DTKCORE_EXPORT QDebug& operator << (QDebug&, dtkCoreParameterSimple<T>);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterNumeric for arithmetic types
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E = dtk::parameter_arithmetic<T>>
class DTKCORE_EXPORT dtkCoreParameterNumeric : public dtkCoreParameterBase<dtkCoreParameterNumeric<T>>
{
public:
     dtkCoreParameterNumeric(void) = default;
    ~dtkCoreParameterNumeric(void) = default;

    dtkCoreParameterNumeric(const T&);
    dtkCoreParameterNumeric(const QVariant&);  // JLS: manque le doc pour la classe abstract ???
    dtkCoreParameterNumeric(const dtkCoreParameterNumeric&);

    dtkCoreParameterNumeric(const QString&, const T&, const T&, const T&, const QString& doc = QString());
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameterNumeric(const QString&, const T&, const T&, const T&, const int&, const QString& doc = QString());

    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator = (const U&);
    dtkCoreParameterNumeric& operator = (const QVariant&);
    dtkCoreParameterNumeric& operator = (const dtkCoreParameterNumeric&);
    template <typename U> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator = (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator += (const U&);
    dtkCoreParameterNumeric& operator += (const QVariant&);
    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator += (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator -= (const U&);
    dtkCoreParameterNumeric& operator -= (const QVariant&);
    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator -= (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator *= (const U&);
    dtkCoreParameterNumeric& operator *= (const QVariant&);
    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator *= (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator /= (const U&);
    dtkCoreParameterNumeric& operator /= (const QVariant&);
    template <typename U> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator /= (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameterNumeric&> operator %= (const U&);
    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo, dtkCoreParameterNumeric&> operator %= (const QVariant&);
    template <typename U = T> std::enable_if_t<std::numeric_limits<U>::is_modulo && std::numeric_limits<T>::is_modulo, dtkCoreParameterNumeric&> operator %= (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, bool> operator == (const U&);
    bool operator == (const QVariant&);
    template <typename U> dtk::parameter_arithmetic<U, bool> operator == (const dtkCoreParameterNumeric<U>&);

    template <typename U = T> dtk::parameter_arithmetic<U, bool> operator != (const U&);
    bool operator != (const QVariant&);
    template <typename U> dtk::parameter_arithmetic<U, bool> operator != (const dtkCoreParameterNumeric<U>&);

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
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    T m_val = T(0);
    std::array<T, 2> m_bounds = {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
    int m_decimals = std::numeric_limits<T>::max_digits10/1.75; // 9 decimals for double, 5 for float
};

template <typename T>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterNumeric<T>&);
template <typename T, typename E = std::enable_if_t<std::is_floating_point<T>::value>>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterNumeric<T>&);
template <typename T, typename E = std::enable_if_t<!std::is_floating_point<T>::value>, typename U = T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterNumeric<T>&);

template <typename T>
DTKCORE_EXPORT QDebug& operator << (QDebug&, dtkCoreParameterNumeric<T>);

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

    dtkCoreParameterInList& operator = (const T&);
    dtkCoreParameterInList& operator = (const QVariant&);
    dtkCoreParameterInList& operator = (const dtkCoreParameterInList&);

    operator T() const;

    void setValueIndex(int);
    void setValue(const T&);
    void setValue(const QVariant&) override;

    int valueIndex(void) const;
    T value(void) const;
    QList<T> values(void) const;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

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
// dtkCoreParameterRange declaration
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E = dtk::parameter_arithmetic<T>>
class DTKCORE_EXPORT dtkCoreParameterRange : public dtkCoreParameterBase<dtkCoreParameterRange<T>>
{
public:
     dtkCoreParameterRange(void) = default;
    ~dtkCoreParameterRange(void) = default;

    dtkCoreParameterRange(const std::array<T, 2>&);
    dtkCoreParameterRange(std::initializer_list<T>);
    dtkCoreParameterRange(const QVariant&);
    dtkCoreParameterRange(const dtkCoreParameterRange&);

    dtkCoreParameterRange(const QString&, const std::array<T, 2>&, const T&, const T&, const QString& doc = QString());
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameterRange(const QString&, const std::array<T, 2>&, const T&, const T&, const int&, const QString& doc = QString());

    dtkCoreParameterRange& operator = (const std::array<T, 2>&);
    dtkCoreParameterRange& operator = (std::initializer_list<T>);
    dtkCoreParameterRange& operator = (const QVariant&);
    dtkCoreParameterRange& operator = (const dtkCoreParameterRange&);

    void setValue(const std::array<T, 2>&);
    void setValue(std::initializer_list<T>);
    void setValue(const QVariant&) override;

    const std::array<T, 2>& value(void) const;

    T min(void) const;
    T max(void) const;

    const std::array<T, 2>& bounds(void) const;

    template <typename U = T> std::enable_if_t<std::is_floating_point<U>::value> setDecimals(const int&);

    int decimals(void) const;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    std::array<T, 2> m_val = {T(0), T(0)};
    std::array<T, 2> m_bounds = {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
    int m_decimals = std::numeric_limits<T>::max_digits10/1.75; // 9 decimals for double, 5 for float
};

// ///////////////////////////////////////////////////////////////////
// Typedef
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_uchar  = dtkCoreParameterNumeric<unsigned char>;
    using d_char   = dtkCoreParameterNumeric<char>;
    using d_uint   = dtkCoreParameterNumeric<qulonglong>;
    using d_int    = dtkCoreParameterNumeric<qlonglong>;
    using d_real   = dtkCoreParameterNumeric<double>;
    using d_bool   = dtkCoreParameterNumeric<bool>;

    using d_string = dtkCoreParameterSimple<QString>;

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
