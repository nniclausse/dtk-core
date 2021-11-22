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

#include <dtkCoreExport>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCoreMetaType functions declarations
// ///////////////////////////////////////////////////////////////////

namespace dtk {

    template <typename T> bool canConvert(const QList<int>&);

    template <typename T> QVariant variantFromValue(const T&);

    template <typename T> T *clone(const T *);
    template <typename T> bool copy(const T *, T *);

    template <typename T> void    assign(T& lhs, const T& rhs);
    template <typename T> void addAssign(T& lhs, const T& rhs);
    template <typename T> void subAssign(T& lhs, const T& rhs);
    template <typename T> void mulAssign(T& lhs, const T& rhs);
    template <typename T> void divAssign(T& lhs, const T& rhs);

    DTKCORE_EXPORT  QString description(const QVariant& v);
    DTKCORE_EXPORT QVariant cloneContent(const QVariant& v);
    DTKCORE_EXPORT QVariant createEmptyContainer(const QVariant& v);
    DTKCORE_EXPORT     bool destroyPointer(QVariant& v);
}

// /////////////////////////////////////////////////////////////////
// Stream operators redefinition
// /////////////////////////////////////////////////////////////////

template <typename T> QDataStream& operator << (QDataStream& s, T   *t);
template <typename T> QDataStream& operator >> (QDataStream& s, T *& t);

template <typename T> QDataStream& operator << (QDataStream& s, const QList<T *>& l);
template <typename T> QDataStream& operator >> (QDataStream& s,       QList<T *>& l);

template <typename T> QDataStream& operator << (QDataStream& s, const QVector<T *>& v);
template <typename T> QDataStream& operator >> (QDataStream& s,       QVector<T *>& v);

template <typename T> QDataStream& operator << (QDataStream& s, const std::list<T *>& l);
template <typename T> QDataStream& operator >> (QDataStream& s,       std::list<T *>& l);

template <typename T> QDataStream& operator << (QDataStream& s, const std::vector<T *>& v);
template <typename T> QDataStream& operator >> (QDataStream& s,       std::vector<T *>& v);

// ///////////////////////////////////////////////////////////////////
// QMetaType for std::string
// ///////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(std::string)

DTKCORE_EXPORT QDebug& operator << (QDebug&, const std::string&);
DTKCORE_EXPORT QDataStream& operator<<(QDataStream&, const std::string&);
DTKCORE_EXPORT QDataStream& operator>>(QDataStream&, std::string&);

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaType.tpp"

// ///////////////////////////////////////////////////////////////////
// Helper funcion to load basic atomic int with respect to Qt Version
// ///////////////////////////////////////////////////////////////////

namespace dtk {
    namespace detail {
        template <typename T>
        T loadBasicAtomicInteger(const QBasicAtomicInteger<T>& a) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
            return a.loadRelaxed();
#else
            return a.load();
#endif
        }
    }
}

// ///////////////////////////////////////////////////////////////////
// Add std::array as sequential container
// ///////////////////////////////////////////////////////////////////

#include <array>

template <typename T, std::size_t N>
struct QMetaTypeId<std::array<T,N>>
{
    enum {
        Defined = QMetaTypeId2<T>::Defined
    };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (const int id = ::dtk::detail::loadBasicAtomicInteger(metatype_id))
            return id;
        const char *tName = QMetaType::typeName(qMetaTypeId<T>());
        const char *nName = QMetaType::typeName(qMetaTypeId<std::size_t>());
        Q_ASSERT(tName);
        const int tNameLen = int(qstrlen(tName));
        const int nNameLen = int(qstrlen(nName));
        QByteArray typeName;
        typeName.reserve(int(sizeof("std::array")) + 1 + tNameLen + 1 + nNameLen + 1);
        typeName.append("std::array", int(sizeof("std::array")) - 1)
            .append('<').append(tName, tNameLen)
            .append(',')
            .append(nName, nNameLen);
        typeName.append('>');
        const int newId = qRegisterNormalizedMetaType<std::array<T,N>>(
                        typeName,
                        reinterpret_cast<std::array<T,N> *>(quintptr(-1)));
        metatype_id.storeRelease(newId);
        return newId;
    }
};
namespace QtPrivate {
    template<typename T, std::size_t N>
    struct IsSequentialContainer<std::array<T,N>>
    {
        enum { Value = true };
    };
}

//
// dtkCoreMetaType.h ends here
