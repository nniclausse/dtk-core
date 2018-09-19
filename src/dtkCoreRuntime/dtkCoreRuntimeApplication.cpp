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

#include "dtkCoreRuntimeApplication.h"

#include <dtkCore>

/*!
  \class dtkCoreRuntimeApplication
  \inmodule dtkWidgets
  \brief This class is used by GUI applications to provide their event loop. It is based on QApplication, and adds a few command line options to setup settings and dtkLog. It can also be used to start a non GUI appliation if the \tt{-nw} argument is given and the create method is called (it won't work if you use new directly)

    \code
   int main(int argc, char *argv[])
   {
    dtkCoreRuntimeApplication *application = dtkCoreRuntimeApplication::create(argc, argv);

    application->setApplicationName("myApp");
    application->setApplicationVersion("1.0.0");
    application->setOrganizationName("inria");
    application->setOrganizationDomain("fr");

    QCommandLineParser *parser = application->parser();
    parser->setApplicationDescription("my first DTK based application.");

    QCommandLineOption myOption("myopt", "enable myopt");
    parser->addOption(myOption);

    application->initialize();

    if (!parser->isSet(myOption)) {
       // do something
    }

    return application->exec();
   }
\endcode

If you run this application, \tt{--help} gives you:

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

/*! \fn dtkCoreRuntimeApplication::dtkCoreRuntimeApplication(int &argc, char **argv)

  Constructs a dtkCoreRuntimeApplication. Initializes the window system and constructs an application object with argc command line arguments in argv.

  The argc and argv arguments are processed by the application, and made available in a more convenient form by the arguments() function.

  Warning: The data referred to by \a argc and \a argv must stay valid for the entire lifetime of the dtkCoreApplication object. In addition, argc must be greater than zero and argv must contain at least one valid character string.
*/

dtkCoreRuntimeApplication::dtkCoreRuntimeApplication(int& argc, char **argv): QApplication(argc, argv)
{
    d = new dtkCoreApplicationPrivate;
    d->setApplication(this);
}

/*! \fn dtkCoreRuntimeApplication::~dtkCoreRuntimeApplication(void)

  Destroys the dtkCoreRuntimeApplication object.
*/

dtkCoreRuntimeApplication::~dtkCoreRuntimeApplication(void)
{
    delete d;

    d = NULL;
}

/*! \fn dtkCoreRuntimeApplication *create(int &argc, char *argv[])

  Helper function to create an instance of a dtkCoreRuntimeApplication. If the \tt{--nw} option is set, it will use a \e{minimal} \tt{QT_QPA_PLATFORM}. \a argc and \a argv are the usual parameters of a QCoreApplication.
*/

/*! \fn Qsettings dtkCoreRuntimeApplication::settings(void)

  Return the main QSettings.
*/
QSettings *dtkCoreRuntimeApplication::settings(void)
{
    return d->settings;
}


/*! \fn bool dtkCoreRuntimeApplication::noGui(void)

  Return true if the application is not a GUI application (ie. the \tt{-nw} was used in the command line)
*/

bool dtkCoreRuntimeApplication::noGui(void)
{
    return !(qApp && qobject_cast<QGuiApplication *>(qApp) && (QGuiApplication::platformName() != "minimal")) ;
}

/*! \fn QCommandLineParser *dtkCoreRuntimeApplication::parser(void)

  Return the main QCommandLineParser used by the application. It can be used to app specific options for your application.

*/
QCommandLineParser *dtkCoreRuntimeApplication::parser(void)
{
    return d->parser;
}

/*! \fn void dtkCoreRuntimeApplication::initialize(void)

 Initialize the command line parser. Should be called once all the specific options of your application are added in the parser.

 \sa parser
*/
void dtkCoreRuntimeApplication::initialize(void)
{
    d->initialize();
}

//
// dtkCoreRuntimeApplication.cpp ends here
