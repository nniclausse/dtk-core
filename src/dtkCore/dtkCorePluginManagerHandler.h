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

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerHandler declaration
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginManagerHandler
{
public:
    using const_iterator = QHash<QString, QString>::const_iterator;

    static dtkCorePluginManagerHandler *instance(void);

    QString pluginPath(const QString& name) const;

    QString    name(const QString& path) const;
    QString version(const QString& path) const;
    QString concept(const QString& path) const;

    QString pluginsLayerVersion(const QString& path) const;
    QVariantList   dependencies(const QString& path) const;

    bool    hasName(const QString& name) const;
    bool hasVersion(const QString& version) const;
    bool hasConcept(const QString& concept) const;

    void scan(const QString& path, bool verboseLoading = false);

    const_iterator namesBegin(void) const;
    const_iterator   namesEnd(void) const;

    const_iterator versionsBegin(void) const;
    const_iterator   versionsEnd(void) const;

    const_iterator conceptsBegin(void) const;
    const_iterator   conceptsEnd(void) const;

    QStringList pluginPaths(void) const;

    QStringList    names(void) const;
    QStringList versions(void) const;
    QStringList concepts(void) const;

private:
    dtkCorePluginManagerHandler(void);

    static dtkCorePluginManagerHandler *s_instance;

    class dtkCorePluginManagerHandlerPrivate *d;
};

// ///////////////////////////////////////////////////////////////////
// Helper function
// ///////////////////////////////////////////////////////////////////

namespace  dtk {
    DTKCORE_EXPORT dtkCorePluginManagerHandler& pluginManagerHandler(void);
}

//
// dtkCorePluginManagerHandler.h ends here
