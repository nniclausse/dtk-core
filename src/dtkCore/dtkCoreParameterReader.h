// Version: $Id$
//
//

// Code:

#pragma once

#include <dtkCoreExport>

#include <QString>

class dtkCoreParameter;

class DTKCORE_EXPORT dtkCoreParameterReader
{
public:
     dtkCoreParameterReader(const QString& json_file = QString());
    ~dtkCoreParameterReader(void);

public:
    void setJsonFile(const QString &json_file);
    bool read(void);

public:
    QHash<QString, dtkCoreParameter *> parameters(void) const;

protected:
    class dtkCoreParameterReaderPrivate *d;
};
