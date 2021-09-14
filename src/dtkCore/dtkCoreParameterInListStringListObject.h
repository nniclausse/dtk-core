// dtkCoreParameterInListStringListObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterInListStringList.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterInListStringListObject declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreParameterInListStringListObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList list  READ list  WRITE setList  NOTIFY  listChanged)
    Q_PROPERTY(int size READ size)

public:
    dtkCoreParameterInListStringListObject(dtkCoreParameterInListStringList *);
    ~dtkCoreParameterInListStringListObject(void);

    QStringList value(void) const;
    void setValue(const QStringList&);

    QStringList list(void) const;
    void setList(const QStringList&);

    int size(void) const;

signals:
    void valueChanged(const QStringList&);
    void  listChanged(const QStringList&);

public:
    void notifyValue(const QStringList&);
    void notifyList(const QStringList&);

public:
    dtkCoreParameterInListStringList *parameter(void) override;

private:
    dtkCoreParameterInListStringList *m_param = nullptr;
};

//
// dtkCoreParameterInListStringListObject.h ends here
