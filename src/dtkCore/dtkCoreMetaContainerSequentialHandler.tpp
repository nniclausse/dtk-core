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
    dtk::detail::assign(*it, *static_cast<const container_value_type *>(t));
}

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

namespace dtk
{
    namespace detail
    {
        template <typename T> dtk::enable_assignment<T> assign(T& lhs, const T& rhs)
        {
            lhs = rhs;
        }

        template <typename T> dtk::disable_assignment<T> assign(T&, const T&)
        {
        }
    }
}

//
// dtkCoreMetaContainerSequentialHandler.tpp ends here
