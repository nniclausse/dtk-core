// dtkCoreParameterPath.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameter.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterPath declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterPath : public dtkCoreParameterBase<dtkCoreParameterPath>
{
public:
    using self_type = dtkCoreParameterPath;
    using base_type = dtkCoreParameterBase<self_type>;

     dtkCoreParameterPath(void) = default;
    ~dtkCoreParameterPath(void) = default;

    dtkCoreParameterPath(const dtkCoreParameter *);
    dtkCoreParameterPath(const QVariant&);
    dtkCoreParameterPath(const dtkCoreParameterPath&);

    dtkCoreParameterPath(const QString& label, const QString& path,
                         const QStringList& filters, const QString& = QString());

    dtkCoreParameterPath& operator = (const dtkCoreParameter *);
    dtkCoreParameterPath& operator = (const QVariant&);
    dtkCoreParameterPath& operator = (const dtkCoreParameterPath&);

    void setValue(const QString& path);
    void setValue(const QVariant&) override;

    void setPath(const QString&);
    void setFilters(const QStringList&);

    QString path(void) const;
    QStringList filters(void) const;

    QString dirName(void) const;
    QString baseName(void) const;

    QVariantHash toVariantHash(void) const override;

    dtkCoreParameterObject *object(void) override;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QString m_path;
    QStringList m_filters;

private:
    dtkCoreParameterPathObject *m_object = nullptr;
};

// ///////////////////////////////////////////////////////////////////

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterPath&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterPath&);

DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterPath);

// ///////////////////////////////////////////////////////////////////
// Alias and QMetaType
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    using d_path = dtkCoreParameterPath;
}

DTK_DECLARE_PARAMETER(dtk::d_path);

//
// dtkCoreParameterPath.h ends here
