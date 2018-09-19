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

#include <dtkCoreExport>

class DTKCORE_EXPORT dtkCoreApplicationPrivate
{
public:
    class QSettings *settings        = nullptr;
    class QCommandLineParser *parser = nullptr;
    class QCoreApplication *app      = nullptr;

public:
             dtkCoreApplicationPrivate(void);
    virtual ~dtkCoreApplicationPrivate(void);

    virtual void initialize(void);

    void setApplication(QCoreApplication *app);
};

//
// dtkCoreApplication_p.h ends here
