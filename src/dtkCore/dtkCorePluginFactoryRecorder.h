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
// dtkCorePluginFactoryRecorder interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginFactoryRecorder
{
public:
    explicit dtkCorePluginFactoryRecorder(class dtkCoreLayerManager *, class dtkCorePluginFactoryBase *, const QString&);
            ~dtkCorePluginFactoryRecorder(void) = default;
};

//
// dtkCorePluginFactoryRecorder.h ends here
