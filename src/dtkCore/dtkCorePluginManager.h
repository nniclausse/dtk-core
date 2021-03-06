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
// dtkCorePluginManagerBase interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginManagerBase
{
public:
    virtual ~dtkCorePluginManagerBase(void) = default;

    virtual void   initialize(const QString& path) = 0;
    virtual void uninitialize(void) = 0;

    virtual void setVerboseLoading(bool value) = 0;
    virtual bool verboseLoading(void) const = 0;

    virtual void setAutoLoading(bool value) = 0;
    virtual bool autoLoading(void) const = 0;

    virtual void   load(const QString& path) = 0;
    virtual void unload(const QString& path) = 0;

    virtual void loadFromName(const QString& plugin_name) = 0;
    virtual void setLayerVersion(const QString& layer_version) = 0;

    virtual QStringList plugins(void) const = 0;
    virtual QStringList availablePlugins(void) const = 0;
};

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManager declaration
// ///////////////////////////////////////////////////////////////////

template <typename T>
class dtkCorePluginManagerPrivate;

template <typename T>
class dtkCorePluginManager : public dtkCorePluginManagerBase
{
public:
     dtkCorePluginManager(void);
    ~dtkCorePluginManager(void);

    void   initialize(const QString& path) override;
    void uninitialize(void) override;

    void setVerboseLoading(bool value) override;
    bool verboseLoading(void) const override;

    void setAutoLoading(bool value) override;
    bool autoLoading(void) const override;

    void   load(const QString& path) override;
    void unload(const QString& path) override;

    void loadFromName(const QString& plugin_name) override;
    void setLayerVersion(const QString& layer_version) override;

    QStringList plugins(void) const override;
    QStringList availablePlugins(void) const override;

protected:
    dtkCorePluginManagerPrivate<T> *d;
};

#include "dtkCorePluginManager.tpp"

//
// dtkCorePluginManager.h ends here
