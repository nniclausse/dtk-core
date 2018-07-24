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

#include <dtkCoreLayerTestExport>

#include <dtkCore>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class DTKCORELAYERTEST_EXPORT dtkAbstractCoreConcept : public QRunnable
{
public:
    virtual void setInput(const QVariant&) = 0;
    virtual void setParameters(const QVariantHash&) = 0;

    virtual QVariant output(void) const = 0;

    virtual void run(void) = 0;
};

// ///////////////////////////////////////////////////////////////////

DTK_DECLARE_OBJECT(        dtkAbstractCoreConcept *)
DTK_DECLARE_PLUGIN(        dtkAbstractCoreConcept, DTKCORELAYERTEST_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkAbstractCoreConcept, DTKCORELAYERTEST_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkAbstractCoreConcept, DTKCORELAYERTEST_EXPORT)

// ///////////////////////////////////////////////////////////////////
// Register dtkAbstractWatershedFilter to the layers
// ///////////////////////////////////////////////////////////////////

namespace dtkCoreLayerTest
{
    DTK_DECLARE_CONCEPT(dtkAbstractCoreConcept, DTKCORELAYERTEST_EXPORT, coreconcept);
}

//
// dtkAbstractCoreConcept.h ends here
