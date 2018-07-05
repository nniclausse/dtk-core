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

    namespace detail
    {
        template <class T>
        std::enable_if_t<!is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            return QVariant::fromValue(t);
        }

        template <class T>
        std::enable_if_t<is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            int class_type = QMetaType::type(t.metaObject()->className());

            if (class_type == QMetaType::UnknownType)
                return QVariant::fromValue(t);

            return QVariant(class_type, &t);
        }

        template <class T>
        std::enable_if_t<is_qobject<T>::value, QVariant> variant_from_value(T * const & t)
        {
            QString class_name(t->metaObject()->className());
            int class_type = QMetaType::type(qPrintable(class_name + "*"));

            if (class_type == QMetaType::UnknownType) {
                return QVariant::fromValue(t);
            }

            return QVariant(class_type, &t, 1);
        }
    }
}

namespace dtk {
    template <typename T> inline QVariant variantFromValue(const T& t)
    {
        return dtk::detail::variant_from_value(t);
    }
}

//
// dtkMetaType.tpp ends here
