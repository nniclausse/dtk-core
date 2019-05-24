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

#include "dtkCoreApplication.h"
#include "dtkCoreApplication_p.h"

#include <QtCore>

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
// dtkCoreApplicationPrivate implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreApplicationPrivate::dtkCoreApplicationPrivate(void) : settings(nullptr), parser(new QCommandLineParser), app(nullptr)
{
    this->parser->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
}

dtkCoreApplicationPrivate::~dtkCoreApplicationPrivate(void)
{
    if (this->settings) {
        delete this->settings;
        this->settings = nullptr;
    }

    delete this->parser;
    this->parser = nullptr;
}

void dtkCoreApplicationPrivate::setApplication(QCoreApplication *q)
{
    this->app = q;
}

void dtkCoreApplicationPrivate::initialize(void)
{
    // unset QT_PLUGIN_PATH, otherwise, kde plugins can change the qmetatype ids
    qputenv("QT_PLUGIN_PATH", "1");
    qputenv("LC_ALL", "C");
    QLocale::setDefault(QLocale::c());
    QSettings::setDefaultFormat(QSettings::IniFormat);

#if defined (Q_OS_UNIX) && !defined(Q_OS_MAC)
    // to avoid troubles with floats separators ('.' and not ',')
    setlocale(LC_NUMERIC, "C");
#endif

    this->parser->addHelpOption();
    this->parser->addVersionOption();

    QCommandLineOption settingsOption("settings", "main settings file", "filename");
    this->parser->addOption(settingsOption);

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));
    this->parser->addOption(verboseOption);

    QCommandLineOption nonguiOption(QStringList() << "nw" << "no-window", QCoreApplication::translate("main", "non GUI application (no window)"));
    this->parser->addOption(nonguiOption);

    QString verbosity = "info";
    QCommandLineOption loglevelOption("loglevel", "log level used by dtkLog (default is info), available: trace|debug|info|warn|error|fatal", "level", verbosity);
    this->parser->addOption(loglevelOption);

    QCommandLineOption logfileOption("logfile", qPrintable(QString("log file used by dtkLog; default is: ").append(dtkLogPath(app))), "filename | console", dtkLogPath(app));
    this->parser->addOption(logfileOption);

    QCommandLineOption logfileMaxSizeOption("logfilemax", "log file max size  (in MB); default is: 3072 (3GB)", "size");
    this->parser->addOption(logfileMaxSizeOption);

    this->parser->process(*(this->app));

    if (this->parser->isSet(settingsOption)) {
        this->settings = new QSettings(this->parser->value(settingsOption), QSettings::IniFormat);
    } else {
        this->settings = new QSettings();
    }

    if (settings->contains("log_level")) {
        dtkLogger::instance().setLevel(settings->value("log_level").toString());
    } else {
        if (this->parser->isSet(loglevelOption)) {
            verbosity = this->parser->value(loglevelOption);
        }

        dtkLogger::instance().setLevel(verbosity);
    }

    qlonglong max_size = 1024L * 1024L * 1024L;

    if (this->parser->isSet(logfileMaxSizeOption)) {
        max_size = this->parser->value(logfileMaxSizeOption).toLongLong() * 1024 * 1024;
    }

    if (this->parser->isSet(logfileOption)) {
        if (this->parser->value(logfileOption) == "console") {
            dtkLogger::instance().attachConsole();
        } else {
            dtkLogger::instance().attachFile(this->parser->value(logfileOption), max_size);
        }
    } else {
        dtkLogger::instance().attachFile(dtkLogPath(this->app), max_size);
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreApplication implementation
// ///////////////////////////////////////////////////////////////////

/*!
  \class dtkCoreApplication
  \inmodule dtkCore
  \brief This class is used by non-GUI applications to provide their
  event loop. It is based on QCoreApplication, and adds a few command
  line options to setup settings and dtkLog. For GUI applications, see
  dtkApplication in dtkWidgets.

  \code
   int main(int argc, char *argv[])
   {
    dtkCoreApplication application(argc, argv);

    application.setApplicationName("myApp");
    application.setApplicationVersion("1.0.0");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    QCommandLineParser *parser = application.parser();
    parser->setApplicationDescription("my first DTK based application.");

    QCommandLineOption myOption("myopt", "enable myopt");
    parser->addOption(myOption);

    application.initialize();

    if (!parser->isSet(myOption)) {
       // do something
    }

    return application.exec();
   }
   \endcode

   If you run this application, --help gives you:

   \code
Usage: ./bin/myApp [options]
my first DTK based application.

Options:
  --myopt                         enable myopt
  -h, --help                      Displays this help.
  -v, --version                   Displays version information.
  --settings <filename>           main settings file
  --verbose                       verbose plugin initialization
  --nw, --no-window               non GUI application (no window)
  --loglevel <level>              log level used by dtkLog (default is info),
                                  available: trace|debug|info|warn|error|fatal
  --logfile <filename | console>  log file used by dtkLog; default is:
                                  /user/nniclaus/home/.local/share/inria/myApp/m
                                  yApp.log
  --logfilemax <size>             log file max size  (in MB); default is: 3072
                                  (3GB)
   \endcode
*/

/*! \fn dtkCoreApplication::dtkCoreApplication(int &argc, char **argv)

    Constructs a dtkCoreApplication. Core applications are
    applications without a graphical user interface. Such applications
    are used at the console or as server processes.

    The argc and argv arguments are processed by the application, and
    made available in a more convenient form by the arguments()
    function.

    Warning: The data referred to by argc and argv must stay valid for
    the entire lifetime of the dtkCoreApplication object. In addition,
    argc must be greater than zero and argv must contain at least one
    valid character string.
*/
dtkCoreApplication::dtkCoreApplication(int& argc, char **argv): QCoreApplication(argc, argv), d(new dtkCoreApplicationPrivate)
{
    d->setApplication(this);
}

/*! \fn dtkCoreApplication::~dtkCoreApplication(void)

    Destroys the dtkCoreApplication object.
*/
dtkCoreApplication::~dtkCoreApplication(void)
{
    delete d;
}

/*! \fn Qsettings dtkCoreApplication::settings(void) const

    Return the main QSettings.
*/
QSettings *dtkCoreApplication::settings(void) const
{
    return d->settings;
}

/*! \fn QCommandLineParser *dtkCoreApplication::parser(void) const

    Return the main QCommandLineParser used by the application. It can
    be used to app specific options for your application.
*/
QCommandLineParser *dtkCoreApplication::parser(void) const
{
    return d->parser;
}

/*! \fn void dtkCoreApplication::initialize(void)

    Initialize the command line parser. Should be called once all the
    specific options of your application are added in the parser.

    \sa parser
*/
void dtkCoreApplication::initialize(void)
{
    d->initialize();
}

dtkCoreApplication *dtkCoreApplication::create(int& argc, char *argv[])
{
    return new dtkCoreApplication(argc, argv);
}

//
// dtkCoreApplication.cpp ends here
