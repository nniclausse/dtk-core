// dtkCoreParameterRangeObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterRange.h"

class DTKCORE_EXPORT dtkCoreParameterRangeRealObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(double rmax  READ rmax     WRITE setRmax     NOTIFY rmaxChanged)
    Q_PROPERTY(double rmin  READ rmin     WRITE setRmin     NOTIFY rminChanged)
    Q_PROPERTY(double max   READ max      WRITE setMax      NOTIFY maxChanged)
    Q_PROPERTY(double min   READ min      WRITE setMin      NOTIFY minChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)

public:
     dtkCoreParameterRangeRealObject(dtkCoreParameterRange<double> *);
    ~dtkCoreParameterRangeRealObject(void);

    void setRmin(double);
    double rmin(void) const;

    void setRmax(double);
    double rmax(void) const;

    void setMax(double);
    double max(void) const;

    void setMin(double);
    double min(void) const;

    void setDecimals(int);
    int decimals(void) const;

signals:
    void rmaxChanged(double);
    void rminChanged(double);
    void maxChanged(double);
    void minChanged(double);
    void decimalsChanged(int);

public:
    dtkCoreParameterRange<double> *parameter(void) override;

private:
    dtkCoreParameterRange<double> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterRangeIntObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong rmax READ rmax WRITE setRmax NOTIFY rmaxChanged)
    Q_PROPERTY(qlonglong rmin READ rmin WRITE setRmin NOTIFY rminChanged)
    Q_PROPERTY(qlonglong max  READ max  WRITE setMax  NOTIFY maxChanged)
    Q_PROPERTY(qlonglong min  READ min  WRITE setMin  NOTIFY minChanged)

public:
     dtkCoreParameterRangeIntObject(dtkCoreParameterRange<qlonglong> *);
    ~dtkCoreParameterRangeIntObject(void);

    void setRmin(qlonglong);
    qlonglong rmin(void) const;

    void setRmax(qlonglong);
    qlonglong rmax(void) const;

    void setMax(qlonglong);
    qlonglong max(void) const;

    void setMin(qlonglong);
    qlonglong min(void) const;

signals:
    void rmaxChanged(qlonglong);
    void rminChanged(qlonglong);
    void maxChanged(qlonglong);
    void minChanged(qlonglong);

public:
    dtkCoreParameterRange<qlonglong> *parameter(void) override;

private:
    dtkCoreParameterRange<qlonglong> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterRangeUintObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(qulonglong rmax READ rmax WRITE setRmax NOTIFY rmaxChanged)
    Q_PROPERTY(qulonglong rmin READ rmin WRITE setRmin NOTIFY rminChanged)
    Q_PROPERTY(qulonglong max  READ max  WRITE setMax  NOTIFY maxChanged)
    Q_PROPERTY(qulonglong min  READ min  WRITE setMin  NOTIFY minChanged)

public:
     dtkCoreParameterRangeUintObject(dtkCoreParameterRange<qulonglong> *);
    ~dtkCoreParameterRangeUintObject(void);

    void setRmin(qulonglong);
    qulonglong rmin(void) const;

    void setRmax(qulonglong);
    qulonglong rmax(void) const;

    void setMax(qulonglong);
    qulonglong max(void) const;

    void setMin(qulonglong);
    qulonglong min(void) const;

signals:
    void rmaxChanged(qulonglong);
    void rminChanged(qulonglong);
    void maxChanged(qulonglong);
    void minChanged(qulonglong);

public:
    dtkCoreParameterRange<qulonglong> *parameter(void) override;

private:
    dtkCoreParameterRange<qulonglong> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterRangeCharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(char rmax READ rmax WRITE setRmax NOTIFY rmaxChanged)
    Q_PROPERTY(char rmin READ rmin WRITE setRmin NOTIFY rminChanged)
    Q_PROPERTY(char max  READ max  WRITE setMax  NOTIFY maxChanged)
    Q_PROPERTY(char min  READ min  WRITE setMin  NOTIFY minChanged)

