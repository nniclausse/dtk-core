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

class QString;

// /////////////////////////////////////////////////////////////////
// dtkCoreLayerManager interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreLayerManager
{
public:
     dtkCoreLayerManager(void);
    ~dtkCoreLayerManager(void);

public:
    void record(const QString& plugin_manager_name, class dtkCorePluginManagerBase *plugin_manager);
    void record(const QString& plugin_factory_name, class dtkCorePluginFactoryBase *plugin_factory);

    void initialize(void);
    void initialize(const QString& path);

    void uninitialize(void);

    void setVerboseLoading(bool value);
    bool verboseLoading(void) const;

    void setAutoLoading(bool value);
    bool autoLoading(void) const;

    void setObjectManager(class dtkCoreObjectManager *manager);
    dtkCoreObjectManager *objectManager(void) const;

private:
    class dtkCoreLayerManagerPrivate *d;
};

//
// dtkCoreLayerManager.h ends here
