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
// dtkCorePluginManagerRecorder interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginManagerRecorder
{
public:
    explicit dtkCorePluginManagerRecorder(class dtkCoreLayerManager *, class dtkCorePluginManagerBase *, const QString&);
            ~dtkCorePluginManagerRecorder(void) = default;
};

//
// dtkCorePluginManagerRecorder.h ends here
