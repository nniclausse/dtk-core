// dtkCoreParameterInListObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterInList.h"

class DTKCORE_EXPORT dtkCoreParameterInListIntObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<qlonglong> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(qlonglong value READ value)

public:
     dtkCoreParameterInListIntObject(dtkCoreParameterInList<qlonglong> *);
    ~dtkCoreParameterInListIntObject(void);

    void setList(const QList<qlonglong>&);
    QList<qlonglong> list(void) const;

    void setIndex(int);
    int index(void) const;

    qlonglong value(void) const;

signals:
    void listChanged(const QList<qlonglong>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<qlonglong> *parameter(void) override;

private:
    dtkCoreParameterInList<qlonglong> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterInListRealObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<double> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(double value READ value)

public:
     dtkCoreParameterInListRealObject(dtkCoreParameterInList<double> *);
    ~dtkCoreParameterInListRealObject(void);

    void setList(const QList<double>&);
    QList<double> list(void) const;

    void setIndex(int);
    int index(void) const;

    double value(void) const;

signals:
    void listChanged(const QList<double>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<double> *parameter(void) override;

private:
    dtkCoreParameterInList<double> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterInListCharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<char> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(char value READ value)

public:
     dtkCoreParameterInListCharObject(dtkCoreParameterInList<char> *);
    ~dtkCoreParameterInListCharObject(void);

    void setList(const QList<char>&);
    QList<char> list(void) const;

    void setIndex(int);
    int index(void) const;

    char value(void) const;

signals:
    void listChanged(const QList<char>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<char> *parameter(void) override;

private:
    dtkCoreParameterInList<char> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterInListUcharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<uchar> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(uchar value READ value)

public:
     dtkCoreParameterInListUcharObject(dtkCoreParameterInList<uchar> *);
    ~dtkCoreParameterInListUcharObject(void);

    void setList(const QList<uchar>&);
    QList<uchar> list(void) const;

    void setIndex(int);
    int index(void) const;

    uchar value(void) const;

signals:
    void listChanged(const QList<uchar>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<uchar> *parameter(void) override;

private:
    dtkCoreParameterInList<uchar> *m_param = nullptr;
};

//

template <typename T = void> class dtkCoreParameterInListObject
{
public:
     dtkCoreParameterInListObject<T>(dtkCoreParameterInList<T> *) {}
    ~dtkCoreParameterInListObject<T>(void) = default;

    void notifyList(const QList<T>&) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyIndex(int) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class dtkCoreParameterInListObject<qlonglong> : public dtkCoreParameterInListIntObject
{
public:
     dtkCoreParameterInListObject<qlonglong>(dtkCoreParameterInList<qlonglong> *p) : dtkCoreParameterInListIntObject(p) {};
    ~dtkCoreParameterInListObject<qlonglong>(void) = default;

    void notifyList(const QList<qlonglong>& l) { emit listChanged(l); }
    void notifyIndex(int id) { emit indexChanged(id); }
};

//

template <> class dtkCoreParameterInListObject<double> : public dtkCoreParameterInListRealObject
{
public:
     dtkCoreParameterInListObject<double>(dtkCoreParameterInList<double> *p) : dtkCoreParameterInListRealObject(p) {};
    ~dtkCoreParameterInListObject<double>(void) = default;

    void notifyList(const QList<double>& l) { emit listChanged(l); }
    void notifyIndex(int id) { emit indexChanged(id); }
};

//

template <> class dtkCoreParameterInListObject<char> : public dtkCoreParameterInListCharObject
{
public:
     dtkCoreParameterInListObject<char>(dtkCoreParameterInList<char> *p) : dtkCoreParameterInListCharObject(p) {};
    ~dtkCoreParameterInListObject<char>(void) = default;

    void notifyList(const QList<char>& l) { emit listChanged(l); }
    void notifyIndex(int id) { emit indexChanged(id); }
};

//

template <> class dtkCoreParameterInListObject<uchar> : public dtkCoreParameterInListUcharObject
{
public:
     dtkCoreParameterInListObject<uchar>(dtkCoreParameterInList<uchar> *p) : dtkCoreParameterInListUcharObject(p) {};
    ~dtkCoreParameterInListObject<uchar>(void) = default;

    void notifyList(const QList<uchar>& l) { emit listChanged(l); }
    void notifyIndex(int id) { emit indexChanged(id); }
};

// MACRO TO ADD TYPE OF INLIST PARAMETER OBJECT

#define DTK_PARAMETER_INLIST_OBJECT(type, name)                         \
class DTKCORE_EXPORT dtkCoreParameterInList##name##Object : public dtkCoreParameterObject { \
    Q_OBJECT                                                            \
    Q_PROPERTY(QList<type> list READ list WRITE setList NOTIFY listChanged) \
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged) \
    Q_PROPERTY(type value READ value)                                   \
                                                                        \
public:                                                                 \
     dtkCoreParameterInList##name##Object(dtkCoreParameterInList<type> *p) : dtkCoreParameterObject(p) {} \
    ~dtkCoreParameterInList##name##Object(void) { m_param = nullptr; }  \
    void setList(const QList<type>& l) { m_param-> setValues(l); }      \
    QList<type> list(void) const { return m_param->values(); }          \
    void setIndex(int i) { if (i != m_param->valueIndex()) m_param->setValueIndex(i); } \
    int index(void) const { return m_param->valueIndex(); }             \
    type value(void) const { return m_param->value(); }                 \
    dtkCoreParameterInList<type> *parameter(void) override { return m_param; } \
                                                                        \
Q_SIGNALS:                                                              \
    void listChanged(const QList<type>&);                               \
    void indexChanged(int);                                             \
                                                                        \
private:                                                                \
    dtkCoreParameterInList<type> *m_param = nullptr;                    \
};                                                                      \
                                                                        \
template <> class DTKCORE_EXPORT dtkCoreParameterInListObject<type> : public dtkCoreParameterInList##name##Object \
{                                                                       \
public:                                                                 \
      dtkCoreParameterInListObject<type>(dtkCoreParameterInList<type> *p) : dtkCoreParameterInList##name##Object(p) {}\
     ~dtkCoreParameterInListObject<type>(void) = default;               \
                                                                        \
     void notifyList(const QList<type>& l) { emit listChanged(l); }     \
     void notifyIndex(int i) { emit indexChanged(i); }                  \
};

// DEFINE THE OBJECT PARAMETER INLIST FOR QSTRING USING THE PREVIOUS MACRO

DTK_PARAMETER_INLIST_OBJECT(QString, String)

//
// dtkCoreParameterInListObject.h ends here
