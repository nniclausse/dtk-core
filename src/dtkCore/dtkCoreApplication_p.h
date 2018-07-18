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
             dtkCoreApplicationPrivate(void);
    virtual ~dtkCoreApplicationPrivate(void);

    virtual void initialize(void);

    void setApplication(class QCoreApplication *app);

public:
    class QSettings *settings        = nullptr;
    class QCommandLineParser *parser = nullptr;
          QCoreApplication *app      = nullptr;
};

//
// dtkCoreApplication_p.h ends here
