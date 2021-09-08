// dtkCoreParameterInListObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterInList.h"

class DTKCORE_EXPORT dtkCoreParameterInListIntegerObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(QList<qlonglong> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(qlonglong value READ value)

public:
     dtkCoreParameterInListIntegerObject(dtkCoreParameterInList<qlonglong> *);
    ~dtkCoreParameterInListIntegerObject(void);

    void setList(const QList<qlonglong>&);
    QList<qlonglong> list(void) const;

    void setIndex(int);
    int index(void) const;

    qlonglong value(void) const;

signals:
    void listChanged(const QList<qlonglong>&);
    void indexChanged(int);

public:
    dtkCoreParameterInList<qlonglong> *parameter(void) const override;

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
    dtkCoreParameterInList<double> *parameter(void) const override;

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
    dtkCoreParameterInList<char> *parameter(void) const override;

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
    dtkCoreParameterInList<uchar> *parameter(void) const override;

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
    dtkCoreParameterInList<QString> *parameter(void) const override;

private:
    dtkCoreParameterInList<QString> *m_param = nullptr;
};



//
// dtkCoreParameterInListObject.h ends here
