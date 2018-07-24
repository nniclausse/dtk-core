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

#include <dtkCoreConceptFooPlugin/dtkCoreConceptFooPluginExport>

#include <QtCore>

class DTKCORECONCEPTFOOPLUGIN_EXPORT dtkCoreConceptFooData
{
public:
     dtkCoreConceptFooData(void) = default;
     dtkCoreConceptFooData(const int& id, const QString& name);
     dtkCoreConceptFooData(const dtkCoreConceptFooData& o);
    ~dtkCoreConceptFooData(void) = default;

    dtkCoreConceptFooData& operator = (const dtkCoreConceptFooData& o);
    bool operator == (const dtkCoreConceptFooData& o) const;

    void setId(const int& id);
    void setName(const QString& name);

    int id(void) const;
    QString name(void) const;

private:
    int m_id = -1;
    QString m_name = QString("dtkCoreConceptFooData");
    friend class dtkCoreConceptFoo;
};

Q_DECLARE_METATYPE(dtkCoreConceptFooData);

//
// dtkCoreConceptFoo_p.h ends here
