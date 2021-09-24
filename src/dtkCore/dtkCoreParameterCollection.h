// dtkCoreParameterCollection.h
//

#pragma once

#include <dtkCoreExport>

#include "dtkCoreParameter.h"

class DTKCORE_EXPORT dtkCoreParameterCollection : public QMap<QString, dtkCoreParameter *>
{
    using base_type = QMap<QString, dtkCoreParameter *>;
    using self_type = dtkCoreParameterCollection;

public:
    using key_type = base_type::key_type;
    using mapped_type = base_type::mapped_type;
    using value_type = dtkCoreParameter*;
    using size_type = base_type::size_type;
    using difference_type = base_type::difference_type;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = base_type::iterator;
    using const_iterator = base_type::const_iterator;
    using key_iterator = base_type::key_iterator;
    using key_value_iterator = base_type::key_value_iterator;
    using const_key_value_iterator = base_type::const_key_value_iterator;

public:
     dtkCoreParameterCollection(void) = default;
     dtkCoreParameterCollection(std::initializer_list<std::pair<key_type, value_type>> list);
     dtkCoreParameterCollection(const dtkCoreParameterCollection&);
     dtkCoreParameterCollection(dtkCoreParameterCollection&&);
     dtkCoreParameterCollection(const dtkCoreParameters&);
    ~dtkCoreParameterCollection(void) = default;

    dtkCoreParameterCollection& operator = (const dtkCoreParameterCollection&);
    dtkCoreParameterCollection& operator = (const dtkCoreParameters&);

    template <typename T, typename E = dtk::is_core_parameter<T>>
    const T&  parameter(const key_type&) const;
    template <typename T, typename E = dtk::is_core_parameter<T>>
    T& parameter(const key_type&);

    QVariant variant(const key_type&) const;

    QVariantMap toVariantMap(void) const;
};

Q_DECLARE_METATYPE(dtkCoreParameterCollection);

// ///////////////////////////////////////////////////////////////////

template <typename T, typename E>
inline const T& dtkCoreParameterCollection::parameter(const key_type& key) const
{
    static T default_p = T();
    if (this->find(key) != this->end()) {
        auto&& p = this->value(key);
        if (qMetaTypeId<T>() == p->typeId()) {
            return *reinterpret_cast<T *>(p);
        } else {
            dtkWarn() << Q_FUNC_INFO
                      << "Unable to cast into type" << QMetaType::typeName(qMetaTypeId<T>())
                      << "from type" << p->typeName()
                      << ". Default param is returned.";
        }
    }
    return default_p;
}

template <typename T, typename E>
inline T& dtkCoreParameterCollection::parameter(const key_type& key)
{
    static T default_p = T();
    if (this->find(key) != this->end()) {
        auto&& p = base_type::operator[](key);
        if (qMetaTypeId<T>() == p->typeId()) {
            return *reinterpret_cast<T *>(p);
        } else {
            dtkWarn() << Q_FUNC_INFO
                      << "Unable to cast into type" << QMetaType::typeName(qMetaTypeId<T>())
                      << "from type" << p->typeName()
                      << ". Default param is returned.";
        }
    }
    return default_p;
}

//
// end of dtkCoreParameterCollection.h
