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

template <typename T = void> class dtkCoreParameterSimpleObject
{
public:
     dtkCoreParameterSimpleObject<T>(dtkCoreParameterSimple<T> *) {}
    ~dtkCoreParameterSimpleObject<T>(void) = default;

    void notifyValue(const T&) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class DTKCORE_EXPORT dtkCoreParameterSimpleObject<QString> : public dtkCoreParameterStringObject
{
public:
     dtkCoreParameterSimpleObject<QString>(dtkCoreParameterSimple<QString> *p) : dtkCoreParameterStringObject(p) {}
    ~dtkCoreParameterSimpleObject<QString>(void) = default;

    void notifyValue(const QString& s) { emit valueChanged(s); }
};

// MACRO TO ADD TYPE OF SIMPLE PARAMETER OBJECT

#define DTK_PARAMETER_SIMPLE_OBJECT(type, name) \
class DTKCORE_EXPORT dtkCoreParameter##name##Object : public dtkCoreParameterObject { \
    Q_OBJECT                                                             \
    Q_PROPERTY(type value READ value WRITE setValue NOTIFY valueChanged) \
                                                                         \
public:                                                                  \
     dtkCoreParameter##name##Object(dtkCoreParameterSimple<type> *p) : dtkCoreParameterObject(p), m_param(p) {} \
    ~dtkCoreParameter##name##Object(void) { m_param = nullptr; }        \
    void setValue(const type& v) { m_param->setValue(v); }              \
    type value(void) const { return m_param->value(); }                 \
    dtkCoreParameterSimple<type> *parameter(void) override { return m_param; } \
                                                                        \
Q_SIGNALS:                                                              \
    void valueChanged(const type&);                                     \
                                                                        \
private:                                                                \
    dtkCoreParameterSimple<type> *m_param = nullptr;                    \
};                                                                      \
                                                                        \
template <> class DTKCORE_EXPORT dtkCoreParameterSimpleObject<type> : public dtkCoreParameter##name##Object \
{                                                                       \
public:                                                                 \
     dtkCoreParameterSimpleObject<type>(dtkCoreParameterSimple<type> *p) : dtkCoreParameter##name##Object(p) {}\
     ~dtkCoreParameterSimpleObject<type>(void) = default;               \
                                                                        \
     void notifyValue(const type& v) { emit valueChanged(v); }          \
};

//
// dtkCoreParameterStringObject.h ends here
