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

#include <QtCore>

#include <type_traits>

namespace dtk {
    namespace detail
    {
        template <class T>
        struct is_qobject_impl : std::is_base_of<QObject, std::remove_pointer_t<std::decay_t<T>>>
        {
        };
    }

    template <class T>
    using is_qobject = detail::is_qobject_impl<T>;

    template <class T>
    constexpr bool is_qobject_v = is_qobject<T>::value;
}

//
// dtkMetaType.tpp ends here
