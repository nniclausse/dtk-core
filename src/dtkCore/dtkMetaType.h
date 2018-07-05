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

class dtkMetaType
{
public:
    template <typename T> static QVariant variantFromValue(const T&);
};

// /////////////////////////////////////////////////////////////////

#include "dtkMetaType.tpp"

//
// dtkMetaType.h ends here
