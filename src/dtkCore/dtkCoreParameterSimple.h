// dtkCoreParameterSimple.h
//

#pragma once

#include "dtkCoreParameter.h"

template <typename T> class dtkCoreParameterSimpleObject;

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter simple version
// ///////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
class dtkCoreParameterSimple : public dtkCoreParameterBase<dtkCoreParameterSimple<T>>
{
public:
    using value_type = T;
    using self_type = dtkCoreParameterSimple<value_type>;
    using base_type = dtkCoreParameterBase<self_type>;

    using dtkCoreParameter::documentation;
    using dtkCoreParameter::setDocumentation;
    using dtkCoreParameter::label;
    using dtkCoreParameter::setLabel;

public:
     dtkCoreParameterSimple(void);
    ~dtkCoreParameterSimple(void);

    dtkCoreParameterSimple(const dtkCoreParameter *);
    dtkCoreParameterSimple(const QVariant&);
    dtkCoreParameterSimple(const dtkCoreParameterSimple&);

    dtkCoreParameterSimple(const QString&, const T&, const QString& = QString());

    dtkCoreParameterSimple& operator = (const T&);
    dtkCoreParameterSimple& operator = (const dtkCoreParameter *);
    dtkCoreParameterSimple& operator = (const QVariant&);
    dtkCoreParameterSimple& operator = (const dtkCoreParameterSimple&);

    operator T() const;

    void setValue(const T&);
    void setValue(const QVariant&) override;

    T value(void) const;

    QVariantHash toVariantHash(void) const override;

    dtkCoreParameterObject *object(void) override;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    T m_value = T();

private:
    dtkCoreParameterSimpleObject<T> *m_object = nullptr;
};

template <typename T>
DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterSimple<T>&);
template <typename T>
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterSimple<T>&);

template <typename T>
DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterSimple<T>);

// ///////////////////////////////////////////////////////////////////
// Alias and registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_string = dtkCoreParameterSimple<QString>;
}

DTK_DECLARE_PARAMETER(dtk::d_string);

// ///////////////////////////////////////////////////////////////////

#include "dtkCoreParameterSimple.tpp"

//
// dtkCoreParameterSimple.h ends here
