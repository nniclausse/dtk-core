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

#include "dtkCoreObjectManager.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreObjectManagerPrivate
// ///////////////////////////////////////////////////////////////////

class dtkCoreObjectManagerPrivate
{
public:
    QVariantHash instances;
};

// ///////////////////////////////////////////////////////////////////
// dtkCoreObjectManager implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreObjectManager *dtkCoreObjectManager::instance(void)
{
    if (!s_instance) {
        s_instance = new dtkCoreObjectManager;
    }

    return s_instance;
}

int dtkCoreObjectManager::count(void) const
{
    return d->instances.count();
}

void dtkCoreObjectManager::add(const QVariant& instance, const QString& name)
{
    d->instances.insert(name, instance);
}

void dtkCoreObjectManager::add(const QVariant& instance)
{
    static int count = 0;

    d->instances.insert(QString("%1 %2").arg(instance.typeName()).arg(count++), instance);
}

QVariant dtkCoreObjectManager::value(const QString& key) const
{
    return d->instances.value(key);
}

QStringList dtkCoreObjectManager::keys(void) const
{
    return d->instances.keys();
}

bool dtkCoreObjectManager::remove(const QVariant& v)
{
    QList<QString> keys;

    for (auto it = d->instances.begin(), end = d->instances.end(); it != end; ++it) {
        if (*it == v) {
            keys << it.key();
        }
    }
    for (auto&& k : keys) {
        d->instances.remove(k);
    }

    return (keys.size());
}

dtkCoreObjectManager::dtkCoreObjectManager(void) : d(new dtkCoreObjectManagerPrivate)
{

}

dtkCoreObjectManager::~dtkCoreObjectManager(void)
{
    delete d;
}

dtkCoreObjectManager *dtkCoreObjectManager::s_instance = nullptr;

// ///////////////////////////////////////////////////////////////////
// Helper function
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    dtkCoreObjectManager& objectManager(void)
    {
        return *(dtkCoreObjectManager::instance());
    }
}
//
// dtkCoreObjectManager.cpp ends here
