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


#include "dtkCoreMetaContainerSequential.h"

/*! \fn void dtkCoreMetaContainerSequential::insert(long long idx, const QVariant& v)

    Inserts the value wrapped into QVariant \a v at index position \a
    idx in the container. If \a idx is 0, the value is prepended to
    the container. If \a idx is size(), the value is appended to the
    container.

    \sa append(), prepend(), removeAt()
*/
void dtkCoreMetaContainerSequential::insert(long long idx, const QVariant& v)
{
    if (m_h->value_type_id == QMetaType::QVariant) {
        m_h->insert(idx, &v);

    } else {
        m_h->insert(idx, v.constData());
    }
}

/*! \fn void dtkCoreMetaContainerSequential::setAt(long long idx, const QVariant& v)

    Replaces the item at index position \a idx with the value wrapped
    into the QVariant \a v.

    \a idx must be a valid index position in the container (i.e., 0 <=
    \a idx < size()).

    \sa at(), operator[](), removeAt()
*/
void dtkCoreMetaContainerSequential::setAt(long long idx, const QVariant& v)
{
    if (m_h->value_type_id == QMetaType::QVariant) {
        m_h->setAt(idx, &v);

    } else {
        m_h->setAt(idx, v.constData());
    }
}

//
// dtkCoreMetaContainerSequential.cpp ends here
