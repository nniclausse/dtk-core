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

#include <functional>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactoryBase interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginFactoryBase
{
public:
    virtual ~dtkCorePluginFactoryBase(void) = default;

    virtual void    connect(class dtkCoreObjectManager *) const = 0;
    virtual void disconnect(      dtkCoreObjectManager *) const = 0;
};

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactory declaration
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginFactory : public dtkCorePluginFactoryBase
{
public:
     dtkCorePluginFactory(void);
    ~dtkCorePluginFactory(void);

public:
    typedef T *(*creator) ();
    typedef std::function<class QWidget *()> widget_creator;

public:
    void record(const QString& key, creator func);
    void recordPlugin(const QString& key, class dtkCorePluginBase *plugin);
    void record(const QString& key, widget_creator func);

public:
    T *create(const QString& key) const;

    QWidget *createWidget(const QString& key) const;

public:
    QStringList keys(void) const;

public:
    void    connect(dtkCoreObjectManager *) const override;
    void disconnect(dtkCoreObjectManager *) const override;

private:
    QHash<QString, creator> creators;
    QHash<QString, dtkCorePluginBase *> creators_plugins;
    QHash<QString, widget_creator> widget_creators;

private:
    class dtkCorePluginFactoryPrivate *m_d;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkCorePluginFactory.tpp"

//
// dtkCorePluginFactory.h ends here
