// dtkCoreParameterRange.h
//

#pragma once

#include "dtkCoreParameter.h"

template <typename T> class dtkCoreParameterRangeObject;

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterRange declaration
// ///////////////////////////////////////////////////////////////////

template <typename T, typename E = dtk::parameter_arithmetic<T>>
class dtkCoreParameterRange : public dtkCoreParameterBase<dtkCoreParameterRange<T>>
{
public:
    using range = std::array<T, 2>;
    using value_type = T;
    using self_type = dtkCoreParameterRange<value_type>;
    using base_type = dtkCoreParameterBase<self_type>;

    using dtkCoreParameter::documentation;
    using dtkCoreParameter::setDocumentation;
    using dtkCoreParameter::label;
    using dtkCoreParameter::setLabel;

public:
     dtkCoreParameterRange(void) = default;
    ~dtkCoreParameterRange(void) = default;

    dtkCoreParameterRange(const std::array<T, 2>&);
    dtkCoreParameterRange(std::initializer_list<T>);
    dtkCoreParameterRange(const QVariant&);
    dtkCoreParameterRange(const dtkCoreParameterRange&);

    dtkCoreParameterRange(const QString&, const std::array<T, 2>&, const T&, const T&, const QString& doc = QString());
#ifndef SWIG
    template <typename U = T, typename = std::enable_if_t<std::is_floating_point<U>::value>> dtkCoreParameterRange(const QString&, const std::array<T, 2>&, const T&, const T&, const int&, const QString& doc = QString());
#endif

    dtkCoreParameterRange& operator = (const std::array<T, 2>&);
    dtkCoreParameterRange& operator = (std::initializer_list<T>);
    dtkCoreParameterRange& operator = (const QVariant&);
    dtkCoreParameterRange& operator = (const dtkCoreParameterRange&);

    void setValue(const std::array<T, 2>&);
    void setValue(std::initializer_list<T>);
    void setValue(const QVariant&) override;

    const std::array<T, 2>& value(void) const;

    value_type  operator[](int index) const;

    T min(void) const;
    T max(void) const;

    void setMin(const T&);
    void setMax(const T&);

    const std::array<T, 2>& bounds(void) const;

    void setBounds(const std::array<T, 2>&);

    template <typename U = T> std::enable_if_t<std::is_floating_point<U>::value> setDecimals(const int&);

    int decimals(void) const;

    QVariantHash toVariantHash(void) const override;

    dtkCoreParameterObject *object(void) override;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    std::array<T, 2> m_val = {T(0), T(0)};
    std::array<T, 2> m_bounds = {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
    int m_decimals = std::numeric_limits<T>::max_digits10/1.75; // 9 decimals for double, 5 for float

private:
    dtkCoreParameterRangeObject<T> *m_object = nullptr;
};

template <typename T>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterRange<T>&);
template <typename T, typename E = std::enable_if_t<std::is_floating_point<T>::value>>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterRange<T>&);
template <typename T, typename E = std::enable_if_t<!std::is_floating_point<T>::value>, typename U = T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterRange<T>&);

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterRange<char>&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterRange<char>&);

template <typename T>
DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterRange<T>);

// ///////////////////////////////////////////////////////////////////
// Alias and registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_range_uchar = dtkCoreParameterRange<unsigned char>;
    using d_range_char = dtkCoreParameterRange<char>;
    using d_range_uint = dtkCoreParameterRange<qulonglong>;
    using d_range_int = dtkCoreParameterRange<qlonglong>;
    using d_range_real = dtkCoreParameterRange<double>;
}

DTK_DECLARE_PARAMETER(dtk::d_range_uchar);
DTK_DECLARE_PARAMETER(dtk::d_range_char);
Q_DECLARE_METATYPE(dtk::d_range_char::range);
DTK_DECLARE_PARAMETER(dtk::d_range_uint);
DTK_DECLARE_PARAMETER(dtk::d_range_int);
Q_DECLARE_METATYPE(dtk::d_range_int::range);
DTK_DECLARE_PARAMETER(dtk::d_range_real);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameterRange.tpp"

//
// dtkCoreParameterRange.h ends here
