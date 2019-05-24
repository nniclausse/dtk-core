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

#include "dtkCoreLayerTest.h"

#include <dtkLog>

#include "dtkCoreLayerTestConfig.h"

// /////////////////////////////////////////////////////////////////
// Layer methods implementations
// /////////////////////////////////////////////////////////////////

namespace dtkCoreLayerTest {

    DTK_DEFINE_LAYER_MANAGER;

    void activateObjectManager(void) {
        manager().setObjectManager(dtkCoreObjectManager::instance());
    }

    void initialize(const QString& s) {

        QString path = s;
        if (path.isEmpty()) {
            QSettings settings;
            settings.beginGroup("imaging");
            path = settings.value("plugins").toString();
            settings.endGroup();
            if (path.isEmpty()) {
                path = QDir::cleanPath(DTKCORELAYERTEST_INSTALL_PREFIX + "/plugins/dtkCoreLayerTest");
                dtkDebug() << "no plugin path configured, use default:" << path;
            }
        }

        manager().initialize(path);
    }

    void setVerboseLoading(bool b)
    {
        manager().setVerboseLoading(b);
    }

    void uninitialize(void)
    {
        manager().uninitialize();
    }
}

//
// dtkCoreLayerTest.cpp ends here
