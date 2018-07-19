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
// dtkCorePluginFactoryPrivate declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginFactoryPrivate : public QObject
{
    Q_OBJECT

public:
     dtkCorePluginFactoryPrivate(void) = default;
    ~dtkCorePluginFactoryPrivate(void) = default;

signals:
    void created(const QVariant&) const;

public:
    void touch(const QVariant&) const;

public:
    void    connect(class dtkCoreObjectManager *) const;
    void disconnect(      dtkCoreObjectManager *) const;
};

//
// dtkCorePluginFactory_p.h ends here
