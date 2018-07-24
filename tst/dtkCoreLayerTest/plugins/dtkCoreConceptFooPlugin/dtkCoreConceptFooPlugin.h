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

#include <dtkCoreConceptFooPlugin/dtkCoreConceptFooPluginExport>

#include <dtkAbstractCoreConcept>

class DTKCORECONCEPTFOOPLUGIN_EXPORT dtkCoreConceptFooPlugin : public dtkAbstractCoreConceptPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkAbstractCoreConceptPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.dtkCoreConceptFooPlugin" FILE "dtkCoreConceptFooPlugin.json")

public:
     dtkCoreConceptFooPlugin(void) = default;
    ~dtkCoreConceptFooPlugin(void) = default;

    void initialize(void);
    void uninitialize(void);
};

//
// dtkCoreConceptFooPlugin.h ends here
