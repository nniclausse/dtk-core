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

#include "dtkCorePluginManagerHandler.h"

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginManagerPrivate
{
public:
    bool check(const QString& path, bool checkConceptLayer = true);
    bool checkConcept(const QString& path);
    bool checkVersion(const QString ref_version, const QString elem_version);

public:
    bool verboseLoading = false;
    bool autoLoading = true;
    QString layerVersion = QString();

public:
    QHash<QString, QPluginLoader *> loaders;
};

// ///////////////////////////////////////////////////////////////////

template <typename T> inline bool dtkCorePluginManagerPrivate<T>::checkConcept(const QString& path)
{
    QString conceptName = QMetaType::typeName(qMetaTypeId<T *>());
    conceptName.remove("Plugin*");

    QString pluginConcept = dtk::pluginManagerHandler().concept(path);

    if (conceptName != pluginConcept) {
        if (this->verboseLoading) {
            dtkDebug() << Q_FUNC_INFO << "skip plugin: not an implementation of the current concept" << conceptName << ", this plugin is for " << pluginConcept;
        }
        return false;
    }

    return true;
}

template <typename T> inline bool dtkCorePluginManagerPrivate<T>::check(const QString& path, bool checkConceptLayer)
{
    bool status = true;

    if (checkConceptLayer && !this->checkConcept(path)) {
        return false;
    }

    if (checkConceptLayer && !layerVersion.isNull() && !checkVersion(layerVersion , dtkCorePluginManagerHandler::instance()->pluginsLayerVersion(path))) {
        dtkWarn() << Q_FUNC_INFO << "Version mismatch: layer version " << layerVersion
                  << " plugin compiled for layer version" << dtk::pluginManagerHandler().pluginsLayerVersion(path)
                  << " for plugin " << path;
        return false;
    }

    for (QVariant item : dtk::pluginManagerHandler().dependencies(path)) {

        QVariantMap mitem = item.toMap();
        QString na_mitem = mitem.value("name").toString();
        QString ve_mitem = mitem.value("version").toString();
        QString key = dtk::pluginManagerHandler().pluginPath(na_mitem);

        if (!dtk::pluginManagerHandler().hasName(na_mitem)) {
            dtkWarn() << Q_FUNC_INFO << "Missing dependency:" << na_mitem << "for plugin" << path;
            status = false;
            continue;
        }

        if (!checkVersion(dtk::pluginManagerHandler().version(key), ve_mitem)) {
            dtkWarn() << Q_FUNC_INFO << "Version mismatch:" << na_mitem << "version" << dtk::pluginManagerHandler().version(key) << "but" << ve_mitem << "required for plugin" << path;
            status = false;
            continue;
        }

        if (!check(key, false)) {
            dtkWarn() << Q_FUNC_INFO << "Corrupted dependency:" << na_mitem << "for plugin" << path;
            status = false;
            continue;
        }
    }

    return status;
}

template <typename T> inline bool dtkCorePluginManagerPrivate<T>::checkVersion(const QString ref_version, const QString elem_version)
{
    QStringList ve_ref_list = ref_version.split(".");
    QStringList ve_elem_list = elem_version.split(".");

    //if major level different return false
    if (ve_ref_list.at(0).toInt() != ve_elem_list.at(0).toInt()) {
        return false;
    }

    //if minor level of ref < elem return false
    if (ve_ref_list.at(1).toInt() < ve_elem_list.at(1).toInt()) {
        return false;

    } else {
        // no patch level specified in ref
        if (ve_ref_list.size() < 3 || ve_elem_list.size() < 3) {
            return true;
        }

        //if same minor level, compare patch level
        if ((ve_ref_list.at(1).toInt() == ve_elem_list.at(1).toInt()) &&
            (ve_ref_list.at(2).toInt() < ve_elem_list.at(2).toInt())) {
            return false;
        }
        //else minor level of elem < ref , then don't compare patch level
    }

    return true;
}

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManager
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkCorePluginManager<T>::dtkCorePluginManager(void) : d(new dtkCorePluginManagerPrivate<T>)
{

}

template <typename T> inline dtkCorePluginManager<T>::~dtkCorePluginManager(void)
{
    delete d;
}

template <typename T> inline void dtkCorePluginManager<T>::setVerboseLoading(bool value)
{
    d->verboseLoading = value;
}

template <typename T> inline bool dtkCorePluginManager<T>::verboseLoading(void) const
{
    return d->verboseLoading;
}
template <typename T> inline void dtkCorePluginManager<T>::setAutoLoading(bool value)
{
    d->autoLoading = value;
}

template <typename T> inline bool dtkCorePluginManager<T>::autoLoading(void) const
{
    return d->autoLoading;
}

