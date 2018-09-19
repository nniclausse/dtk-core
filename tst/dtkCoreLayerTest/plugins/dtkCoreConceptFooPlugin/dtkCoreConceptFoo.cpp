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

#include "dtkCoreConceptFoo.h"
#include "dtkCoreConceptFoo_p.h"

#include <dtkCore>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class dtkCoreConceptFooPrivate
{
public:
    dtkCoreConceptFooData input;
    dtkCoreConceptFooData output;

    QVariantHash params;
};

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

dtkCoreConceptFoo::dtkCoreConceptFoo(void) : dtkAbstractCoreConcept(), d(new dtkCoreConceptFooPrivate)
{
    d->input.setId(-9999);
}

dtkCoreConceptFoo::~dtkCoreConceptFoo(void)
{
    delete d;
}

void dtkCoreConceptFoo::setInput(const QVariant& input)
{
    if (input.canConvert<dtkCoreConceptFooData>()) {
        d->input = input.value<dtkCoreConceptFooData>();
    }
}

void dtkCoreConceptFoo::setParameters(const QVariantHash& params)
{
    d->params = params;
}

QVariant dtkCoreConceptFoo::output(void) const
{
    return dtk::variantFromValue(d->output);
}

void dtkCoreConceptFoo::run(void)
{
    if (d->input.id() != -9999) {
        d->output = d->input;
    }

    if (d->params.contains("id")) {
        d->output.setId(d->params["id"].toInt());

    } else {
        d->output.setId(d->output.id() + 1);
    }
}

//
// dtkCoreConceptFoo.cpp ends here
