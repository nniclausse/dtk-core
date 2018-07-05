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

#include "dtkCorePluginManagerRecorder.h"

#include "dtkCoreLayerManager.h"

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerRecorder implementation
// /////////////////////////////////////////////////////////////////

dtkCorePluginManagerRecorder::dtkCorePluginManagerRecorder(dtkCoreLayerManager *l_manager, dtkCorePluginManagerBase *p_manager, const QString& p_manager_name)
{
    l_manager->record(p_manager_name, p_manager);
}

//
// dtkCorePluginManagerRecorder.cpp ends here
