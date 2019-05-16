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

#include <dtkCoreRuntimeExport>

#include <QtWidgets/QApplication>

class QCommandLineParser;
class QSettings;

class DTKCORERUNTIME_EXPORT dtkCoreRuntimeApplication : public QApplication
{
public:
     dtkCoreRuntimeApplication(int& argc, char **argv);
    ~dtkCoreRuntimeApplication(void);

public:
    virtual void initialize(void);

public:
    virtual bool noGui(void);

public:
    static dtkCoreRuntimeApplication *create(int& argc, char *argv[]);

public:
    QCommandLineParser *parser(void);
    QSettings *settings(void);

protected:
    class dtkCoreApplicationPrivate *d;
};

//
// dtkCoreRuntimeApplication.h ends here
