// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkCoreConceptFoo_p.h"

dtkCoreConceptFooData::dtkCoreConceptFooData(const int& id, const QString& name) : m_id(id), m_name(name)
{
}

dtkCoreConceptFooData:: dtkCoreConceptFooData(const dtkCoreConceptFooData& o) : m_id(o.m_id), m_name(o.m_name)
{
}

dtkCoreConceptFooData& dtkCoreConceptFooData::operator = (const dtkCoreConceptFooData& o)
{
    m_id = o.m_id;
    m_name = o.m_name;
    return (*this);
}

bool dtkCoreConceptFooData::operator == (const dtkCoreConceptFooData& o) const
{
    if (m_id != o.m_id || m_name != o.m_name)
        return false;
    return true;
}

void dtkCoreConceptFooData::setId(const int& id)
{
    m_id = id;
}

void dtkCoreConceptFooData::setName(const QString& name)
{
    m_name = name;
}

int dtkCoreConceptFooData::id(void) const
{
    return m_id;
}

QString dtkCoreConceptFooData::name(void) const
{
    return m_name;
}
