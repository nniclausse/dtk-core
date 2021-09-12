// dtkCoreParameterPathObject.cpp
//

#include "dtkCoreParameterPathObject.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterPathObject implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreParameterPathObject::dtkCoreParameterPathObject(dtkCoreParameterPath *p) : dtkCoreParameterObject(p), m_param(p)
{

}

dtkCoreParameterPathObject::~dtkCoreParameterPathObject(void)
{
    m_param = nullptr;
}

void dtkCoreParameterPathObject::setPath(const QString& path)
{
    m_param->setPath(path);
}

QString dtkCoreParameterPathObject::path(void) const
{
    return m_param->path();
}

void dtkCoreParameterPathObject::setFilters(const QStringList& filters)
{
    m_param->setFilters(filters);
}

QStringList dtkCoreParameterPathObject::filters(void) const
{
    return m_param->filters();
}

QString dtkCoreParameterPathObject::dirName(void) const
{
    return m_param->dirName();
}

QString dtkCoreParameterPathObject::baseName(void) const
{
    return m_param->baseName();
}

dtkCoreParameterPath *dtkCoreParameterPathObject::parameter(void)
{
    return m_param;
}

void dtkCoreParameterPathObject::notifyPath(const QString& path)
{
    emit pathChanged(path);
}

void dtkCoreParameterPathObject::notifyFilters(const QStringList& filters)
{
    emit filtersChanged(filters);
}

//
// dtkCoreParameterPathObject.cpp ends here
