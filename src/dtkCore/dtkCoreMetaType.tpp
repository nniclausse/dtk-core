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

#include "dtkCoreTypeTraits.h"

#include <QtCore>

#include <type_traits>

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaType functions implementations
// ///////////////////////////////////////////////////////////////////

namespace dtk {


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

    template <typename T>
    inline bool canConvert(const QList<int>& types)
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
        std::enable_if_t<!dtk::is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            return QVariant::fromValue(t);
        }

        template <typename T>
        std::enable_if_t<dtk::is_qobject<T>::value, QVariant> variant_from_value(const T& t)
        {
            int class_type = QMetaType::type(t.metaObject()->className());

            if (class_type == QMetaType::UnknownType)
                return QVariant::fromValue(t);

            return QVariant(class_type, &t);
        }

        template <typename T>
        std::enable_if_t<dtk::is_qobject<T>::value, QVariant> variant_from_value(T * const & t)
        {
            QString class_name(t->metaObject()->className());
            int class_type = QMetaType::type(qPrintable(class_name + "*"));

            if (class_type == QMetaType::UnknownType) {
                return QVariant::fromValue(t);
            }

            return QVariant(class_type, &t, 1);
        }
    }

    template <typename T>
    inline QVariant variantFromValue(const T& t)
    {
        return dtk::detail::variant_from_value(t);
    }

    // Cloning an object by trying to downcasting as much as possible so that it avoids slicing
    namespace detail {

        template <typename T>
        std::enable_if_t<!dtk::is_clonable<T>::value, T *> clone_default(const T *t)
        {
            return nullptr;
        }

        template <typename T>
        std::enable_if_t<dtk::is_clonable<T>::value, T *> clone_default(const T *t)
        {
            using Type = std::remove_pointer_t<std::decay_t<T>>;
            return new Type(*t);
        }

        template <typename T>
        std::enable_if_t<!dtk::is_qobject<T>::value, T *> clone(const T *t)
        {
            return detail::clone_default(t);
        }

        template <typename T>
        std::enable_if_t<dtk::is_qobject<T>::value, T *> clone(const T *t)
        {
            QString class_name(t->metaObject()->className());
            int class_type = QMetaType::type(qPrintable(class_name));

            if (class_type == QMetaType::UnknownType) {
                return detail::clone_default(t);
            }
            return static_cast<T *>(QMetaType::create(class_type, t));
        }
    }

    template <typename T>
    inline T *clone(const T *t)
    {
        return dtk::detail::clone(t);
    }


    // Copying an object by trying to downcasting as much as possible so that it avoids slicing
    namespace detail
    {
        template <typename T>
        std::enable_if_t<!dtk::is_copyable<T>::value, bool> copy_default(const T *, T *)
        {
            return false;
        }

        template <typename T>
        std::enable_if_t<dtk::is_copyable<T>::value, bool> copy_default(const T *s, T *t)
        {
            *t = *s;
            return true;
        }

        template <typename T>
        std::enable_if_t<!dtk::is_qobject<T>::value, bool> copy(const T *s, T *t)
        {
            return detail::copy_default(s, t);
        }

        template <typename T>
        std::enable_if_t<dtk::is_qobject<T>::value, bool> copy(const T *s, T *t)
        {
            QString t_class_name(t->metaObject()->className());
            int t_class_type = QMetaType::type(qPrintable(t_class_name));

            QString s_class_name(s->metaObject()->className());
            int s_class_type = QMetaType::type(qPrintable(s_class_name));

            if (t_class_type == QMetaType::UnknownType || (t_class_type != s_class_type)) {
                return detail::copy_default(s, t);
            }

            QMetaType::construct(t_class_type, t, s);
            return true;
        }
    }

    template <typename T>
    inline bool copy(const T *s, T *t)
    {
        return dtk::detail::copy(s, t);
    }


    // Assign operation (aka =) when type supports it
    namespace detail
    {
        template <typename T>
        dtk::enable_assignment<T> assign(T& lhs, const T& rhs)
        {
            lhs = rhs;
        }

        template <typename T>
        dtk::disable_assignment<T> assign(T&, const T&)
        {
            dtkTrace() << Q_FUNC_INFO << "Current type does not support assignment";
        }
    }

    template <typename T>
    inline void assign(T& lhs, const T& rhs)
    {
        dtk::detail::assign(lhs, rhs);
    }


    // AddAssign operation (aka +=) when type supports it
    namespace detail
    {
        template <typename T>
        dtk::enable_add_assignment<T> add_assign(T& lhs, const T& rhs)
        {
            lhs += rhs;
        }

        template <typename T>
        dtk::disable_add_assignment<T> add_assign(T&, const T&)
        {
            dtkTrace() << Q_FUNC_INFO << "Current type does not support += operation";
        }
    }

    template <typename T>
    inline void addAssign(T& lhs, const T& rhs)
    {
        dtk::detail::add_assign(lhs, rhs);
    }


    // SubAssign operation (aka +=) when type supports it
    namespace detail
    {
        template <typename T>
        dtk::enable_sub_assignment<T> sub_assign(T& lhs, const T& rhs)
        {
            lhs -= rhs;
        }

        template <typename T>
        dtk::disable_sub_assignment<T> sub_assign(T&, const T&)
        {
            dtkTrace() << Q_FUNC_INFO << "Current type does not support -= operation";
        }
    }

    template <typename T>
    inline void subAssign(T& lhs, const T& rhs)
    {
        dtk::detail::sub_assign(lhs, rhs);
    }


    // MulAssign operation (aka +=) when type supports it
    namespace detail
    {
        template <typename T>
        dtk::enable_mul_assignment<T> mul_assign(T& lhs, const T& rhs)
        {
            lhs *= rhs;
        }

        template <typename T>
        dtk::disable_mul_assignment<T> mul_assign(T&, const T&)
        {
            dtkTrace() << Q_FUNC_INFO << "Current type does not support *= operation.";
        }
    }

    template <typename T>
    inline void mulAssign(T& lhs, const T& rhs)
    {
        dtk::detail::mul_assign(lhs, rhs);
    }


    // DivAssign operation (aka +=) when type supports it
    namespace detail
    {
        template <typename T>
        dtk::enable_div_assignment<T> div_assign(T& lhs, const T& rhs)
        {
            lhs /= rhs;
        }

        template <typename T>
        dtk::disable_div_assignment<T> div_assign(T&, const T&)
        {
            dtkTrace() << Q_FUNC_INFO << "Current type does not support /= operation.";
        }
    }

    template <typename T>
    inline void divAssign(T& lhs, const T& rhs)
    {
        dtk::detail::div_assign(lhs, rhs);
    }
}

//
// dtkCoreMetaType.tpp ends here
