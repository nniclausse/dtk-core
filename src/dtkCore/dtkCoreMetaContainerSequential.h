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

#include "dtkCoreTypeTraits.h"
#include "dtkCoreMetaContainerSequentialHandler.h"

// /////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequential definition
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreMetaContainerSequential
{
public:
    using handler = dtkCoreMetaContainerSequentialHandler;


    struct iterator;
    struct DTKCORE_EXPORT item
    {
    private:
        friend struct iterator;
        friend class dtkCoreMetaContainerSequential;
        handler::iterator *it;


        explicit item(handler::iterator *iterator);

    public:
         item(const item& o) = delete;
         item(item&& o);
        ~item(void);

        item& operator = (const item& o);
        item& operator = (item&& o);

        bool operator == (const item& o) const;
        bool operator != (const item& o) const;

        const QVariant value(void) const;

        template <typename T> const T& value(void) const;

        template <typename T> item& operator  = (const T& t);
        template <typename T> item& operator += (const T& t);
        template <typename T> item& operator -= (const T& t);
        template <typename T> item& operator *= (const T& t);
        template <typename T> item& operator /= (const T& t);

        template <typename T> bool operator == (const T& t) const;
        template <typename T> bool operator != (const T& t) const;
    };


    struct DTKCORE_EXPORT iterator
    {
    private:
        friend class dtkCoreMetaContainerSequential;
        item proxy;


        explicit iterator(handler::iterator *iterator);

    public:
         iterator(const iterator& o);
         iterator(iterator&& o);
        ~iterator(void);

        iterator& operator = (const iterator& o);
        iterator& operator = (iterator&& o);

        bool operator == (const iterator& o) const;
        bool operator != (const iterator& o) const;

        item& operator *  (void);
        item& operator [] (long long j);

        template <typename T> T& value(void);

        iterator& operator ++ (void);
        iterator  operator ++ (int);
        iterator& operator -- (void);
        iterator  operator -- (int);
        iterator& operator += (long long j);
        iterator& operator -= (long long j);
        iterator  operator +  (long long j) const;
        iterator  operator -  (long long j) const;
    };


    struct DTKCORE_EXPORT const_iterator
    {
    private:
        friend class dtkCoreMetaContainerSequential;
        handler::const_iterator *it;


        explicit const_iterator(handler::const_iterator *iterator);

    public:
         const_iterator(const const_iterator& o);
         const_iterator(const_iterator&& o);
        ~const_iterator(void);

        const_iterator& operator = (const const_iterator& o);
        const_iterator& operator = (const_iterator&& o);

        bool operator == (const const_iterator& o) const;
        bool operator != (const const_iterator& o) const;

        QVariant operator *  (void)        const;
        QVariant operator [] (long long j) const;

        const_iterator& operator ++ (void);
        const_iterator  operator ++ (int);
        const_iterator& operator -- (void);
        const_iterator  operator -- (int);
        const_iterator& operator += (long long j);
        const_iterator& operator -= (long long j);
        const_iterator  operator +  (long long j) const;
        const_iterator  operator -  (long long j) const;
    };


     dtkCoreMetaContainerSequential(handler *h);
     dtkCoreMetaContainerSequential(dtkCoreMetaContainerSequential&& o);
    ~dtkCoreMetaContainerSequential(void);

    bool hasBiDirectionalIterator(void) const;
    bool  hasRandomAccessIterator(void) const;

    bool      empty(void) const;
    long long  size(void) const;

    void   clear(void);
    void reserve(long long size);
    void  resize(long long size);

    template <typename T> void  append(const T& t);
    template <typename T> void prepend(const T& t);

    void  append(const QVariant& v);
    void prepend(const QVariant& v);

    template <typename T> void insert(long long idx, const T& t);
    template <typename T> void  setAt(long long idx, const T& t);

    void insert(long long idx, const QVariant& v);
    void  setAt(long long idx, const QVariant& v);

    const QVariant& at(long long idx) const;

    template <typename T> const T& at(long long idx) const;

    void removeAt(long long idx);

    const QVariant& first(void) const;
    item& first(void);

    const QVariant& last(void) const;
    item& last(void);

    const QVariant& operator [] (long long idx) const;
    item& operator [] (long long idx);

    iterator begin(void);
    iterator   end(void);

    const_iterator begin(void) const;
    const_iterator   end(void) const;

    const_iterator cbegin(void) const;
    const_iterator   cend(void) const;

protected:
    friend QDebug& operator << (QDebug debug, const dtkCoreMetaContainerSequential& container);

protected:
    handler *m_h;
    item *m_proxy;
    mutable QVariant m_var;
};

