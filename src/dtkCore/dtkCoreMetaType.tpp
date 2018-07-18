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
// dtkCoreMetaType functions implementations
// ///////////////////////////////////////////////////////////////////

namespace dtk {


    // Typetrait is_qobject to detect whether a class inherits from QObject or not
    namespace detail
    {
        template <typename T>
        struct is_qobject_impl : std::is_base_of<QObject, std::remove_pointer_t<std::decay_t<T>>>
        {
        };
    }

    template <typename T>
    using is_qobject = detail::is_qobject_impl<T>;


    // Typetrait is_instantiable to detect whether an object of the class can be instantiated or not
    namespace detail
    {
        template <typename T>
        struct is_instantiable_impl : public std::conditional_t<!std::is_abstract<std::remove_pointer_t<std::decay_t<T>>>::value, std::is_constructible<std::remove_pointer_t<std::decay_t<T>>>, std::false_type>
        {
        };
    }

    template <typename T>
    using is_instantiable = detail::is_instantiable_impl<T>;


    // Test conversion between list of types given as QMetaTypeId integers and template type
    namespace detail
    {
        template <typename T>
        std::enable_if_t<!std::is_pointer<T>::value, bool> can_convert(const QList<int>& types)
        {
            QVariant var = QVariant(qMetaTypeId<T>(reinterpret_cast<T *>(0)), 0);

            for (int i : types) {
                if (!var.canConvert(i)) {
                    return false;
                }
            }
            return true;
        }

        template <typename T>
        std::enable_if_t<std::is_pointer<T>::value && !dtk::is_instantiable<T>::value, bool> can_convert(const QList<int>& types)
        {
            using Type = std::remove_pointer_t<std::decay_t<T>>;
            int from = qMetaTypeId<Type *>();

            if (types.size() == 1 && types.first() == from) {
                return true;
            }
            for (int to : types) {
                if (!QMetaType::hasRegisteredConverterFunction(from, to)) {
                    return false;
                }
            }
            return true;
        }

        template <typename T>
        std::enable_if_t<std::is_pointer<T>::value && dtk::is_instantiable<T>::value, bool> can_convert(const QList<int>& types)
        {
            using Type = std::remove_pointer_t<std::decay_t<T>>;
            int from = qMetaTypeId<Type *>();

            if (types.size() == 1 && types.first() == from) {
                return true;
            }

            bool can_convert = true;
            Type *ptr = new Type();
            QVariant var = QVariant::fromValue(ptr);

            for (int to : types) {
                if (!(var.canConvert(to) || QMetaType::hasRegisteredConverterFunction(from, to))) {
                    can_convert = false;
                    break;
                }
            }
            delete ptr;

            return can_convert;
        }
    }

    template <typename T> inline bool canConvert(const QList<int>& types)
    {
        if (types.empty()) {
            return true;
        }
        return dtk::detail::can_convert<T>(types);
    }


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
// dtkCoreMetaType.tpp ends here
