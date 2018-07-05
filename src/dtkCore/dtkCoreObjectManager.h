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

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCoreObjectManager declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreObjectManager : public QObject
{
    Q_OBJECT

public:
    static dtkCoreObjectManager *instance(void);

public:
    int count(void) const;

public slots:
    void add(const QVariant&, const QString&);
    void add(const QVariant&);

    bool remove(const QVariant&);

public:
    QVariant value(const QString& key) const;
    QStringList keys(void) const;

protected:
    static dtkCoreObjectManager *s_instance;

private:
     dtkCoreObjectManager(void);
    ~dtkCoreObjectManager(void);

private:
    class dtkCoreObjectManagerPrivate *d;
};

// ///////////////////////////////////////////////////////////////////
// Helper function
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    DTKCORE_EXPORT dtkCoreObjectManager& objectManager(void);
}

//
// dtkCoreObjectManager.h ends here
