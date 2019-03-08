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

#include <QtCore>

class DTKCORE_EXPORT dtkCoreSettings : public QSettings
{
public:
    explicit dtkCoreSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-core") {}
            ~dtkCoreSettings(void) = default;
};

//
// dtkCoreSettings.h ends here
