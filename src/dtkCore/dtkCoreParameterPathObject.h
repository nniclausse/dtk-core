// dtkCoreParameterPathObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterPath.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterPathObject declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterPathObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QStringList filters READ filters WRITE setFilters NOTIFY filtersChanged)
    Q_PROPERTY(QString dirName READ dirName CONSTANT)
    Q_PROPERTY(QString baseName READ baseName CONSTANT)

public:
     dtkCoreParameterPathObject(dtkCoreParameterPath *);
    ~dtkCoreParameterPathObject(void);

    void setPath(const QString&);
    QString path(void) const;

    void setFilters(const QStringList&);
    QStringList filters(void) const;

    QString dirName(void) const;
    QString baseName(void) const;

signals:
    void pathChanged(const QString&);
    void filtersChanged(const QStringList&);

public:
    dtkCoreParameterPath *parameter(void) override;

public:
    void notifyPath(const QString&);
    void notifyFilters(const QStringList&);

private:
    dtkCoreParameterPath *m_param = nullptr;
};

//
// dtkCoreParameterPathObject.h ends here
