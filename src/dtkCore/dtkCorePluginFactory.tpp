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

#include "dtkCoreMetaType.h"
#include "dtkCorePluginBase.h"
#include "dtkCorePluginFactory_p.h"

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactory implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkCorePluginFactory<T>::dtkCorePluginFactory(void) : m_d(new dtkCorePluginFactoryPrivate)
{

}

template <typename T> inline dtkCorePluginFactory<T>::~dtkCorePluginFactory(void)
{
    delete m_d;
}

template <typename T> inline void dtkCorePluginFactory<T>::record(const QString& key, creator func)
{
    if (this->creators.contains(key)) {
        dtkTrace() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }
    this->creators.insert(key, func);
}

template <typename T> inline void dtkCorePluginFactory<T>::recordPlugin(const QString& key, dtkCorePluginBase *plugin)
{
    if (this->creators_plugins.contains(key)) {
        dtkTrace() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }
    this->creators_plugins.insert(key, plugin);
}

template <typename T> inline void dtkCorePluginFactory<T>::record(const QString& key, widget_creator func)
{
    if (this->widget_creators.contains(key)) {
        dtkTrace() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }
    this->widget_creators.insert(key, func);
}

template <typename T> inline T *dtkCorePluginFactory<T>::create(const QString& key) const
{
    T *obj = nullptr;
    if (this->creators.contains(key)) {
        obj = this->creators.value(key)();

    } else if (this->creators_plugins.contains(key)) {
        void *o = this->creators_plugins.value(key)->create();
        if (!o) {
            dtkWarn() << Q_FUNC_INFO << "Nullptr is returned by plugin creator.";
            return nullptr;
        }
        obj = static_cast<T*>(o);
    }

    if (obj) {
        m_d->touch(dtk::variantFromValue(obj));
    }

    return obj;
}

template <typename T> inline QWidget *dtkCorePluginFactory<T>::createWidget(const QString& key) const
{
    if (this->widget_creators.contains(key)) {
        return this->widget_creators[key]();
    }
    return nullptr;
}

template <typename T> inline QStringList dtkCorePluginFactory<T>::keys(void) const
{
    QStringList lkeys = this->creators.keys() ;
    lkeys << this->creators_plugins.keys();
    return lkeys;
}

template <typename T> inline void dtkCorePluginFactory<T>::connect(dtkCoreObjectManager *manager) const
{
    m_d->connect(manager);
}

template <typename T> inline void dtkCorePluginFactory<T>::disconnect(dtkCoreObjectManager *manager) const
{
    m_d->disconnect(manager);
}

//
// dtkCorePluginFactory.tpp ends here
