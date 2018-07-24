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
// dtkCoreLayerManager interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreLayerManager
{
public:
    using PluginManagers  = QHash<QString, class dtkCorePluginManagerBase *>;
    using PluginFactories = QHash<QString, class dtkCorePluginFactoryBase *>;

     dtkCoreLayerManager(void);
    ~dtkCoreLayerManager(void);

    void record(const QString& plugin_manager_name, dtkCorePluginManagerBase *plugin_manager);
    void record(const QString& plugin_factory_name, dtkCorePluginFactoryBase *plugin_factory);

    void initialize(void);
    void initialize(const QString& path);

    void uninitialize(void);

    void setVerboseLoading(bool value);
    bool verboseLoading(void) const;

    void setAutoLoading(bool value);
    bool autoLoading(void) const;

    void setObjectManager(class dtkCoreObjectManager *manager);
    dtkCoreObjectManager *objectManager(void) const;

    PluginManagers pluginManagers(void) const;
    PluginFactories pluginFactories(void) const;

private:
    class dtkCoreLayerManagerPrivate *d;
};

//
// dtkCoreLayerManager.h ends here
