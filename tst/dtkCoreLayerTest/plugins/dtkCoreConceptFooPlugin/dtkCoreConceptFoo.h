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

#include <dtkCoreConceptFooPlugin/dtkCoreConceptFooPluginExport>

#include <dtkAbstractCoreConcept>

class DTKCORECONCEPTFOOPLUGIN_EXPORT dtkCoreConceptFoo final : public dtkAbstractCoreConcept
{
public:
     dtkCoreConceptFoo(void);
	~dtkCoreConceptFoo(void);

    void setInput(const QVariant&);
    void setParameters(const QVariantHash&);

    QVariant output(void) const;

    void run(void);

protected:
    class dtkCoreConceptFooPrivate *d;
};

// ///////////////////////////////////////////////////////////////////

inline dtkAbstractCoreConcept *dtkCoreConceptFooCreator(void)
{
    return new dtkCoreConceptFoo();
}

//
// dtkCoreConceptFoo.h ends here
