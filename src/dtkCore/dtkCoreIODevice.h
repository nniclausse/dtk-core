#pragma once

#include <QtCore>
#include <dtkCoreExport.h>

namespace dtkCoreIODevice {

    DTKCORE_EXPORT QIODevice *create(const QString& file_name);
    DTKCORE_EXPORT QIODevice *create(const char* file_name);
}
