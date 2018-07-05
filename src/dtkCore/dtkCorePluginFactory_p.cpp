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

#include "dtkCorePluginFactory_p.h"
#include "dtkCoreObjectManager.h"

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactoryPrivate implementation
// ///////////////////////////////////////////////////////////////////


/*!
  \class dtkCorePluginFactoryPrivate
  \inmodule dtkCore
  \brief The dtkCorePluginFactoryPrivate class add signals to register object to object manager.
 */


/*! \fn void dtkCorePluginFactoryPrivate::touch(int type, void *t)
    Emits signal created(QVariant).
    The QVariant is defined by the QMetaType \a type and the address of the object \a t.
 */
void dtkCorePluginFactoryPrivate::touch(const QVariant &v) const
{
    emit created(v);
}

/*! \fn void dtkCorePluginFactoryPrivate::connect(dtkObjectManager *manager)
    Enables connection to \a manager.
 */
void dtkCorePluginFactoryPrivate::connect(dtkCoreObjectManager *manager) const
{
    QObject::connect(this, SIGNAL(created(const QVariant&)), manager, SLOT(add(const QVariant&)));
}

/*! \fn void dtkCorePluginFactoryPrivate::connect(dtkObjectManager *manager)
    Enables connection to \a manager.
 */
void dtkCorePluginFactoryPrivate::disconnect(dtkCoreObjectManager *manager) const
{
    QObject::disconnect(this, SIGNAL(created(const QVariant&)), manager, SLOT(add(const QVariant&)));
}

//
// dtkCorePluginFactory_p.cpp ends here
