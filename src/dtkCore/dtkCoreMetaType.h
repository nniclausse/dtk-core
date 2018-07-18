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

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaType functions declarations
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    template <typename T> bool canConvert(const QList<int>&);
    template <typename T> QVariant variantFromValue(const T&);
}

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaType.tpp"

//
// dtkCoreMetaType.h ends here
