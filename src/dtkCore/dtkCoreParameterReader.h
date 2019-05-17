// Version: $Id$
//
//

// Code:

#pragma once

#include <dtkCoreExport>

#include <QtCore>

class dtkCoreParameter;

class DTKCORE_EXPORT dtkCoreParameterReader
{
public:
    dtkCoreParameterReader(const QString&);
    ~dtkCoreParameterReader(void);

public:
    QHash<QString, dtkCoreParameter *> parameters(void) const;

protected:
    class dtkCoreParameterReaderPrivate *d;
};
