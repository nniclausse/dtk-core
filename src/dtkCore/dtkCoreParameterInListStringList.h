// dtkCoreParameterInListStringList.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameter.h"

class dtkCoreParameterInListStringListObject;

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameter contained in a given list
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterInListStringList : public dtkCoreParameterBase<dtkCoreParameterInListStringList>
{
public:
    using value_type = QStringList;
    using self_type = dtkCoreParameterInListStringList;
    using base_type = dtkCoreParameterBase<self_type>;

    using dtkCoreParameter::documentation;
    using dtkCoreParameter::setDocumentation;
    using dtkCoreParameter::label;
    using dtkCoreParameter::setLabel;

public:
     dtkCoreParameterInListStringList(void);
    ~dtkCoreParameterInListStringList(void);

    dtkCoreParameterInListStringList(const QStringList&);
    dtkCoreParameterInListStringList(const QVariant&);
    dtkCoreParameterInListStringList(const dtkCoreParameterInListStringList&);

    dtkCoreParameterInListStringList(const QString&, const QStringList&, const QStringList&, const QString& = QString());

    dtkCoreParameterInListStringList& operator = (const QStringList&);
    dtkCoreParameterInListStringList& operator = (const QVariant&);
    dtkCoreParameterInListStringList& operator = (const dtkCoreParameterInListStringList&);

    int size(void) const;
    QStringList value(void) const;
    QStringList list(void) const;

    void addValue(const QString&);
    void removeValue(const QString&);

    void setValue(const QStringList&);
    void setValue(const QVariant&) override;
    void setList(const QStringList&);

    QVariantHash toVariantHash(void) const override;

    dtkCoreParameterObject *object(void) override;

    Q_DECL_DEPRECATED QStringList values(void) const;
    Q_DECL_DEPRECATED void setValues(const QStringList&);

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QStringList m_value;
    QStringList m_list;

private:
    dtkCoreParameterInListStringListObject *m_object = nullptr;
};

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterInListStringList&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterInListStringList&);

DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterInListStringList);

// ///////////////////////////////////////////////////////////////////
// Alias and registration to QMetaType system
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_inliststringlist = dtkCoreParameterInListStringList;
}

DTK_DECLARE_PARAMETER(dtk::d_inliststringlist);

//
// dtkCoreParameterInListStringList.h ends here
