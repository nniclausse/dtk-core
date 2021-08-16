// dtkCoreParameterInList.h
//

#pragma once

#include "dtkCoreParameter.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter contained in a given list
// ///////////////////////////////////////////////////////////////////

template <typename T>
class dtkCoreParameterInList : public dtkCoreParameterBase<dtkCoreParameterInList<T>>
{
public:
    using value_type = T;
    using self_type = dtkCoreParameterInList<value_type>;
    using base_type = dtkCoreParameterBase<self_type>;

    using dtkCoreParameter::documentation;
    using dtkCoreParameter::setDocumentation;
    using dtkCoreParameter::label;
    using dtkCoreParameter::setLabel;

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
    void setValues(const QList<T>&);

    int valueIndex(void) const;
    T value(void) const;
    QList<T> values(void) const;

    QVariantHash toVariantHash(void) const override;

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
DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterInList<T>);

// ///////////////////////////////////////////////////////////////////
// ALias
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_inliststring = dtkCoreParameterInList<QString>;
    using d_inlistreal = dtkCoreParameterInList<double>;
    using d_inlistint = dtkCoreParameterInList<qlonglong>;
}

// ///////////////////////////////////////////////////////////////////
// Registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

DTK_DECLARE_PARAMETER(dtk::d_inliststring);
DTK_DECLARE_PARAMETER(dtk::d_inlistreal);
DTK_DECLARE_PARAMETER(dtk::d_inlistint);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameterInList.tpp"

//
// dtkCoreParameterInList.h ends here
