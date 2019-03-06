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

#include "dtkCoreParameter.h"

class DTKCORE_EXPORT dtkCoreSettings : public QSettings
{
public:

    explicit dtkCoreSettings(const QString& file_name) : QSettings(file_name, QSettings::IniFormat) {}
    explicit dtkCoreSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-core") {}
            ~dtkCoreSettings(void) = default;

    template<typename T>
        void track(dtkCoreParameter<T> *parameter) {

        this->setValue(parameter->name(), parameter->variant());

        connect(parameter, &dtkCoreParameter<T>::valueChanged, [=] (QVariant v) {
                this->setValue(parameter->name(), parameter->variant());
            });

    }

    QVariant restore(const QString& parameter_name) {

        return this->value(parameter_name);

    }
};

//
// dtkCoreSettings.h ends here
