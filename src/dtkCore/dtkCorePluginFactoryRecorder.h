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
class dtkCorePluginFactoryBase;

// /////////////////////////////////////////////////////////////////
// dtkCorePluginFactoryRecorder interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginFactoryRecorder
{
public:
    explicit dtkCorePluginFactoryRecorder(dtkCoreLayerManager *, dtkCorePluginFactoryBase *, const QString&);
            ~dtkCorePluginFactoryRecorder(void) = default;
};

//
// dtkCorePluginFactoryRecorder.h ends here
