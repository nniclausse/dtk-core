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

#include <dtkCoreLayerTestExport>

#include <dtkCore>

// /////////////////////////////////////////////////////////////////
// Layer methods declarations
// /////////////////////////////////////////////////////////////////

namespace dtkCoreLayerTest {

    DTKCORELAYERTEST_EXPORT dtkCoreLayerManager& manager(void);

    DTKCORELAYERTEST_EXPORT void activateObjectManager(void);

    DTKCORELAYERTEST_EXPORT void initialize(const QString& path = QString());
    DTKCORELAYERTEST_EXPORT void setVerboseLoading(bool b);
    DTKCORELAYERTEST_EXPORT void uninitialize(void);
}

//
// dtkCoreLayerTest.h ends here
