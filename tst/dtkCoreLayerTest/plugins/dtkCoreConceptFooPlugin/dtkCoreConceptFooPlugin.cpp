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

#include "dtkCoreConceptFooPlugin.h"
#include "dtkCoreConceptFoo.h"
#include "dtkCoreConceptFooWidget.h"

#include <dtkCore>

// ///////////////////////////////////////////////////////////////////
// cgalVolumeMesherPlugin
// ///////////////////////////////////////////////////////////////////

void dtkCoreConceptFooPlugin::initialize(void)
{
    dtkCoreLayerTest::coreconcept::pluginFactory().record("dtkCoreConceptFoo", dtkCoreConceptFooCreator);
    dtkCoreLayerTest::coreconcept::pluginFactory().record("dtkCoreConceptFoo", dtkCoreConceptFooWidgetCreator);
}

void dtkCoreConceptFooPlugin::uninitialize(void)
{

}

// ///////////////////////////////////////////////////////////////////
// Plugin meta data
// ///////////////////////////////////////////////////////////////////

DTK_DEFINE_PLUGIN(dtkCoreConceptFoo)

//
// cgalVolumeMesherPlugin.cpp ends here
