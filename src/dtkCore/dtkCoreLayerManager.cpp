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

#include "dtkCoreLayerManager.h"

#include "dtkCorePluginManager.h"
#include "dtkCorePluginFactory.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkCoreLayerManagerPrivate implementation
// /////////////////////////////////////////////////////////////////

class dtkCoreLayerManagerPrivate
{
public:
    bool verbose_loading = false;
    bool auto_loading = true;

    dtkCoreObjectManager *object_manager = nullptr;

    QHash<QString, dtkCorePluginManagerBase *> plugin_managers;
    QHash<QString, dtkCorePluginFactoryBase *> plugin_factories;
};

// /////////////////////////////////////////////////////////////////
// dtkCoreLayerManager implementation
// /////////////////////////////////////////////////////////////////

dtkCoreLayerManager::dtkCoreLayerManager(void) : d(new dtkCoreLayerManagerPrivate)
{

}

dtkCoreLayerManager::~dtkCoreLayerManager(void)
{
    delete d;
}

void dtkCoreLayerManager::record(const QString& plugin_manager_name, dtkCorePluginManagerBase *plugin_manager)
{
    d->plugin_managers[plugin_manager_name] = plugin_manager;
}

void dtkCoreLayerManager::record(const QString& plugin_factory_name, dtkCorePluginFactoryBase *plugin_factory)
{
    d->plugin_factories[plugin_factory_name] = plugin_factory;
}

void dtkCoreLayerManager::initialize(void)
{
    this->initialize(QString());
}

void dtkCoreLayerManager::initialize(const QString& path)
{
    for (auto pm : d->plugin_managers) {
        pm->initialize(path);
    }
    if (d->object_manager) {
        for (auto pf : d->plugin_factories) {
            pf->connect(d->object_manager);
        }
    }
}

void dtkCoreLayerManager::uninitialize(void)
{
    for (auto pm : d->plugin_managers) {
        pm->uninitialize();
    }
    if (d->object_manager) {
        for (auto pf : d->plugin_factories) {
            pf->disconnect(d->object_manager);
        }
    }
}

void dtkCoreLayerManager::setVerboseLoading(bool value)
{
    for (auto pm : d->plugin_managers) {
        pm->setVerboseLoading(value);
    }
    d->verbose_loading = value;
}

bool dtkCoreLayerManager::verboseLoading(void) const
{
    return d->verbose_loading;
}

void dtkCoreLayerManager::setAutoLoading(bool value)
{
    for (auto pm : d->plugin_managers) {
        pm->setAutoLoading(value);
    }
    d->auto_loading = value;
}

bool dtkCoreLayerManager::autoLoading(void) const
{
    return d->auto_loading;
}

void dtkCoreLayerManager::setObjectManager(dtkCoreObjectManager * manager)
{
    d->object_manager = manager;
}

dtkCoreObjectManager *dtkCoreLayerManager::objectManager(void) const
{
    return d->object_manager;
}

auto dtkCoreLayerManager::pluginManagers(void) const -> PluginManagers
{
    return d->plugin_managers;
}

auto dtkCoreLayerManager::pluginFactories(void) const -> PluginFactories
{
    return d->plugin_factories;
}

//
// dtkCoreLayerManager.cpp ends here
