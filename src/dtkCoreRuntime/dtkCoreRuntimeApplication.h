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

#include <dtkCoreRuntimeExport.h>

#include <dtkLog>

#include <QtCore>
#include <QtWidgets>

class DTKCORERUNTIME_EXPORT dtkCoreRuntimeApplication : public QApplication
{
public:
             dtkCoreRuntimeApplication(int& argc, char **argv);
    virtual ~dtkCoreRuntimeApplication(void);

public:
    virtual void initialize(void);

public:
    virtual bool noGui(void);

public:
    static dtkCoreRuntimeApplication *create(int& argc, char *argv[]) {
        for (int i = 0; i < argc; i++) {
            if (!qstrcmp(argv[i], "-nw") || !qstrcmp(argv[i], "--nw") ||  !qstrcmp(argv[i], "-no-window") || !qstrcmp(argv[i], "--no-window") || !qstrcmp(argv[i], "-h") || !qstrcmp(argv[i], "--help") || !qstrcmp(argv[i], "--version")) {
                qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("minimal"));
            }
        }

        return new dtkCoreRuntimeApplication(argc, argv);
    }

public:
    QCommandLineParser *parser(void);
    QSettings *settings(void);

protected:
    class dtkCoreApplicationPrivate *d;
};

//
// dtkCoreRuntimeApplication.h ends here
