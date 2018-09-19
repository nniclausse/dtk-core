// Version: $Id:
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkCoreLayerTestSettings.h"

/*!
 * \brief dtkCoreLayerTestSettings::dtkCoreLayerTestSettings
 *
 * Constructs settings containing a path to plugins
 */
dtkCoreLayerTestSettings::dtkCoreLayerTestSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-core-layer-test")
{
    this->beginGroup("core-layer-test");
    if(!this->allKeys().contains("plugins"))
        this->setValue("plugins", QString());
    this->sync();
    this->endGroup();
}

//
// dtkCoreLayerTestSettings.cpp ends here
