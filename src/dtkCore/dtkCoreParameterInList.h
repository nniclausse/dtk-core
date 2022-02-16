// dtkCoreParameterInList.h
//

#pragma once

#include "dtkCoreParameter.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter contained in a given list
// ///////////////////////////////////////////////////////////////////
template <typename T> class dtkCoreParameterInListObject;
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
     dtkCoreParameterInList(void);
    ~dtkCoreParameterInList(void);

    dtkCoreParameterInList(const T &value);
    dtkCoreParameterInList(const QVariant &variant);
    dtkCoreParameterInList(const dtkCoreParameterInList&);

    dtkCoreParameterInList(const QString &label, const T &value, const QList<T> &available_values,
                           const QString &doc = QString());
    dtkCoreParameterInList(const QString &label, int value_index, const QList<T> &available_values,
                           const QString &doc = QString());
    dtkCoreParameterInList(const QString &label, const QList<T> &available_values, const QString &doc = QString());

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

    dtkCoreParameterObject *object(void) override;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QList<T> m_values;
    int m_value_index = -1;

private:
    dtkCoreParameterInListObject<T> *m_object = nullptr;
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
    using d_inlistchar = dtkCoreParameterInList<char>;
    using d_inlistuchar = dtkCoreParameterInList<uchar>;
}

// ///////////////////////////////////////////////////////////////////
// Registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

DTK_DECLARE_PARAMETER(dtk::d_inliststring);
DTK_DECLARE_PARAMETER(dtk::d_inlistreal);
DTK_DECLARE_PARAMETER(dtk::d_inlistint);
DTK_DECLARE_PARAMETER(dtk::d_inlistchar);
DTK_DECLARE_PARAMETER(dtk::d_inlistuchar);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameterInList.tpp"

//
// dtkCoreParameterInList.h ends here
