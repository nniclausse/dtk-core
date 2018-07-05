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

// ///////////////////////////////////////////////////////////////////
// dtkMetaType functions implementations
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    // Typetrait is_qobject to detect whether a class inherits from QObject
    namespace detail
    {
        template <typename T>
        struct is_qobject_impl : std::is_base_of<QObject, std::remove_pointer_t<std::decay_t<T>>>
        {
        };
    }

    template <typename T>
    using is_qobject = detail::is_qobject_impl<T>;

    // Creating of a variant by downcasting the class as much as possible
    namespace detail
    {
        template <typename T>
        std::enable_if_t<!is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            return QVariant::fromValue(t);
        }

        template <typename T>
        std::enable_if_t<is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            int class_type = QMetaType::type(t.metaObject()->className());

            if (class_type == QMetaType::UnknownType)
                return QVariant::fromValue(t);

            return QVariant(class_type, &t);
        }

        template <typename T>
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

    template <typename T> inline QVariant variantFromValue(const T& t)
    {
        return dtk::detail::variant_from_value(t);
    }
}

//
// dtkMetaType.tpp ends here
