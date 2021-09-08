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

    void setValue(QString);
    QString value(void) const;

signals:
    void valueChanged(QString);

public:
    dtkCoreParameterSimple<QString> *parameter(void) const override;

private:
    dtkCoreParameterSimple<QString> *m_param = nullptr;
};

//
// dtkCoreParameterStringObject.h ends here
