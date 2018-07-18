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
// dtkMetaContainerSequentialHandler
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreMetaContainerSequentialHandler
{
public:
    struct DTKCORE_EXPORT iterator
    {
        virtual ~iterator(void) = default;

        virtual iterator *clone(void) const = 0;
        virtual void copy(const iterator& o) = 0;
        virtual bool equal(const iterator& o) const = 0;

        virtual void advance(void) = 0;
        virtual void  moveForward(long long step) = 0;
        virtual void moveBackward(long long step) = 0;

        virtual void *value(void) const = 0;
        virtual QVariant variant(void) const = 0;

        virtual void    assign(const void *t) = 0;
        virtual void addAssign(const void *t) = 0;
        virtual void subAssign(const void *t) = 0;
        virtual void mulAssign(const void *t) = 0;
        virtual void divAssign(const void *t) = 0;

        virtual bool equalToValue(const void *t) const = 0;
    };

public:
    struct DTKCORE_EXPORT const_iterator
    {
        virtual ~const_iterator(void) = default;

        virtual const_iterator *clone(void) const = 0;
        virtual void copy(const const_iterator& o) = 0;
        virtual bool equal(const const_iterator& o) const = 0;

        virtual void advance(void) = 0;
        virtual void  moveForward(long long step) = 0;
        virtual void moveBackward(long long step) = 0;

        virtual const void *value(void) const = 0;
        virtual QVariant variant(void) const = 0;
    };

public:
    virtual ~dtkCoreMetaContainerSequentialHandler(void) = default;

    virtual QString description(void) const = 0;

    virtual bool hasBiDirectionalIterator(void) const = 0;
    virtual bool  hasRandomAccessIterator(void) const = 0;

    virtual       iterator  *begin(void)       = 0;
    virtual const_iterator *cbegin(void) const = 0;
    virtual       iterator    *end(void)       = 0;
    virtual const_iterator   *cend(void) const = 0;

    virtual bool      empty(void) const = 0;
    virtual long long  size(void) const = 0;

    virtual void   clear(void) = 0;
    virtual void reserve(long long size) = 0;
    virtual void  resize(long long size) = 0;

    virtual void  append(const void *t) = 0;
    virtual void prepend(const void *t) = 0;
    virtual void  insert(long long idx, const void *t) = 0;

    virtual void    setAt(long long idx, const void *t) = 0;
    virtual void removeAt(long long idx) = 0;

    virtual const void *at(long long idx) const = 0;
    virtual       void *at(long long idx)       = 0;

    virtual iterator *iteratorAt(long long idx, iterator *pit) = 0;
    virtual QVariant& variantAt(long long idx, QVariant& var) = 0;

public:
    int value_type_id;
};

Q_DECLARE_METATYPE(dtkCoreMetaContainerSequentialHandler *)

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerTemplate
// ///////////////////////////////////////////////////////////////////

template <typename T>
class dtkCoreMetaContainerSequentialHandlerTemplate : public dtkCoreMetaContainerSequentialHandler
{
public:
    using container_value_type = typename T::value_type;
    using container_iterator = typename T::iterator;
    using container_const_iterator = typename T::const_iterator;


    using handler_iterator = dtkCoreMetaContainerSequentialHandler::iterator;
    using handler_const_iterator = dtkCoreMetaContainerSequentialHandler::const_iterator;


    struct iterator : public handler_iterator
    {
        container_iterator it;

        iterator(const container_iterator& iterator);

        handler_iterator *clone(void) const;
        void  copy(const handler_iterator& o);
        bool equal(const handler_iterator& o) const;

        void advance(void);
        void  moveForward(long long step);
        void moveBackward(long long step);

        void *value(void) const;
        QVariant variant(void) const;

        void    assign(const void *t);
        void addAssign(const void *t);
        void subAssign(const void *t);
        void mulAssign(const void *t);
        void divAssign(const void *t);

        bool equalToValue(const void *t) const;
    };


    struct const_iterator : public handler_const_iterator
    {
        container_const_iterator it;

        const_iterator(const container_const_iterator& iterator);

        handler_const_iterator *clone(void) const;
        void copy(const handler_const_iterator& o);
        bool equal(const handler_const_iterator& o) const;

        void advance(void);
        void  moveForward(long long step);
        void moveBackward(long long step);

        const void *value(void) const;
        QVariant variant(void) const;
    };


    explicit dtkCoreMetaContainerSequentialHandlerTemplate(T *c);
            ~dtkCoreMetaContainerSequentialHandlerTemplate(void);

    QString description(void) const;

    bool hasBiDirectionalIterator(void) const;
    bool  hasRandomAccessIterator(void) const;

    bool      empty(void) const;
    long long  size(void) const;

    void   clear(void);
    void reserve(long long size);
    void  resize(long long size);

    void  append(const void *t);
    void prepend(const void *t);
    void  insert(long long idx, const void *t);

