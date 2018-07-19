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


// /////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequential::item implementation
// /////////////////////////////////////////////////////////////////

inline dtkCoreMetaContainerSequential::item::item(handler::iterator *iterator) : it(iterator)
{

}

inline dtkCoreMetaContainerSequential::item::item(item&& o) : it(nullptr)
{
    std::swap(it, o.it);
}

inline dtkCoreMetaContainerSequential::item::~item(void)
{
    if (it) {
        delete it;
    }
    it = nullptr;
}

inline auto dtkCoreMetaContainerSequential::item::operator = (const item& o) -> item&
{
    if (this != &o) {
        it->copy(*(o.it));
    }
    return *this;
}

inline auto dtkCoreMetaContainerSequential::item::operator = (item&& o) -> item&
{
    std::swap(it, o.it);
    return *this;
}

inline bool dtkCoreMetaContainerSequential::item::operator == (const item& o) const
{
    return  it->equal(*(o.it));
}

inline bool dtkCoreMetaContainerSequential::item::operator != (const item& o) const
{
    return !it->equal(*(o.it));
}

inline const QVariant dtkCoreMetaContainerSequential::item::value(void) const
{
    return it->variant();
}

template <typename T>
inline const T& dtkCoreMetaContainerSequential::item::value(void) const
{
    return *static_cast<const T *>(it->value());
}

template <typename T>
inline auto dtkCoreMetaContainerSequential::item::operator = (const T& t) -> item&
{
    it->assign(&t);
    return *this;
}

template <typename T>
inline auto dtkCoreMetaContainerSequential::item::operator += (const T& t) -> item&
{
    it->addAssign(&t);
    return *this;
}

template <typename T>
inline auto dtkCoreMetaContainerSequential::item::operator -= (const T& t) -> item&
{
    it->subAssign(&t);
    return *this;
}

template <typename T>
inline auto dtkCoreMetaContainerSequential::item::operator *= (const T& t) -> item&
{
    it->mulAssign(&t);
    return *this;
}

template <typename T>
inline auto dtkCoreMetaContainerSequential::item::operator /= (const T& t) -> item&
{
    it->divAssign(&t);
    return *this;
}

template<typename T>
inline bool dtkCoreMetaContainerSequential::item::operator == (const T& t) const
{
    return it->equalToValue(&t);
}

template<typename T>
inline bool dtkCoreMetaContainerSequential::item::operator != (const T& t) const
{
    return !it->equalToValue(&t);
}

// /////////////////////////////////////////////////////////////////

inline QDebug& operator << (QDebug debug, const dtkCoreMetaContainerSequential::item& item)
{
    const bool oldSetting = debug.autoInsertSpaces();
    debug.nospace() << item.value();
    debug.setAutoInsertSpaces(oldSetting);
    return debug.maybeSpace();
}

// /////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequential::iterator implementation
// /////////////////////////////////////////////////////////////////

inline dtkCoreMetaContainerSequential::iterator::iterator(handler::iterator *iterator) : proxy(iterator)
{
}

inline dtkCoreMetaContainerSequential::iterator::iterator(const iterator& o) : proxy(o.proxy.it)
{
}

inline dtkCoreMetaContainerSequential::iterator::iterator(iterator&& o) : proxy(o.proxy.it)
{
    o.proxy.it = nullptr;
}

inline dtkCoreMetaContainerSequential::iterator::~iterator(void)
{
}

