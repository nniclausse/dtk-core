// dtkCoreParameterCollection.cpp
//

#include <QtQml>

#include "dtkCoreParameterObject.h"
#include "dtkCoreParameterCollection.h"

class dtkCoreParameterCollectionPrivate
{
public:
    mutable QJSValue m_collection;
    mutable bool m_built = false;
};

dtkCoreParameterCollection::dtkCoreParameterCollection(void): base_type(), d(new dtkCoreParameterCollectionPrivate)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(std::initializer_list<std::pair<key_type, value_type>> list) : base_type(list), d(new dtkCoreParameterCollectionPrivate)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(const dtkCoreParameterCollection& o) : base_type(o), d(new dtkCoreParameterCollectionPrivate)
{
}

dtkCoreParameterCollection::dtkCoreParameterCollection(dtkCoreParameterCollection&& o) : base_type(o), d(new dtkCoreParameterCollectionPrivate)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(const dtkCoreParameters& o) : base_type(), d(new dtkCoreParameterCollectionPrivate)
{
    for (auto it = o.cbegin(); it != o.cend(); ++it) {
        this->insert(it.key(), it.value());
    }
}

dtkCoreParameterCollection& dtkCoreParameterCollection::operator = (const dtkCoreParameterCollection& o)
{
    base_type::operator=(o);
    return *this;
}

dtkCoreParameterCollection& dtkCoreParameterCollection::operator = (const dtkCoreParameters& o)
{
    self_type s(o);
    this->swap(s);
    return *this;
}

QJSValue dtkCoreParameterCollection::toJSValue(QObject *object) const
{
    if (!d->m_built) {
        QQmlEngine *js_engine = dynamic_cast<QQmlEngine*>(object);
        if (!js_engine) {
            QQmlContext *context = QQmlEngine::contextForObject(object);
            if (!context)
                return d->m_collection;
            else
                js_engine = context->engine();
        }

        d->m_collection = js_engine->newObject();
        for (auto it = this->begin(); it != this->end(); ++it) {
            d->m_collection.setProperty(it.key(), js_engine->newQObject(it.value()->object()));
        }
        d->m_built = true;
    }
    return d->m_collection;
}

QVariant dtkCoreParameterCollection::variant(const key_type& key) const
{
    return base_type::operator[](key)->variant();
}

QVariantMap dtkCoreParameterCollection::toVariantMap(void) const
{
    QVariantMap target_map;
    for (auto it = base_type::cbegin(); it != base_type::cend(); ++it) {
        target_map[it.key()] = it.value()->variant();
    }
    return target_map;
}

//
// end of dtkCoreParameterCollection.cpp
