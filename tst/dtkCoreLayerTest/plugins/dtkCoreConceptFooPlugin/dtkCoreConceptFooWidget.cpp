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

#include "dtkCoreConceptFooWidget.h"
#include "dtkCoreConceptFoo.h"

#include <dtkCore>
#include <dtkLog>

class dtkCoreConceptFooWidgetPrivate
{
public:
    QMetaObject::Connection connection;
    dtkCoreConceptFoo *dtkConcept;

public:
    QSpinBox *id_sb;

public:
    void connect(void);
};

void dtkCoreConceptFooWidgetPrivate::connect(void)
{
    QObject::connect(this->id_sb, QOverload<int>::of(&QSpinBox::valueChanged), [this] (int v) {
        QVariantHash params;
        params["id"] = v;
        this->dtkConcept->setParameters(params);
    });
}

// ///////////////////////////////////////////////////////////////////

dtkCoreConceptFooWidget::dtkCoreConceptFooWidget(QWidget* parent) : QWidget(parent), d(new dtkCoreConceptFooWidgetPrivate)
{
    QVBoxLayout *main_lo = new QVBoxLayout();
    setLayout(main_lo);

    d->id_sb = new QSpinBox();
    d->id_sb->setObjectName("id_sb");
    d->id_sb->setMinimum(0);
    d->id_sb->setMaximum(30);
    d->id_sb->setValue(3);

    QLabel *id_lb = new QLabel(tr("Foo &Id"));
    id_lb->setToolTip("This parameter controls the id of the Foo object.");
    id_lb->setBuddy(d->id_sb);

    QHBoxLayout *id_lo = new QHBoxLayout();
    id_lo->addWidget(id_lb);
    id_lo->addWidget(d->id_sb);
    main_lo->addLayout(id_lo);

    d->connection = connect(&dtkCorePluginWidgetManager::instance(), &dtkCorePluginWidgetManager::added, [this] (const QVariant& v, QWidget *w) {

            if (w != this) {
                dtkTrace() << Q_FUNC_INFO << "Mismatch widget";
                return;
            }

            dtkAbstractCoreConcept *m = v.value<dtkAbstractCoreConcept *>();
            if (!m) {
                dtkTrace() << Q_FUNC_INFO << "Wrong dtkConcept";
                return;
            }

            d->dtkConcept = dynamic_cast<dtkCoreConceptFoo *>(m);
            if (!d->dtkConcept) {
                dtkTrace() << Q_FUNC_INFO << "Wrong implementation";
                return;
            }

            d->connect();
        });
}

dtkCoreConceptFooWidget::~dtkCoreConceptFooWidget(void)
{
    QObject::disconnect(d->connection);
    delete d;
}

//
// dtkCoreConceptFooWidget.cpp ends here
