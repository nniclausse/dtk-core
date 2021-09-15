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

class DTKCORE_EXPORT dtkCoreParameterInListStringObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QString value READ value)

public:
     dtkCoreParameterInListStringObject(dtkCoreParameterInList<QString> *);
    ~dtkCoreParameterInListStringObject(void);

    void setList(const QList<QString>&);
    QList<QString> list(void) const;

    void setIndex(int);
    int index(void) const;

    QString value(void) const;

signals:
    void listChanged(const QList<QString>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<QString> *parameter(void) override;

private:
    dtkCoreParameterInList<QString> *m_param = nullptr;
};

//

template <typename T = void> class dtkCoreParameterInListObject : public dtkCoreParameterObject
{
public:
     dtkCoreParameterInListObject<T>(dtkCoreParameterInList<T> *p) : dtkCoreParameterObject(p) {}
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

//

template <> class dtkCoreParameterInListObject<QString> : public dtkCoreParameterInListStringObject
{
public:
     dtkCoreParameterInListObject<QString>(dtkCoreParameterInList<QString> *p) : dtkCoreParameterInListStringObject(p) {};
    ~dtkCoreParameterInListObject<QString>(void) = default;

    void notifyList(const QList<QString>& l) { emit listChanged(l); }
    void notifyIndex(int id) { emit indexChanged(id); }
};

//
// dtkCoreParameterInListObject.h ends here
