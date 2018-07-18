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

#include "dtkCorePluginManagerHandler.h"

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerHandlerPrivate class
// /////////////////////////////////////////////////////////////////

class dtkCorePluginManagerHandlerPrivate
{
public:
    QHash<QString, QString> pluginsLayerVersion;
    QHash<QString, QVariantList> dependencies;

public:
    QHash<QString, QString> names;
    QHash<QString, QString> versions;
    QHash<QString, QString> concepts;
};

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerHandler implementation
// /////////////////////////////////////////////////////////////////

dtkCorePluginManagerHandler::dtkCorePluginManagerHandler(void) : d(new dtkCorePluginManagerHandlerPrivate)
{

}

dtkCorePluginManagerHandler *dtkCorePluginManagerHandler::instance(void)
{
    if (!s_instance) {
        s_instance = new dtkCorePluginManagerHandler;
    }
    return s_instance;
};

void dtkCorePluginManagerHandler::scan(const QString& path, bool verboseLoading)
{
    if (!QLibrary::isLibrary(path))
        return;

    if (d->names.contains(path) && verboseLoading) {
        dtkTrace() << Q_FUNC_INFO << "scan: skip path" << path << ", already scanned";
        return;
    }

    QPluginLoader *loader = new QPluginLoader(path);

    d->names.insert(path, loader->metaData().value("MetaData").toObject().value("name").toString());
    d->versions.insert(path, loader->metaData().value("MetaData").toObject().value("version").toString());
    d->concepts.insert(path, loader->metaData().value("MetaData").toObject().value("concept").toString());

    d->dependencies.insert(path, loader->metaData().value("MetaData").toObject().value("dependencies").toArray().toVariantList());
    d->pluginsLayerVersion.insert(path, loader->metaData().value("MetaData").toObject().value("layerVersion").toString());

    delete loader;
}

QString dtkCorePluginManagerHandler::pluginPath(const QString& name) const
{
    return d->names.key(name);
}

QString dtkCorePluginManagerHandler::name(const QString& path) const
{
    return d->names.value(path);
}

QString dtkCorePluginManagerHandler::version(const QString& path) const
{
    return d->versions.value(path);
}

QString dtkCorePluginManagerHandler::concept(const QString& path) const
{
    return d->concepts.value(path);
}

QVariantList dtkCorePluginManagerHandler::dependencies(const QString& path) const
{
    return d->dependencies.value(path);
}

QString dtkCorePluginManagerHandler::pluginsLayerVersion(const QString& path) const
{
    return d->pluginsLayerVersion.value(path);
}

bool dtkCorePluginManagerHandler::hasName(const QString& name) const
{
    for (const QString& n : d->names) {
        if (n == name) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerHandler::hasVersion(const QString& version) const
{
    for (const QString& v : d->versions) {
        if (v == version) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerHandler::hasConcept(const QString& concept) const
{
    for (const QString& c : d->concepts) {
        if (c == concept) {
            return true;
        }
    }
    return false;
}

auto dtkCorePluginManagerHandler::namesBegin(void) const -> const_iterator
{
    return d->names.cbegin();
}

auto dtkCorePluginManagerHandler::namesEnd(void) const -> const_iterator
{
    return d->names.cend();
}

auto dtkCorePluginManagerHandler::versionsBegin(void) const -> const_iterator
{
    return d->versions.cbegin();
}

auto dtkCorePluginManagerHandler::versionsEnd(void) const -> const_iterator
{
    return d->versions.cend();
}

auto dtkCorePluginManagerHandler::conceptsBegin(void) const -> const_iterator
{
    return d->concepts.cbegin();
}

auto dtkCorePluginManagerHandler::conceptsEnd(void) const -> const_iterator
{
    return d->concepts.cend();
}

QStringList dtkCorePluginManagerHandler::pluginPaths(void) const
{
    return d->names.keys();
}

QStringList dtkCorePluginManagerHandler::names(void) const
{
    return d->names.values();
}

QStringList dtkCorePluginManagerHandler::versions(void) const
{
    return d->versions.values();
}

QStringList dtkCorePluginManagerHandler::concepts(void) const
{
    return d->concepts.values();
}

dtkCorePluginManagerHandler *dtkCorePluginManagerHandler::s_instance = nullptr;

// ///////////////////////////////////////////////////////////////////
// Helper function implementation
// ///////////////////////////////////////////////////////////////////

namespace  dtk {
    dtkCorePluginManagerHandler& pluginManagerHandler(void)
    {
        return *(dtkCorePluginManagerHandler::instance());
    }
}

//
// dtkCorePluginManagerHandler.cpp ends here
