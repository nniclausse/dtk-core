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

#include <QtCore/QCoreApplication>

class DTKCORE_EXPORT dtkCoreApplication : public QCoreApplication
{
public:
             dtkCoreApplication(int& argc, char **argv);
    virtual ~dtkCoreApplication(void);

public:
    virtual void initialize(void);

public:
    static dtkCoreApplication *create(int& argc, char *argv[]);

public:
    class QCommandLineParser *parser(void) const;
    class QSettings *settings(void) const;

protected:
    class dtkCoreApplicationPrivate *d;
};

//
// dtkCoreApplication.h ends here
