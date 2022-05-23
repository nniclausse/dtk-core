// dtkCoreParameterSimpleObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterSimple.h"

class DTKCORE_EXPORT dtkCoreParameterStringObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

public:
     dtkCoreParameterStringObject(dtkCoreParameterSimple<QString> *);
    ~dtkCoreParameterStringObject(void);

    void setValue(const QString&);
    QString value(void) const;

signals:
    void valueChanged(const QString&);

public:
    dtkCoreParameterSimple<QString> *parameter(void) override;

private:
    dtkCoreParameterSimple<QString> *m_param = nullptr;
};

//

template <typename T = void> class dtkCoreParameterSimpleObject : public dtkCoreParameterObject
{
public:
     dtkCoreParameterSimpleObject(dtkCoreParameterSimple<T> *p) : dtkCoreParameterObject(p) {}
    ~dtkCoreParameterSimpleObject(void) = default;

    void notifyValue(const T&) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class DTKCORE_EXPORT dtkCoreParameterSimpleObject<QString> : public dtkCoreParameterStringObject
{
public:
     dtkCoreParameterSimpleObject(dtkCoreParameterSimple<QString> *p) : dtkCoreParameterStringObject(p) {}
    ~dtkCoreParameterSimpleObject(void) = default;

    void notifyValue(const QString& s) { emit valueChanged(s); }
};

//
// dtkCoreParameterStringObject.h ends here
