// Version: $Id$
//
//

// Code:

#pragma once

#include <dtkCoreExport>

#include <QString>

#include "dtkCoreParameters.h"

class DTKCORE_EXPORT dtkCoreParameterReader
{
public:
     dtkCoreParameterReader(const QString& json_file = QString());
    ~dtkCoreParameterReader(void);

public:
    void setJsonFile(const QString &json_file);
    bool read(void);

public:
    dtkCoreParameters parameters(void) const;

protected:
    class dtkCoreParameterReaderPrivate *d;
};
