// dtkCoreParameterObject.h
//

#pragma once

#include <dtkCoreExport>

#include <QtCore>

class dtkCoreParameter;

class DTKCORE_EXPORT dtkCoreParameterObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString doc READ doc WRITE setDoc NOTIFY docChanged)
    Q_PROPERTY(QString type READ type CONSTANT)

public:
     dtkCoreParameterObject(dtkCoreParameter *);
    ~dtkCoreParameterObject(void);

    void setLabel(const QString&);
    QString label(void) const;

    void setUnit(const QString&);
    QString unit(void) const;

    void setDoc(const QString&);
    QString doc(void) const;

    QString type(void) const;

signals:
    void labelChanged(const QString&);
    void unitChanged(const QString&);
    void docChanged(const QString&);

public:
    virtual dtkCoreParameter *parameter(void);

    void notifyLabel(const QString&);
    void notifyUnit(const QString&);
    void notifyDoc(const QString&);

private:
    dtkCoreParameter *m_parameter = nullptr;
};

//
// dtkCoreParameterObject.h ends here
