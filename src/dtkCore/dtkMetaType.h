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

class QVariant;

// ///////////////////////////////////////////////////////////////////
// dtkMetaType functions declarations
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    template <typename T> QVariant variantFromValue(const T&);
}

// /////////////////////////////////////////////////////////////////

#include "dtkMetaType.tpp"

//
// dtkMetaType.h ends here
