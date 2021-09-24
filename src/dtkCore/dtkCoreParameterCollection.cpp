// dtkCoreParameterCollection.cpp
//

#include "dtkCoreParameterCollection.h"

dtkCoreParameterCollection::dtkCoreParameterCollection(std::initializer_list<std::pair<key_type, value_type>> list) : base_type(list)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(const dtkCoreParameterCollection& o) : base_type(o)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(dtkCoreParameterCollection&& o) : base_type(o)
{

}

dtkCoreParameterCollection::dtkCoreParameterCollection(const dtkCoreParameters& o) : base_type()
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

QVariant dtkCoreParameterCollection::variant(const key_type& key) const
{
    return base_type::operator[](key)->variant();
}

QVariantMap dtkCoreParameterCollection::asVariantMap(void) const
{
    QVariantMap target_map;
    for (auto it = base_type::cbegin(); it != base_type::cend(); ++it) {
        target_map[it.key()] = it.value()->variant();
    }
    return target_map;
}

//
// end of dtkCoreParameterCollection.cpp
