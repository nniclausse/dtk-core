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

#include "dtkCorePluginFactoryRecorder.h"

#include "dtkCoreLayerManager.h"

// /////////////////////////////////////////////////////////////////
// dtkCorePluginFactoryRecorder implementation
// /////////////////////////////////////////////////////////////////

dtkCorePluginFactoryRecorder::dtkCorePluginFactoryRecorder(dtkCoreLayerManager *l_manager, dtkCorePluginFactoryBase *p_factory, const QString& p_name)
{
    l_manager->record(p_name, p_factory);
}

//
// dtkCorePluginFactoryRecorder.cpp ends here
