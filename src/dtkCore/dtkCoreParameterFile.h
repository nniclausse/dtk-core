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

class DTKCORE_EXPORT dtkCoreParameterDir : public dtkCoreParameterBase<dtkCoreParameterDir>
{
public:
     dtkCoreParameterDir(void) = default;
    ~dtkCoreParameterDir(void) = default;

    dtkCoreParameterDir(const QVariant&);
    dtkCoreParameterDir(const dtkCoreParameterDir&);

    dtkCoreParameterDir(const QString& label, const QString& dirname,
                        const QStringList& filters, const QString& = QString());

    dtkCoreParameterDir& operator = (const QVariant&);
    dtkCoreParameterDir& operator = (const dtkCoreParameterDir&);

    virtual void setValue(const QString& filename);
    void setValue(const QVariant&) override;

    QString dir(void) const;
    QStringList filters(void) const;

protected:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QString m_dir;
    QStringList m_filters;
};

// ///////////////////////////////////////////////////////////////////

DTKCORE_EXPORT QDataStream& operator << (QDataStream&, const dtkCoreParameterDir&);
DTKCORE_EXPORT QDataStream& operator >> (QDataStream&, dtkCoreParameterDir&);

DTKCORE_EXPORT QDebug operator << (QDebug, dtkCoreParameterDir);

// ///////////////////////////////////////////////////////////////////
// Alias and QMetaType
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    using d_dir = dtkCoreParameterDir;
}

Q_DECLARE_METATYPE(dtk::d_dir);
Q_DECLARE_METATYPE(dtk::d_dir *);

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterFile declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterFile : public dtkCoreParameterDir
{
public:
     dtkCoreParameterFile(void) = default;
    ~dtkCoreParameterFile(void) = default;

    dtkCoreParameterFile(const QVariant&);
    dtkCoreParameterFile(const dtkCoreParameterFile&);

    dtkCoreParameterFile(const QString& label, const QString& dirname, const QString& basename,
                         const QStringList& filters, const QString& = QString());

    dtkCoreParameterFile& operator = (const QVariant&);
    dtkCoreParameterFile& operator = (const dtkCoreParameterFile&);

    void setValue(const QString& filename) override;
    void setValue(const QVariant&) override;

    QString fileName(void) const;
    QString baseName(void) const;

private:
    using dtkCoreParameter::m_label;
    using dtkCoreParameter::m_doc;

    QString m_basename;
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
