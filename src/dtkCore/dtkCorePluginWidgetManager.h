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

class DTKCORE_EXPORT dtkCorePluginWidgetManager : public QObject
{
    Q_OBJECT

public:
    static dtkCorePluginWidgetManager& instance(void);

    void add(const void *, const QVariant&, class QWidget *);

    int remove(const void *);
    int remove(QWidget *);

    void clear(void);

    QWidget *widget(const void *) const;
    QWidget   *take(const void *) const;

    QString description(void) const;

signals:
    void added(const QVariant&, QWidget *) const;

protected:
    static dtkCorePluginWidgetManager *s_instance;

     dtkCorePluginWidgetManager(void);
    ~dtkCorePluginWidgetManager(void);

    class dtkCorePluginWidgetManagerPrivate *d;
};

DTKCORE_EXPORT QDebug operator << (QDebug, dtkCorePluginWidgetManager&);

//
// dtkCorePluginWidgetManager.h ends here