    void    setAt(long long idx, const void *t);
    void removeAt(long long idx);

    const void *at(long long idx) const;
          void *at(long long idx);

    handler_iterator *iteratorAt(long long idx, handler_iterator *pit);
    QVariant& variantAt(long long idx, QVariant& var);

    handler_iterator *begin(void);
    handler_iterator   *end(void);

    handler_const_iterator *cbegin(void) const;
    handler_const_iterator   *cend(void) const;

private:
    T *m_container;
};

// // ///////////////////////////////////////////////////////////////////
// // dtkMetaContainerSequentialHandlerHelper
// // ///////////////////////////////////////////////////////////////////

// template <typename T>
// struct dtkMetaContainerSequentialHandlerHelper
// {
//     using container_value_type = typename T::value_type;
//     using container_iterator = typename T::iterator;

//     template <typename U = T>
//     static std::enable_if_t< dtkMetaIteratorIsBidirectional<typename U::iterator>::value, bool> hasBidirectionalIterator(void) {
//         return true;
//     }
//     template <typename U = T> static typename std::enable_if < !dtkMetaIteratorIsBidirectional<typename U::iterator>::value, bool >::type hasBidirectionalIterator(void) {
//         return false;
//     }

// public:
//     template <typename U = T> static typename std::enable_if< dtkMetaIteratorIsRandomAccess<typename U::iterator>::value, bool>::type hasRandomAccesIterator(void) {
//         return true;
//     }
//     template <typename U = T> static typename std::enable_if < !dtkMetaIteratorIsRandomAccess<typename U::iterator>::value, bool >::type hasRandomAccesIterator(void) {
//         return false;
//     }

// public:
//     static bool      empty(const T *c);
//     static qlonglong  size(const T *c);

// public:
//     static void clear(T *c);

// public:
//     template <typename U = T> static typename std::enable_if< dtkMetaContainerIsReservable<U>::value>::type reserve(T *c, qlonglong size);
//     template <typename U = T> static typename std::enable_if < !dtkMetaContainerIsReservable<U>::value >::type reserve(T *c, qlonglong size);

// public:
//     template <typename U = T> static typename std::enable_if< dtkMetaContainerIsResizable<U>::value>::type resize(T *c, qlonglong size);
//     template <typename U = T> static typename std::enable_if < !dtkMetaContainerIsResizable<U>::value >::type resize(T *c, qlonglong size);

// public:
//     static void   insert(T *c, qlonglong idx, const ValueType& t);
//     static void    setAt(T *c, qlonglong idx, const ValueType& t);
//     static void removeAt(T *c, qlonglong idx);

// public:
//     static const ValueType *at(const T *c, qlonglong idx);
//     static       ValueType *at(      T *c, qlonglong idx);

// public:
//     static void iteratorAt(T *c, qlonglong idx, Iterator& it);

// public:
//     static QVariant& variantAt(const T *c, qlonglong idx, QVariant& var);
// };

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialItemHelper
// ///////////////////////////////////////////////////////////////////

template <typename T> struct dtkMetaContainerSequentialIteratorHelper {
public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsAssignable<U>::value>::type assign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if < !dtkMetaTypeIsAssignable<U>::value >::type assign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsAddAssignable<U>::value>::type addAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if < !dtkMetaTypeIsAddAssignable<U>::value >::type addAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsSubAssignable<U>::value>::type subAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if < !dtkMetaTypeIsSubAssignable<U>::value >::type subAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsMulAssignable<U>::value>::type mulAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if < !dtkMetaTypeIsMulAssignable<U>::value >::type mulAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsDivAssignable<U>::value>::type divAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if < !dtkMetaTypeIsDivAssignable<U>::value >::type divAssign(T&, const T&);
};

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::convertFunctor for QMetatype system
// /////////////////////////////////////////////////////////////////

template <typename From> struct dtkMetaContainerSequentialConvertFunctor {
};

template <typename From> struct dtkMetaContainerSequentialConvertFunctor<From *> {
    dtkMetaContainerSequentialHandler *operator () (From *f) const;
};

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialRegisterConverter
// ///////////////////////////////////////////////////////////////////

template < typename T, bool = QMetaTypeId2<typename std::remove_pointer<T>::type::value_type>::Defined > struct dtkContainerSequentialValueTypeIsMetaType {
    static bool record(int) {
        return false;
    }
};

template < typename T > struct dtkContainerSequentialValueTypeIsMetaType<T, true> {
    static bool record(int id);
};

template < typename T, bool = dtkMetaTypeIsSequentialContainerPointer<T>::value > struct dtkMetaContainerSequentialRegisterConverter {
    static bool record(int) {
        return false;
    }
};

template < typename T> struct dtkMetaContainerSequentialRegisterConverter<T, true> : public dtkContainerSequentialValueTypeIsMetaType<T> {
};

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaContainerSequentialHandler.tpp"

//
// dtkCoreMetaContainerSequentialHandler.h ends here