// ///////////////////////////////////////////////////////////////////

namespace dtk
{
    using metaSequentialContainer = dtkCoreMetaContainerSequential;
}

// ///////////////////////////////////////////////////////////////////
// Debug operator
// ///////////////////////////////////////////////////////////////////

QDebug& operator << (QDebug debug, const dtkCoreMetaContainerSequential& container);

// /////////////////////////////////////////////////////////////////
// MACRO REGISTERING POINTERS OF CONTAINERS INTO QMETATYPE SYSTEM
// /////////////////////////////////////////////////////////////////

#define DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(CONTAINER_ARG)                   \
template <typename T>                                                             \
struct QMetaTypeId< CONTAINER_ARG<T> * >                                          \
{                                                                                 \
    enum {                                                                        \
        Defined = QMetaTypeId2<T>::Defined                                        \
    };                                                                            \
    static int qt_metatype_id()                                                   \
    {                                                                             \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);       \
        if (const int id = metatype_id.loadRelaxed())                                    \
            return id;                                                            \
        const char *tName = QMetaType::typeName(qMetaTypeId<T>());                \
        Q_ASSERT(tName);                                                          \
        const int tNameLen = int(qstrlen(tName));                                 \
        QByteArray typeName;                                                      \
        typeName.reserve(int(sizeof(#CONTAINER_ARG)) + 1 + tNameLen + 1 + 1 + 1); \
        typeName.append(#CONTAINER_ARG, int(sizeof(#CONTAINER_ARG)) - 1)          \
            .append('<').append(tName, tNameLen).append('>');                     \
        typeName.append('*');                                                     \
        const int newId = qRegisterNormalizedMetaType< CONTAINER_ARG<T> * >(      \
                        typeName,                                                 \
                        reinterpret_cast< CONTAINER_ARG<T> **>(quintptr(-1)));    \
        metatype_id.storeRelease(newId);                                          \
        if (newId > 0) {                                                          \
            dtk::registerConverterToMetaContainerSequential< CONTAINER_ARG<T> * >(newId);  \
        }                                                                         \
        return newId;                                                             \
    }                                                                             \
};                                                                                \
template <typename T>                                                             \
struct dtk::is_sequential_container_pointer< CONTAINER_ARG<T> * > : std::true_type {};

// /////////////////////////////////////////////////////////////////
// Register standard containers as a sequential container pointer
// /////////////////////////////////////////////////////////////////

DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(QList);
DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(QVector);
DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(QVarLengthArray);
DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(std::list);
DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(std::vector);

// /////////////////////////////////////////////////////////////////
// Register QStringList* as a sequential container pointer
// /////////////////////////////////////////////////////////////////

template <> struct QMetaTypeId<QStringList *> {
    enum {
        Defined = QMetaTypeId2<QString>::Defined
    };

    static int qt_metatype_id() {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);

        if (const int id = metatype_id.loadRelaxed())
            return id;

        QByteArray typeName("QStringList*", 12);

        const int newId = qRegisterNormalizedMetaType<QStringList *>(typeName, reinterpret_cast<QStringList **>(quintptr(-1)));
        metatype_id.storeRelease(newId);

        if (newId > 0) {
            dtk::registerConverterToMetaContainerSequential<QStringList *>(newId);
        }

        return newId;
    }
};

template<> struct dtk::is_sequential_container_pointer<QStringList *> : std::true_type {};

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaContainerSequential.tpp"

//
// dtkCoreMetaContainerSequential.h ends here
