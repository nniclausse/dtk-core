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

#include <dtkCoreConceptFooPluginExport>

#include <QtWidgets>

class DTKCORECONCEPTFOOPLUGIN_EXPORT dtkCoreConceptFooWidget : public QWidget
{
public:
     dtkCoreConceptFooWidget(QWidget* parent = 0);
    ~dtkCoreConceptFooWidget(void);

private:
    class dtkCoreConceptFooWidgetPrivate *d;
};

// ///////////////////////////////////////////////////////////////////

inline QWidget *dtkCoreConceptFooWidgetCreator(void)
{
    return new dtkCoreConceptFooWidget();
}
//
// dtkCoreConceptFooWidget.h ends here
