// dtkCoreParameterInListObject.cpp
//

#include "dtkCoreParameterInListObject.h"

dtkCoreParameterInListIntegerObject::dtkCoreParameterInListIntegerObject(dtkCoreParameterInList<qlonglong> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterInListIntegerObject::~dtkCoreParameterInListIntegerObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterInListIntegerObject::setList(const QList<qlonglong>& l)
{
    if (l != m_param->values()) {
        m_param->setValues(l);
    }
}

QList<qlonglong> dtkCoreParameterInListIntegerObject::list(void) const
{
    return m_param->values();
}

void dtkCoreParameterInListIntegerObject::setIndex(int i)
{
    if (i != m_param->valueIndex()) {
        m_param->setValueIndex(i);
    }
}

int dtkCoreParameterInListIntegerObject::index(void) const
{
    return m_param->valueIndex();
}

qlonglong dtkCoreParameterInListIntegerObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterInList<qlonglong> *dtkCoreParameterInListIntegerObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterInListRealObject::dtkCoreParameterInListRealObject(dtkCoreParameterInList<double> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterInListRealObject::~dtkCoreParameterInListRealObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterInListRealObject::setList(const QList<double>& l)
{
    if (l != m_param->values()) {
        m_param->setValues(l);
    }
}

QList<double> dtkCoreParameterInListRealObject::list(void) const
{
    return m_param->values();
}

void dtkCoreParameterInListRealObject::setIndex(int i)
{
    if (i != m_param->valueIndex()) {
        m_param->setValueIndex(i);
    }
}

int dtkCoreParameterInListRealObject::index(void) const
{
    return m_param->valueIndex();
}

double dtkCoreParameterInListRealObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterInList<double> *dtkCoreParameterInListRealObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterInListCharObject::dtkCoreParameterInListCharObject(dtkCoreParameterInList<char> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterInListCharObject::~dtkCoreParameterInListCharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterInListCharObject::setList(const QList<char>& l)
{
    if (l != m_param->values()) {
        m_param->setValues(l);
    }
}

QList<char> dtkCoreParameterInListCharObject::list(void) const
{
    return m_param->values();
}

void dtkCoreParameterInListCharObject::setIndex(int i)
{
    if (i != m_param->valueIndex()) {
        m_param->setValueIndex(i);
    }
}

int dtkCoreParameterInListCharObject::index(void) const
{
    return m_param->valueIndex();
}

char dtkCoreParameterInListCharObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterInList<char> *dtkCoreParameterInListCharObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterInListUcharObject::dtkCoreParameterInListUcharObject(dtkCoreParameterInList<uchar> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterInListUcharObject::~dtkCoreParameterInListUcharObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterInListUcharObject::setList(const QList<uchar>& l)
{
    if (l != m_param->values()) {
        m_param->setValues(l);
    }
}

QList<uchar> dtkCoreParameterInListUcharObject::list(void) const
{
    return m_param->values();
}

void dtkCoreParameterInListUcharObject::setIndex(int i)
{
    if (i != m_param->valueIndex()) {
        m_param->setValueIndex(i);
    }
}

int dtkCoreParameterInListUcharObject::index(void) const
{
    return m_param->valueIndex();
}

uchar dtkCoreParameterInListUcharObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterInList<uchar> *dtkCoreParameterInListUcharObject::parameter(void) const
{
    return m_param;
}

//

dtkCoreParameterInListStringObject::dtkCoreParameterInListStringObject(dtkCoreParameterInList<QString> *p) : dtkCoreParameterObject(p), m_param(p)
{
}

dtkCoreParameterInListStringObject::~dtkCoreParameterInListStringObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterInListStringObject::setList(const QList<QString>& l)
{
    if (l != m_param->values()) {
        m_param->setValues(l);
    }
}

QList<QString> dtkCoreParameterInListStringObject::list(void) const
{
    return m_param->values();
}

void dtkCoreParameterInListStringObject::setIndex(int i)
{
    if (i != m_param->valueIndex()) {
        m_param->setValueIndex(i);
    }
}

int dtkCoreParameterInListStringObject::index(void) const
{
    return m_param->valueIndex();
}

QString dtkCoreParameterInListStringObject::value(void) const
{
    return m_param->value();
}

dtkCoreParameterInList<QString> *dtkCoreParameterInListStringObject::parameter(void) const
{
    return m_param;
}

//
// dtkCoreParameterInListObject.cpp ends here
