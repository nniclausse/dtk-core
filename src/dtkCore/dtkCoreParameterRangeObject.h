// dtkCoreParameterRangeObject.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameterObject.h"

#include "dtkCoreParameterRange.h"

class DTKCORE_EXPORT dtkCoreParameterRangeRealObject : public dtkCoreParameterObject
{
    Q_OBJECT
    Q_PROPERTY(std::array<double, 2> range READ range    WRITE setRange    NOTIFY rangeChanged)
    Q_PROPERTY(double max                  READ max      WRITE setMax      NOTIFY maxChanged)
    Q_PROPERTY(double min                  READ min      WRITE setMin      NOTIFY minChanged)
    Q_PROPERTY(int decimals                READ decimals WRITE setDecimals NOTIFY decimalsChanged)

public:
     dtkCoreParameterRangeRealObject(dtkCoreParameterRange<double> *);
    ~dtkCoreParameterRangeRealObject(void);

    void setRange(const std::array<double, 2>&);
    const std::array<double, 2>& range(void) const;

    void setMax(double);
    double max(void) const;

    void setMin(double);
    double min(void) const;

    void setDecimals(int);
    int decimals(void) const;

signals:
    void rangeChanged(const std::array<double, 2>&);
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
    Q_PROPERTY(std::array<qlonglong, 2> range READ range WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(qlonglong max                  READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(qlonglong min                  READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterRangeIntObject(dtkCoreParameterRange<qlonglong> *);
    ~dtkCoreParameterRangeIntObject(void);

    void setRange(const std::array<qlonglong, 2>&);
    const std::array<qlonglong, 2>& range(void) const;

    void setMax(qlonglong);
    qlonglong max(void) const;

    void setMin(qlonglong);
    qlonglong min(void) const;

signals:
    void rangeChanged(const std::array<qlonglong, 2>&);
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
    Q_PROPERTY(std::array<qulonglong, 2> range READ range WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(qulonglong max                  READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(qulonglong min                  READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterRangeUintObject(dtkCoreParameterRange<qulonglong> *);
    ~dtkCoreParameterRangeUintObject(void);

    void setRange(const std::array<qulonglong, 2>&);
    const std::array<qulonglong, 2>& range(void) const;

    void setMax(qulonglong);
    qulonglong max(void) const;

    void setMin(qulonglong);
    qulonglong min(void) const;

signals:
    void rangeChanged(const std::array<qulonglong, 2>&);
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
    Q_PROPERTY(std::array<char, 2> range READ range WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(char max                  READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(char min                  READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterRangeCharObject(dtkCoreParameterRange<char> *);
    ~dtkCoreParameterRangeCharObject(void);

    void setRange(const std::array<char, 2>&);
    const std::array<char, 2>& range(void) const;

    void setMax(char);
    char max(void) const;

    void setMin(char);
    char min(void) const;

signals:
    void rangeChanged(const std::array<char, 2>&);
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
    Q_PROPERTY(std::array<uchar, 2> range READ range WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(uchar max                  READ max   WRITE setMax   NOTIFY maxChanged)
    Q_PROPERTY(uchar min                  READ min   WRITE setMin   NOTIFY minChanged)

public:
     dtkCoreParameterRangeUcharObject(dtkCoreParameterRange<uchar> *);
    ~dtkCoreParameterRangeUcharObject(void);

    void setRange(const std::array<uchar, 2>&);
    const std::array<uchar, 2>& range(void) const;

    void setMax(uchar);
    uchar max(void) const;

    void setMin(uchar);
    uchar min(void) const;

signals:
    void rangeChanged(const std::array<uchar, 2>&);
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

    void notifyRange(const std::array<T, 2>& ) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMin(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyMax(T) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
    void notifyDecimals(int) { qDebug() << Q_FUNC_INFO << "Default impl nothing is done"; }
};

template <> class dtkCoreParameterRangeObject<double> : public dtkCoreParameterRangeRealObject
{
public:
     dtkCoreParameterRangeObject<double>(dtkCoreParameterRange<double> *p) : dtkCoreParameterRangeRealObject(p) {};
    ~dtkCoreParameterRangeObject<double>(void) = default;

    void notifyRange(const std::array<double, 2>& r) { emit rangeChanged(r); }
    void notifyMin(double m) { emit minChanged(m); }
    void notifyMax(double m) { emit maxChanged(m); }
    void notifyDecimals(int d) { emit decimalsChanged(d); }
};

template <> class dtkCoreParameterRangeObject<qlonglong> : public dtkCoreParameterRangeIntObject
{
public:
     dtkCoreParameterRangeObject<qlonglong>(dtkCoreParameterRange<qlonglong> *p) : dtkCoreParameterRangeIntObject(p) {};
    ~dtkCoreParameterRangeObject<qlonglong>(void) = default;

    void notifyRange(const std::array<qlonglong, 2>& r) { emit rangeChanged(r); }
    void notifyMin(qlonglong m) { emit minChanged(m); }
    void notifyMax(qlonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<qulonglong> : public dtkCoreParameterRangeUintObject
{
public:
     dtkCoreParameterRangeObject<qulonglong>(dtkCoreParameterRange<qulonglong> *p) : dtkCoreParameterRangeUintObject(p) {};
    ~dtkCoreParameterRangeObject<qulonglong>(void) = default;

    void notifyRange(const std::array<qulonglong, 2>& r) { emit rangeChanged(r); }
    void notifyMin(qulonglong m) { emit minChanged(m); }
    void notifyMax(qulonglong m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<char> : public dtkCoreParameterRangeCharObject
{
public:
     dtkCoreParameterRangeObject<char>(dtkCoreParameterRange<char> *p) : dtkCoreParameterRangeCharObject(p) {};
    ~dtkCoreParameterRangeObject<char>(void) = default;

    void notifyRange(const std::array<char, 2>& r) { emit rangeChanged(r); }
    void notifyMin(char m) { emit minChanged(m); }
    void notifyMax(char m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

template <> class dtkCoreParameterRangeObject<uchar> : public dtkCoreParameterRangeUcharObject
{
public:
     dtkCoreParameterRangeObject<uchar>(dtkCoreParameterRange<uchar> *p) : dtkCoreParameterRangeUcharObject(p) {};
    ~dtkCoreParameterRangeObject<uchar>(void) = default;

    void notifyRange(const std::array<uchar, 2>& r) { emit rangeChanged(r); }
    void notifyMin(uchar m) { emit minChanged(m); }
    void notifyMax(uchar m) { emit maxChanged(m); }
    void notifyDecimals(int) {}
};

//
// dtkCoreParameterRangeObject.h
