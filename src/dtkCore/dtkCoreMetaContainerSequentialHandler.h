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
#include "dtkCoreMetaType.h"

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
    template <typename U = T> dtk:: enable_reserve<U> reserve_impl(long long size);
    template <typename U = T> dtk::disable_reserve<U> reserve_impl(long long size);

    void resize(long long size);
    template <typename U = T> dtk:: enable_resize<U> resize_impl(long long size);
    template <typename U = T> dtk::disable_resize<U> resize_impl(long long size);

    void  append(const void *t);
    void prepend(const void *t);
    void  insert(long long idx, const void *t);

    void    setAt(long long idx, const void *t);
    void removeAt(long long idx);

    const void *at(long long idx) const;
          void *at(long long idx);

    QVariant& variantAt(long long idx, QVariant& var);

    handler_iterator *begin(void);
    handler_iterator   *end(void);

    handler_const_iterator *cbegin(void) const;
    handler_const_iterator   *cend(void) const;

private:
    T *m_container;
};

// ///////////////////////////////////////////////////////////////////
// Register converter to dtkCoreMetaContainerSequential
// ///////////////////////////////////////////////////////////////////

namespace dtk
{
    template <typename T> bool registerConverterToMetaContainerSequential(int);
}

// /////////////////////////////////////////////////////////////////

#include "dtkCoreMetaContainerSequentialHandler.tpp"

//
// dtkCoreMetaContainerSequentialHandler.h ends here