inline auto dtkCoreMetaContainerSequential::iterator::operator = (const iterator& o) -> iterator&
{
    proxy = o.proxy;
    return *this;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator = (iterator&& o) -> iterator&
{
    std::swap(proxy.it, o.proxy.it);
    return *this;
}

inline bool dtkCoreMetaContainerSequential::iterator::operator == (const iterator& o) const
{
    return proxy == o.proxy;
}

inline bool dtkCoreMetaContainerSequential::iterator::operator != (const iterator& o) const
{
    return proxy != o.proxy;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator * (void) -> item&
{
    return proxy;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator [] (long long j) ->item&
{
    return *(*this + j);
}

template <typename T>
inline T& dtkCoreMetaContainerSequential::iterator::value(void)
{
    return *static_cast<T *>(proxy.it->value());
}

inline auto dtkCoreMetaContainerSequential::iterator::operator ++ (void) -> iterator&
{
    proxy.it->advance();
    return *this;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator ++ (int) -> iterator
{
    iterator o(*this);
    proxy.it->advance();
    return o;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator -- (void) -> iterator&
{
    proxy.it->moveBackward(static_cast<long long>(1));
    return *this;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator -- (int) -> iterator
{
    iterator o(*this);
    proxy.it->moveBackward(static_cast<long long>(1));
    return o;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator += (long long j) -> iterator&
{
    proxy.it->moveForward(j);
    return *this;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator -= (long long j) -> iterator&
{
    proxy.it->moveBackward(j);
    return *this;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator + (long long j) const -> iterator
{
    iterator o(*this);
    o += j;
    return o;
}

inline auto dtkCoreMetaContainerSequential::iterator::operator - (long long j) const -> iterator
{
    iterator o(*this);
    o -= j;
    return o;
}

// /////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequential::const_iterator implementation
// /////////////////////////////////////////////////////////////////

inline dtkCoreMetaContainerSequential::const_iterator::const_iterator(handler::const_iterator *iterator) : it(iterator)
{
}

inline dtkCoreMetaContainerSequential::const_iterator::const_iterator(const const_iterator& o) : it(o.it->clone())
{
}

inline dtkCoreMetaContainerSequential::const_iterator::const_iterator(const_iterator&& o) : it(o.it)
{
    o.it = nullptr;
}

inline dtkCoreMetaContainerSequential::const_iterator::~const_iterator(void)
{
    if (it) {
        delete it;
    }
    it = nullptr;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator = (const const_iterator& o) -> const_iterator&
{
    if (this != &o) {
        it->copy(*(o.it));
    }
    return *this;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator = (const_iterator&& o) -> const_iterator&
{
    std::swap(it, o.it);
    return *this;
}

inline bool dtkCoreMetaContainerSequential::const_iterator::operator == (const const_iterator& o) const
{
    return it->equal(*(o.it));
}

inline bool dtkCoreMetaContainerSequential::const_iterator::operator != (const const_iterator& o) const
{
    return !it->equal(*(o.it));
}

inline QVariant dtkCoreMetaContainerSequential::const_iterator::operator * (void) const
{
    return it->variant();
}

inline QVariant dtkCoreMetaContainerSequential::const_iterator::operator [] (long long j) const
{
    return *(*this + j);
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator ++ (void) -> const_iterator&
{
    it->advance();
    return *this;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator ++ (int) -> const_iterator
{
    const_iterator o(*this);
    it->advance();
    return o;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator -- (void) -> const_iterator&
{
    it->moveBackward(static_cast<long long>(1));
    return *this;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator -- (int) -> const_iterator
{
    const_iterator o(*this);
    it->moveBackward(static_cast<long long>(1));
    return o;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator += (long long j) -> const_iterator&
{
    it->moveForward(j);
    return *this;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator -= (long long j) -> const_iterator&
{
    it->moveBackward(j);
    return *this;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator + (long long j) const -> const_iterator
{
    const_iterator o(*this);
    o += j;
    return o;
}

inline auto dtkCoreMetaContainerSequential::const_iterator::operator - (long long j) const -> const_iterator
{
    const_iterator o(*this);
    o -= j;
    return o;
}

// /////////////////////////////////////////////////////////////////
// dtkCoreMetaContainerSequential implementation
// /////////////////////////////////////////////////////////////////

inline dtkCoreMetaContainerSequential::dtkCoreMetaContainerSequential(handler *h) : m_h(h), m_proxy(new item(nullptr))
{
    if (m_h) {
        m_proxy->it = m_h->begin();
    }
}

inline dtkCoreMetaContainerSequential::dtkCoreMetaContainerSequential(dtkCoreMetaContainerSequential&& o) : m_h(o.m_h), m_proxy(new item(nullptr))
{
    if (m_h) {
        m_proxy->it = m_h->begin();
    }
    o.m_h = nullptr;
}

inline dtkCoreMetaContainerSequential::~dtkCoreMetaContainerSequential(void)
{
    if (m_h) {
        delete m_h;
    }
    m_h = nullptr;
}

inline bool dtkCoreMetaContainerSequential::hasBiDirectionalIterator(void) const
{
    return m_h->hasBiDirectionalIterator();
}

inline bool dtkCoreMetaContainerSequential::hasRandomAccessIterator(void) const
{
    return m_h->hasRandomAccessIterator();
}

inline bool dtkCoreMetaContainerSequential::empty(void) const
{
    return m_h->empty();
}

inline long long dtkCoreMetaContainerSequential::size(void) const
{
    return m_h->size();
}

inline void dtkCoreMetaContainerSequential::clear(void)
{
    m_h->clear();
}

inline void dtkCoreMetaContainerSequential::reserve(long long size)
{
    m_h->reserve(size);
}

inline void dtkCoreMetaContainerSequential::resize(long long size)
{
    m_h->resize(size);
}

template <typename T> inline void dtkCoreMetaContainerSequential::append(const T& t)
{
    m_h->append(&t);
}

template <typename T> inline void dtkCoreMetaContainerSequential::prepend(const T& t)
{
    m_h->prepend(&t);
}

inline void dtkCoreMetaContainerSequential::append(const QVariant& v)
{
    this->insert(m_h->size(), v);
}

inline void dtkCoreMetaContainerSequential::prepend(const QVariant& v)
{
    this->insert(0, v);
}

template <typename T>
inline void dtkCoreMetaContainerSequential::insert(long long idx, const T& t)
{
    m_h->insert(idx, &t);
}

template <typename T>
inline void dtkCoreMetaContainerSequential::setAt(long long idx, const T& t)
{
    m_h->setAt(idx, &t);
}

template <typename T>
inline const T& dtkCoreMetaContainerSequential::at(long long idx) const
{
    return *static_cast<const T *>(m_h->at(idx));
}

inline const QVariant& dtkCoreMetaContainerSequential::at(long long idx) const
{
    m_h->variantAt(idx, m_var);
    return m_var;
}

inline void dtkCoreMetaContainerSequential::removeAt(long long idx)
{
    m_h->removeAt(idx);
}

inline const QVariant& dtkCoreMetaContainerSequential::first(void) const
{
    m_h->variantAt(0, m_var);
    return m_var;
}

inline auto dtkCoreMetaContainerSequential::first(void) -> item&
{
    m_proxy->it = m_h->begin();
    return *m_proxy;
}

inline const QVariant& dtkCoreMetaContainerSequential::last(void) const
{
    m_h->variantAt(m_h->size() - 1, m_var);
    return m_var;
}

inline auto dtkCoreMetaContainerSequential::last(void) -> item&
{
    m_proxy->it = m_h->begin();
    m_proxy->it->moveForward(m_h->size() - 1);
    return *m_proxy;
}

inline const QVariant& dtkCoreMetaContainerSequential::operator [] (long long idx) const
{
    m_h->variantAt(idx, m_var);
    return m_var;
}

inline auto dtkCoreMetaContainerSequential::operator [] (long long idx) -> item&
{
    m_h->iteratorAt(idx, m_proxy->it);
    return *m_proxy;
}

inline auto dtkCoreMetaContainerSequential::begin(void) -> iterator
{
    return iterator(m_h->begin());
}

inline auto dtkCoreMetaContainerSequential::end(void) -> iterator
{
    return iterator(m_h->end());
}

inline auto dtkCoreMetaContainerSequential::begin(void) const -> const_iterator
{
    return const_iterator(m_h->cbegin());
}

inline auto dtkCoreMetaContainerSequential::end(void) const -> const_iterator
{
    return const_iterator(m_h->cend());
}

inline auto dtkCoreMetaContainerSequential::cbegin(void) const -> const_iterator
{
    return const_iterator(m_h->cbegin());
}

inline auto dtkCoreMetaContainerSequential::cend(void) const -> const_iterator
{
    return const_iterator(m_h->cend());
}

// ///////////////////////////////////////////////////////////////////
// Debug operator
// ///////////////////////////////////////////////////////////////////

inline QDebug& operator << (QDebug debug, const dtkCoreMetaContainerSequential& container)
{
    debug << qPrintable(container.m_h->description());
    return debug.maybeSpace();
}

// /////////////////////////////////////////////////////////////////
// Specialization of Qt internal QVariant
// /////////////////////////////////////////////////////////////////

namespace QtPrivate
{
    template <> struct QVariantValueHelperInterface<dtkCoreMetaContainerSequential>
    {
        static dtkCoreMetaContainerSequential invoke(const QVariant& v)
        {
            return dtkCoreMetaContainerSequential(v.value<dtkCoreMetaContainerSequentialHandler *>());
        }
    };
}

// /////////////////////////////////////////////////////////////////
// Specialization of dtk::canConvert function
// /////////////////////////////////////////////////////////////////

namespace dtk
{
    namespace detail
    {
        template <>
        inline bool can_convert<dtkCoreMetaContainerSequential>(const QList<int>& types)
        {
            int to = qMetaTypeId<dtkCoreMetaContainerSequentialHandler *>();

            for (int from : types) {
                if (!QMetaType::hasRegisteredConverterFunction(from, to)) {
                    return false;
                }
            }
            return true;
        }
    }
}

// /////////////////////////////////////////////////////////////////
// Specialization of QVariant::canConvert<T>() method
// /////////////////////////////////////////////////////////////////

template <>
inline bool QVariant::canConvert<dtkCoreMetaContainerSequential>(void) const
{
    int from = d.type;
    int to = qMetaTypeId<dtkCoreMetaContainerSequentialHandler *>();
    return QMetaType::hasRegisteredConverterFunction(from, to);
}

//
// dtkCoreMetaContainerSequential.tpp ends here
