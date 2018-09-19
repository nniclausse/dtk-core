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
class dtkCoreLayerManager;
class dtkCorePluginManagerBase;

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerRecorder interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginManagerRecorder
{
public:
    explicit dtkCorePluginManagerRecorder(dtkCoreLayerManager *, dtkCorePluginManagerBase *, const QString&);
            ~dtkCorePluginManagerRecorder(void) = default;
};

//
// dtkCorePluginManagerRecorder.h ends here
