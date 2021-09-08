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
    Q_PROPERTY(QString doc READ doc WRITE setDoc NOTIFY docChanged)

public:
     dtkCoreParameterObject(dtkCoreParameter *);
    ~dtkCoreParameterObject(void);

    void setLabel(const QString&);
    QString label(void) const;

    void setDoc(const QString&);
    QString doc(void) const;

signals:
    void labelChanged(const QString&);
    void docChanged(const QString&);

public:
    virtual dtkCoreParameter *parameter(void) const;

private:
    dtkCoreParameter *m_parameter = nullptr;
};

//
// dtkCoreParameterObject.h ends here