template <typename T> inline void dtkCorePluginManager<T>::loadFromName(const QString& plugin_name)
{
    QString full_name = plugin_name % "Plugin";

    auto i = dtk::pluginManagerHandler().namesBegin();
    auto e = dtk::pluginManagerHandler().namesEnd();

    while (i != e) {
        if (QString::compare(i.value(), full_name) == 0) {
            this->load(i.key());
            return;
        }
        ++i;
    }
    dtkWarn() << Q_FUNC_INFO << plugin_name << " not found ";
    dtkWarn() << Q_FUNC_INFO << "keys" << dtk::pluginManagerHandler().pluginPaths() << dtk::pluginManagerHandler().names();
}

template <typename T> inline void dtkCorePluginManager<T>::setLayerVersion(const QString& layer_version)
{
    d->layerVersion = layer_version;
}

template <typename T> void dtkCorePluginManager<T>::initialize(const QString& path)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    auto skip_empty_parts = Qt::SkipEmptyParts;
#else
    auto skip_empty_parts = QString::SkipEmptyParts;
#endif
    for (QString path2 : path.split(":", skip_empty_parts)) {
        if (path2.startsWith ("~/")) {
            path2.replace (0, 1, QDir::homePath());
        }

        QDir dir(path2);

        if (d->verboseLoading) {
            dtkTrace() << Q_FUNC_INFO << "scanning directory for plugins:" << path2;
        }

        for (QFileInfo info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
            dtk::pluginManagerHandler().scan(info.absoluteFilePath(), d->verboseLoading);

        if (d->autoLoading) {
            for (QFileInfo info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
                if (d->checkConcept(info.absoluteFilePath())) {
                    if (d->verboseLoading) {
                        dtkInfo() << Q_FUNC_INFO << "load" << info.absoluteFilePath();
                    }
                    this->load(info.absoluteFilePath());
                }
            }
        } else {
            dtkInfo() << Q_FUNC_INFO << "auto loading disabled";
        }
    }
}

template <typename T> inline void dtkCorePluginManager<T>::uninitialize(void)
{
    for (const QString& path : d->loaders.keys()) {
        this->unload(path);
    }
}

template <typename T> inline void dtkCorePluginManager<T>::load(const QString& path)
{
    if (!QLibrary::isLibrary(path)) {
        QString error = "Unable to load non library file " + path;
        if (d->verboseLoading) {
            dtkWarn() << Q_FUNC_INFO << error;
        }
        return;
    }

    if (!d->check(path)) {
        QString error = "check failure for plugin file " + path;
        if (d->verboseLoading) {
            dtkWarn() << Q_FUNC_INFO << error;
        }
        return;
    }

    QPluginLoader *loader = new QPluginLoader(path); // should not set this as parent to avoid bad deallocation

    if (!loader) {
        QString error = "Empty loader for file " + path;
        if (d->verboseLoading) {
            dtkWarn() << Q_FUNC_INFO << error;
        }
        return;
    }

    loader->setLoadHints(QLibrary::ExportExternalSymbolsHint);

    if (d->verboseLoading) {
        dtkTrace() << Q_FUNC_INFO << "Loading plugin from " << path;
    }

    if (!loader->load()) {
        QString error = "Unable to load ";
        error += path;
        error += " - ";
        error += loader->errorString();
        dtkWarn() << Q_FUNC_INFO << error;
        delete loader;
        return;
    }

    T *plugin = qobject_cast<T *>(loader->instance());

    if (!plugin) {
        QString error = "Unable to retrieve ";
        error += path;
        dtkWarn() << Q_FUNC_INFO << error;
        loader->unload();
        delete loader;
        return;
    }

    plugin->initialize();

    d->loaders.insert(path, loader);

    if (d->verboseLoading) {
        QString name =  loader->metaData().value("MetaData").toObject().value("name").toString();
        dtkTrace() << Q_FUNC_INFO << "Loaded plugin " <<  name  << " from " << path;
    }
}

template <typename T> inline void dtkCorePluginManager<T>::unload(const QString& path)
{
    QPluginLoader *loader = d->loaders.value(path);

    T *plugin = qobject_cast<T *>(loader->instance());

    if (plugin)
        plugin->uninitialize();

    if (loader->unload()) {
        d->loaders.remove(path);
        delete loader;
    } else {
        dtkWarn() << Q_FUNC_INFO << loader->errorString();
    }
}

template <typename T> inline QStringList dtkCorePluginManager<T>::plugins(void) const
{
    return d->loaders.keys();
}

template <typename T> inline QStringList dtkCorePluginManager<T>::availablePlugins(void) const
{
    return dtk::pluginManagerHandler().names();
}

//
// dtkCorePluginManager.tpp ends here
