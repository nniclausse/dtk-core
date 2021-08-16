// dtkCoreParameterNumeric.h
//

#pragma once

#include "dtkCoreParameter.h"

#include <array>

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterNumeric for arithmetic types
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E = dtk::parameter_arithmetic<T>>
class dtkCoreParameterNumeric : public dtkCoreParameterBase<dtkCoreParameterNumeric<T>>
{
public:
    using value_type = T;
    using self_type = dtkCoreParameterNumeric<value_type>;
    using base_type = dtkCoreParameterBase<self_type>;

    using dtkCoreParameter::documentation;
    using dtkCoreParameter::setDocumentation;
    using dtkCoreParameter::label;
    using dtkCoreParameter::setLabel;

public:
     dtkCoreParameterNumeric(void) = default;
    ~dtkCoreParameterNumeric(void) = default;

    dtkCoreParameterNumeric(const T&);
    template <typename U, typename V = typename dtk::is_core_parameter<U>>
    dtkCoreParameterNumeric(const U *);
    dtkCoreParameterNumeric(const QVariant&);
    dtkCoreParameterNumeric(const dtkCoreParameterNumeric&);

    dtkCoreParameterNumeric(const QString&, const T&, const T&, const T&, const QString& doc = QString());
#ifndef SWIG
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameterNumeric(const QString&, const T&, const T&, const T&, const int&, const QString& doc = QString());
    template <typename U = T, typename = std::enable_if_t<std::is_same<U, bool>::value>>     dtkCoreParameterNumeric(const QString&, const T&, const QString& doc = QString());
#endif
    template <typename U = T> dtk::parameter_arithmetic<U, dtkCoreParameterNumeric&> operator = (const U&);
    template <typename U> dtk::is_core_parameter<U, dtkCoreParameterNumeric&> operator = (const U *);
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

    void setMin(const T&);
    void setMax(const T&);

    const std::array<T, 2>& bounds(void) const;

    void setBounds(const std::array<T, 2>&);

    template <typename U = T> std::enable_if_t<std::is_floating_point<U>::value> setDecimals(const int&);

    int decimals(void) const;

    QVariantHash toVariantHash(void) const override;

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

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterNumeric<char>&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterNumeric<char>&);

template <typename T>
DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterNumeric<T>);

// ///////////////////////////////////////////////////////////////////
// Alias and registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_uchar = dtkCoreParameterNumeric<unsigned char>;
    using d_char = dtkCoreParameterNumeric<char>;
    using d_uint = dtkCoreParameterNumeric<qulonglong>;
    using d_int = dtkCoreParameterNumeric<qlonglong>;
    using d_real = dtkCoreParameterNumeric<double>;
    using d_bool = dtkCoreParameterNumeric<bool>;
}

DTK_DECLARE_PARAMETER(dtk::d_uchar);
DTK_DECLARE_PARAMETER(dtk::d_char);
DTK_DECLARE_PARAMETER(dtk::d_uint);
DTK_DECLARE_PARAMETER(dtk::d_int);
DTK_DECLARE_PARAMETER(dtk::d_real);
DTK_DECLARE_PARAMETER(dtk::d_bool);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameterNumeric.tpp"

//
// dtkCoreParameterNumeric.h ends here
