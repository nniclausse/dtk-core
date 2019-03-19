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

#include "dtkCoreParameter.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterFile declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterFile : public dtkCoreParameterBase<dtkCoreParameterFile>
{
public:
     dtkCoreParameterFile(void) = default;
    ~dtkCoreParameterFile(void) = default;

    dtkCoreParameterFile(const QVariant&);
    dtkCoreParameterFile(const dtkCoreParameterFile&);

    dtkCoreParameterFile(const QString& label, const QString& filename, const QString& dir,
                         const QStringList& filters, const QString& = QString());

    dtkCoreParameterFile& operator = (const QVariant&);
    dtkCoreParameterFile& operator = (const dtkCoreParameterFile&);

    void setValue(const QString& filename);
    void setValue(const QVariant&) override;

    QString fileName(void) const;
    QString dir(void) const;
    QStringList filters(void) const;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QString m_filename;
    QString m_dir;
    QStringList m_filters;
};

// ///////////////////////////////////////////////////////////////////

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterFile&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterFile&);

DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterFile);

// ///////////////////////////////////////////////////////////////////
// Alias and QMetaType
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    using d_file = dtkCoreParameterFile;
}

Q_DECLARE_METATYPE(dtk::d_file);
Q_DECLARE_METATYPE(dtk::d_file *);

//
// dtkCoreParameterFile.h ends here
