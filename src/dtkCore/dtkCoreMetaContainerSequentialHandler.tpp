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

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequentialHandlerTemplate::iterator
// ///////////////////////////////////////////////////////////////////

template < typename T >
inline dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::iterator(const container_iterator& iterator) : it(iterator)
{

}

template < typename T >
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::clone(void) const -> handler_iterator*
{
    return new iterator(it);
}

template < typename T >
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::copy(const handler_iterator& o)
{
    it = static_cast<const iterator&>(o).it;
}

template < typename T >
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::equal(const handler_iterator& o) const
{
    return it == static_cast<const iterator&>(o).it;
}

template < typename T >
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::advance(void)
{
    ++it;
}

template < typename T >
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::moveForward(long long step)
{
    std::advance(it, step);
}

template < typename T >
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::moveBackward(long long step)
{
    std::advance(it, -step);
}

template < typename T >
inline void *dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::value(void) const
{
    return &(*it);
}

template < typename T >
inline QVariant dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::variant(void) const
{
    return QVariant(qMetaTypeId<container_value_type>(), &(*it), QTypeInfo<container_value_type>::isPointer);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::assign(const void *t)
{
    dtk::assign(*it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::addAssign(const void *t)
{
    dtk::addAssign(*it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::subAssign(const void *t)
{
    dtk::subAssign(*it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::mulAssign(const void *t)
{
    dtk::mulAssign(*it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::divAssign(const void *t)
{
    dtk::divAssign(*it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::iterator::equalToValue(const void *t) const
{
    return (*it == *static_cast<const container_value_type *>(t));
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequentialHandlerTemplate::const_iterator
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::const_iterator(const container_const_iterator& iterator) : it(iterator)
{

}

template <typename T>
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::clone(void) const -> handler_const_iterator *
{
    return new const_iterator(it);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::copy(const handler_const_iterator& o)
{
    it = static_cast<const const_iterator&>(o).it;
}

template <typename T>
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::equal(const handler_const_iterator& o) const
{
    return it == static_cast<const const_iterator&>(o).it;
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::advance(void)
{
    ++it;
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::moveForward(long long step)
{
    std::advance(it, step);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::moveBackward(long long step)
{
    std::advance(it, -step);
}

template < typename T >
inline const void *dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::value(void) const
{
    return &(*it);
}

template <typename T>
inline QVariant dtkCoreMetaContainerSequentialHandlerTemplate<T>::const_iterator::variant(void) const
{
    return QVariant(qMetaTypeId<container_value_type>(), &(*it), QTypeInfo<container_value_type>::isPointer);
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequentialHandlerTemplate
// ///////////////////////////////////////////////////////////////////

template <typename T>
inline dtkCoreMetaContainerSequentialHandlerTemplate<T>::dtkCoreMetaContainerSequentialHandlerTemplate(T *c) : m_container(c)
{
}

template <typename T>
inline dtkCoreMetaContainerSequentialHandlerTemplate<T>::~dtkCoreMetaContainerSequentialHandlerTemplate(void)
{
    m_container = nullptr;
}

template <typename T>
inline QString dtkCoreMetaContainerSequentialHandlerTemplate<T>::description(void) const
{
    QString desc;
    QDebug dbg(&desc);
    dbg.nospace() << QMetaType::typeName(qMetaTypeId<T *>());
    dbg.nospace() << ", size = ";
    dbg.nospace() << this->size();
    dbg.nospace() << ", (";

    for (long long i = 0; i < this->size(); ++i) {
        if (i)
            dbg << ", ";

        dbg << *static_cast<const container_value_type *>(this->at(i));
    }

    dbg << ')';
    return desc;
}

template <typename T>
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::hasBiDirectionalIterator(void) const
{
    return dtk::is_bidirectional<typename T::iterator>::value;
}

template <typename T>
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::hasRandomAccessIterator(void) const
{
    return dtk::is_random_access<typename T::iterator>::value;
}

template <typename T>
inline bool dtkCoreMetaContainerSequentialHandlerTemplate<T>::empty(void) const
{
    return m_container->empty();
}

template <typename T>
inline long long dtkCoreMetaContainerSequentialHandlerTemplate<T>::size(void) const
{
    return m_container->size();
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::clear(void)
{
    m_container->clear();
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::reserve(long long size)
{
    this->reserve_impl<T>(size);
}

template <typename T> template <typename U>
inline dtk::enable_reserve<U> dtkCoreMetaContainerSequentialHandlerTemplate<T>::reserve_impl(long long size)
{
    m_container->reserve(size);
}

template <typename T> template <typename U>
inline dtk::disable_reserve<U> dtkCoreMetaContainerSequentialHandlerTemplate<T>::reserve_impl(long long)
{
    dtkTrace() << Q_FUNC_INFO << "This type of container does not support reserve operation.";
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::resize(long long size)
{
    this->resize_impl<T>(size);
}

template <typename T> template <typename U>
inline dtk::enable_resize<U> dtkCoreMetaContainerSequentialHandlerTemplate<T>::resize_impl(long long size)
{
    m_container->resize(size);
}

template <typename T> template <typename U>
inline dtk::disable_resize<U> dtkCoreMetaContainerSequentialHandlerTemplate<T>::resize_impl(long long)
{
    dtkTrace() << Q_FUNC_INFO << "This type of container does not support resize operation.";
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::append(const void *t)
{
    this->insert(this->size(), t);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::prepend(const void *t)
{
    this->insert(0, t);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::insert(long long idx, const void *t)
{
    typename T::iterator it(m_container->begin());
    std::advance(it, idx);
    m_container->insert(it, *static_cast<const container_value_type *>(t));
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::setAt(long long idx, const void *t)
{
    typename T::iterator it(m_container->begin());
    std::advance(it, idx);
    *it = *static_cast<const container_value_type *>(t);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::removeAt(long long idx)
{
    typename T::iterator it(m_container->begin());
    std::advance(it, idx);
    m_container->erase(it);
}

template <typename T>
inline const void *dtkCoreMetaContainerSequentialHandlerTemplate<T>::at(long long idx) const
{
    typename T::const_iterator it(m_container->begin());
    std::advance(it, idx);
    return &(*it);
}

template <typename T>
inline void *dtkCoreMetaContainerSequentialHandlerTemplate<T>::at(long long idx)
{
    typename T::iterator it(m_container->begin());
    std::advance(it, idx);
    return &(*it);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::variantAt(long long idx, QVariant& var)
{
    typename T::const_iterator it(m_container->cbegin());
    std::advance(it, idx);
    var.setValue(*it);
}

template <typename T>
inline void dtkCoreMetaContainerSequentialHandlerTemplate<T>::iteratorAt(long long idx, handler_iterator *pit)
{
    auto hit = static_cast<iterator *>(pit);
    hit->it = m_container->begin();
    std::advance(hit->it, idx);
}

template <typename T>
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::begin(void) -> handler_iterator *
{
    return new iterator(m_container->begin());
}

template <typename T>
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::cbegin(void) const -> handler_const_iterator *
{
    return new const_iterator(m_container->cbegin());
}

template <typename T>
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::end(void) -> handler_iterator *
{
    return new iterator(m_container->end());
}

template <typename T>
inline auto dtkCoreMetaContainerSequentialHandlerTemplate<T>::cend(void) const -> handler_const_iterator *
{
    return new const_iterator(m_container->cend());
}

// ///////////////////////////////////////////////////////////////////
// Register converter to dtkCoreMetaContainerSequential
// ///////////////////////////////////////////////////////////////////

namespace dtk
{
    // Functor that converts container pointer to dtkCoreMetaContainerSequentialHandler
    namespace detail
    {
        template <typename T>
        struct converter_to_meta_container_sequential_impl
        {
        };

        template <typename T>
        struct converter_to_meta_container_sequential_impl<T *>
        {
            dtkCoreMetaContainerSequentialHandler *operator () (T *container) const
            {
                return new dtkCoreMetaContainerSequentialHandlerTemplate<T>(container);
            }
        };
    }

    template <typename T>
    using converterToMetaContainerSequential = detail::converter_to_meta_container_sequential_impl<T>;


    // Registration of the above converter to the QMetaType system
    namespace detail
    {
        template <typename T,
          std::enable_if_t<!::dtk::is_container_value_type_meta_type<T>::value, int> = 0 >
        bool register_converter_to_meta_container_sequential_impl(int)
        {
            return false;
        }

        template <typename T,
          std::enable_if_t<::dtk::is_container_value_type_meta_type<T>::value, int> = 0 >
        bool register_converter_to_meta_container_sequential_impl(int id)
        {
            using handler = dtkCoreMetaContainerSequentialHandler;
            using converter = ::dtk::converterToMetaContainerSequential<T>;

            const int toId = qMetaTypeId<handler *>();

            if (!QMetaType::hasRegisteredConverterFunction(id, toId)) {
                converter o;
                return QMetaType::registerConverter<T, handler *, converter>(o);
            }
            return true;
        }

        template <typename T,
          std::enable_if_t<!::dtk::is_sequential_container_pointer<T>::value, int> = 0 >
        bool register_converter_to_meta_container_sequential(int)
        {
            return false;
        }

        template <typename T,
          std::enable_if_t<::dtk::is_sequential_container_pointer<T>::value, int> = 0 >
        bool register_converter_to_meta_container_sequential(int id)
        {
            return register_converter_to_meta_container_sequential_impl<T>(id);
        }
    }

    template <typename T>
    inline bool registerConverterToMetaContainerSequential(int id)
    {
        return detail::register_converter_to_meta_container_sequential<T>(id);
    }
}

//
// dtkCoreMetaContainerSequentialHandler.tpp ends here
