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

// ///////////////////////////////////////////////////////////////////
// dtkCoreAbstractParameter interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreAbstractParameter : public QObject
{
    Q_OBJECT

public:
     dtkCoreAbstractParameter(void) = default;
     dtkCoreAbstractParameter(const QString&);
     dtkCoreAbstractParameter(const dtkCoreAbstractParameter&);
     dtkCoreAbstractParameter(dtkCoreAbstractParameter&&);
    ~dtkCoreAbstractParameter(void);

    void setDocumentation(const QString&);

    QString documentation(void) const;

    virtual void setValue(const QVariant&) = 0;
    virtual QVariant variant(void) const = 0;

signals:
    void valueChanged(QVariant);

protected:
    QString m_doc;
};

Q_DECLARE_METATYPE(dtkCoreAbstractParameter *);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter for arithmetic types
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable = std::enable_if_t<std::is_arithmetic<T>::value>>
class DTKCORE_EXPORT dtkCoreParameter : public dtkCoreAbstractParameter
{
public:
    dtkCoreParameter(void) = default;
    dtkCoreParameter(const T&);
    dtkCoreParameter(const QVariant&);
    dtkCoreParameter(const dtkCoreParameter&);
    dtkCoreParameter(dtkCoreParameter&&);

    dtkCoreParameter(const T&, const T&, const T&, const QString& doc = QString());
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameter(const T&, const T&, const T&, const int&, const QString& doc = QString());

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
    QVariant variant(void) const override;

    T min(void) const;
    T max(void) const;

    const std::array<T, 2>& bounds(void) const;

    template <typename U = T> std::enable_if_t<std::is_floating_point<U>::value> setDecimals(const int&);

    int decimals(void) const;

protected:
    T m_val = T(0);
    std::array<T, 2> m_bounds = {std::numeric_limits<T>::min(), std::numeric_limits<T>::max()};
    int m_decimals = std::numeric_limits<T>::max_digits10/1.75; // 9 decimals for double, 5 for float
};

template <typename T, typename Enable = std::enable_if_t<std::is_arithmetic<T>::value>>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameter<T, Enable>&);
template <typename T, typename Enable = std::enable_if_t<std::is_arithmetic<T>::value>, typename B = std::enable_if_t<std::is_floating_point<T>::value>>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameter<T, Enable>&);
template <typename T, typename Enable = std::enable_if_t<std::is_arithmetic<T>::value>, typename B = std::enable_if_t<!std::is_floating_point<T>::value>, typename U = T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameter<T, Enable>&);

template <typename T, typename Enable = std::enable_if_t<std::is_arithmetic<T>::value>>
DTKCORE_EXPORT QDebug& operator << (QDebug&, dtkCoreParameter<T, Enable>);

// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_uchar = dtkCoreParameter<unsigned char>;
    using d_char = dtkCoreParameter<char>;
    using d_uint = dtkCoreParameter<qulonglong>;
    using d_int = dtkCoreParameter<qlonglong>;
    using d_real = dtkCoreParameter<double>;
    using d_bool = dtkCoreParameter<bool>;
}

Q_DECLARE_METATYPE(dtk::d_uchar);
Q_DECLARE_METATYPE(dtk::d_char);
Q_DECLARE_METATYPE(dtk::d_uint);
Q_DECLARE_METATYPE(dtk::d_int);
Q_DECLARE_METATYPE(dtk::d_real);
Q_DECLARE_METATYPE(dtk::d_bool);

Q_DECLARE_METATYPE(dtk::d_uchar*);
Q_DECLARE_METATYPE(dtk::d_char*);
Q_DECLARE_METATYPE(dtk::d_uint*);
Q_DECLARE_METATYPE(dtk::d_int*);
Q_DECLARE_METATYPE(dtk::d_real*);
Q_DECLARE_METATYPE(dtk::d_bool*);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameter.tpp"

//
// dtkCoreParameter.h ends here
