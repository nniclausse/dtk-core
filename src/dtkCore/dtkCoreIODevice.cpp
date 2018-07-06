#include "dtkCoreIODevice.h"
#include "dtkCoreConfig.h"

#if defined(DTK_HAVE_ZLIB)
#include <dtkCore/dtkCoreIOCompressor>
#endif

namespace dtkCoreIODevice {

    QIODevice *create(const char * file_name) { return dtkCoreIODevice::create(QString(file_name));}

    QIODevice *create(const QString& file_name) {
        if (QFileInfo(file_name).suffix() == "gz" ) {
#if defined(DTK_HAVE_ZLIB)
            QFile *file = new QFile(file_name);
            return new dtkCoreIOCompressor(file, true);
#endif
            qWarning() << "No zlib support, can't open compressed file !";
            return nullptr;
        } else {
            return new QFile(file_name);
        }
    }
}
