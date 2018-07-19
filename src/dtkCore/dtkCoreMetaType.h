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

#pragma once

#include <dtkCoreExport>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaType functions declarations
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    template <typename T> bool canConvert(const QList<int>&);

    template <typename T> QVariant variantFromValue(const T&);

    template <typename T> T *clone(const T *);
    template <typename T> bool copy(const T *, T *);

    template <typename T> void    assign(T& lhs, const T& rhs);
    template <typename T> void addAssign(T& lhs, const T& rhs);
    template <typename T> void subAssign(T& lhs, const T& rhs);
    template <typename T> void mulAssign(T& lhs, const T& rhs);
    template <typename T> void divAssign(T& lhs, const T& rhs);

    DTKCORE_EXPORT  QString description(const QVariant& v);
    DTKCORE_EXPORT QVariant cloneContent(const QVariant& v);
    DTKCORE_EXPORT QVariant createEmptyContainer(const QVariant& v);
    DTKCORE_EXPORT     bool destroyPointer(QVariant& v);
}

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaType.tpp"

//
// dtkCoreMetaType.h ends here