public:
     dtkCoreParameterRangeCharObject(dtkCoreParameterRange<char> *);
    ~dtkCoreParameterRangeCharObject(void);

    void setRmin(char);
    char rmin(void) const;

    void setRmax(char);
    char rmax(void) const;

    void setMax(char);
    char max(void) const;

    void setMin(char);
    char min(void) const;

signals:
    void rmaxChanged(char);
    void rminChanged(char);
    void maxChanged(char);
    void minChanged(char);

public:
    dtkCoreParameterRange<char> *parameter(void) override;

private:
    dtkCoreParameterRange<char> *m_param = nullptr;
};

//

class DTKCORE_EXPORT dtkCoreParameterRangeUcharObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(uchar rmax READ rmax WRITE setRmax NOTIFY rmaxChanged)
    Q_PROPERTY(uchar rmin READ rmin WRITE setRmin NOTIFY rminChanged)
    Q_PROPERTY(uchar max  READ max  WRITE setMax  NOTIFY maxChanged)
    Q_PROPERTY(uchar min  READ min  WRITE setMin  NOTIFY minChanged)

public:
     dtkCoreParameterRangeUcharObject(dtkCoreParameterRange<uchar> *);
    ~dtkCoreParameterRangeUcharObject(void);

    void setRmin(uchar);
    uchar rmin(void) const;

    void setRmax(uchar);
    uchar rmax(void) const;

    void setMax(uchar);
    uchar max(void) const;

    void setMin(uchar);
    uchar min(void) const;

signals:
    void rmaxChanged(uchar);
    void rminChanged(uchar);
    void maxChanged(uchar);
    void minChanged(uchar);

public:
    dtkCoreParameterRange<uchar> *parameter(void) override;

private:
    dtkCoreParameterRange<uchar> *m_param = nullptr;
};

//

template <typename T = void> class dtkCoreParameterRangeObject : public dtkCoreParameterObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<T> *p) : dtkCoreParameterObject(p) {}
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyRmax(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMin(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMax(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyDecimals(int) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class dtkCoreParameterRangeObject<double> : public dtkCoreParameterRangeRealObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<double> *p) : dtkCoreParameterRangeRealObject(p) {};
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(double m) {emit rmaxChanged(m);}
    void notifyRmax(double m) {emit rminChanged(m);}
    void notifyMin(double m) { emit minChanged(m); }
    void notifyMax(double m) { emit maxChanged(m); }
    void notifyDecimals(int d) { emit decimalsChanged(d); }
};

template <> class dtkCoreParameterRangeObject<qlonglong> : public dtkCoreParameterRangeIntObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<qlonglong> *p) : dtkCoreParameterRangeIntObject(p) {};
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(qlonglong m) {emit rmaxChanged(m);}
    void notifyRmax(qlonglong m) {emit rminChanged(m);}
    void notifyMin(qlonglong m) { emit minChanged(m); }
    void notifyMax(qlonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<qulonglong> : public dtkCoreParameterRangeUintObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<qulonglong> *p) : dtkCoreParameterRangeUintObject(p) {};
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(qulonglong m) {emit rmaxChanged(m);}
    void notifyRmax(qulonglong m) {emit rminChanged(m);}
    void notifyMin(qulonglong m) { emit minChanged(m); }
    void notifyMax(qulonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<char> : public dtkCoreParameterRangeCharObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<char> *p) : dtkCoreParameterRangeCharObject(p) {};
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(char m) {emit rmaxChanged(m);}
    void notifyRmax(char m) {emit rminChanged(m);}
    void notifyMin(char m) { emit minChanged(m); }
    void notifyMax(char m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<uchar> : public dtkCoreParameterRangeUcharObject
{
public:
     dtkCoreParameterRangeObject(dtkCoreParameterRange<uchar> *p) : dtkCoreParameterRangeUcharObject(p) {};
    ~dtkCoreParameterRangeObject(void) = default;

    void notifyRmin(uchar m) {emit rmaxChanged(m);}
    void notifyRmax(uchar m) {emit rminChanged(m);}
    void notifyMin(uchar m) { emit minChanged(m); }
    void notifyMax(uchar m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

//
// dtkCoreParameterRangeObject.h
