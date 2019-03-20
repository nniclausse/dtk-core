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

#include "dtkCoreParameterFile.h"

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterFile implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreParameterDir::dtkCoreParameterDir(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterDir>()
{
    if (v.canConvert<dtkCoreParameterDir>()) {
        auto o(v.value<dtkCoreParameterDir>());
        *this = o;

    } else if (v.canConvert<QString>()) {
        QFileInfo filename = QFileInfo(v.toString());
        m_dir = filename.dir().path();
    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterDir>())
                  << ". Nothing is done.";
    }
}

dtkCoreParameterDir::dtkCoreParameterDir(const dtkCoreParameterDir& o) : dtkCoreParameterBase<dtkCoreParameterDir>(o),
                                                                            m_dir(o.m_dir),
                                                                            m_filters(o.m_filters)
{

}

dtkCoreParameterDir::dtkCoreParameterDir(const QString& label, const QString& dir, const QStringList& filters, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterDir>(label, doc),
                                                                                                                                                                m_dir(dir),
                                                                                                                                                                m_filters(filters)
{

}

dtkCoreParameterDir& dtkCoreParameterDir::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterDir>()) {
        *this = v.value<dtkCoreParameterDir>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        m_dir = v.toString();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

dtkCoreParameterDir& dtkCoreParameterDir::operator = (const dtkCoreParameterDir& o)
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_dir = o.m_dir;
        m_filters = o.m_filters;
        this->sync();
    }
    return *this;
}

void dtkCoreParameterDir::setValue(const QString& dir)
{
    QFileInfo filename = QFileInfo(dir);
    m_dir = filename.dir().path();
    this->sync();
}

void dtkCoreParameterDir::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterDir>()) {
        *this = v.value<dtkCoreParameterDir>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        m_dir = v.toString();

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterDir>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}

QString dtkCoreParameterDir::dir(void) const
{
    return m_dir;
}

QStringList dtkCoreParameterDir::filters(void) const
{
    return m_filters;
}

QDataStream& operator << (QDataStream& s, const dtkCoreParameterDir& p)
{
    s << p.label();
    s << p.dir();
    auto filters = p.filters();
    s << filters.size();
    for (int i = 0; i < filters.size(); ++i) {
        s << filters[i];
    }
    s << p.documentation();

    return s;
}

QDataStream& operator >> (QDataStream& s, dtkCoreParameterDir& p)
{
    QString label; s >> label;
    QString dir; s >> dir;
    int count; s >> count;
    QStringList filters;
    for (int i = 0; i < count; ++i) {
        QString filter; s >> filter;
        filters << filter;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterDir(label, dir, filters, doc);
    return s;

}

QDebug operator << (QDebug dbg, dtkCoreParameterDir p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "dir " << p.dir() << ", "
                  << "filters " << p.filters() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

// ///////////////////////////////////////////////////////////////////
// dtkCoreParameterFile implementation
// ///////////////////////////////////////////////////////////////////

dtkCoreParameterFile::dtkCoreParameterFile(const QVariant& v) : dtkCoreParameterDir(v)
{
    if (v.canConvert<dtkCoreParameterFile>()) {
        auto o(v.value<dtkCoreParameterFile>());
        *this = o;

    } else if (v.canConvert<QString>()) {
        QFileInfo filename = QFileInfo(v.toString());
        m_dir = filename.dir().path();
        m_basename = filename.baseName();
    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterFile>())
                  << ". Nothing is done.";
    }
}

dtkCoreParameterFile::dtkCoreParameterFile(const dtkCoreParameterFile& o) : dtkCoreParameterDir(o),
                                                                            m_basename(o.m_basename)
{

}

dtkCoreParameterFile::dtkCoreParameterFile(const QString& label, const QString& basename, const QString& dir, const QStringList& filters, const QString& doc) : dtkCoreParameterDir(label, dir, filters, doc),
                                                                                                                                                                m_basename(basename)
{

}

dtkCoreParameterFile& dtkCoreParameterFile::operator = (const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterFile>()) {
        *this = v.value<dtkCoreParameterFile>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_basename = map["basename"].toString();
        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        QFileInfo fileinfo = QFileInfo(v.toString());
        m_dir = fileinfo.dir().path();
        m_basename = fileinfo.baseName();

    } else {
        return *this;
    }
    this->sync();
    return *this;
}

dtkCoreParameterFile& dtkCoreParameterFile::operator = (const dtkCoreParameterFile& o)
{
    if (this != &o) {
        m_label = o.m_label;
        m_doc = o.m_doc;
        m_basename = o.m_basename;
        m_dir = o.m_dir;
        m_filters = o.m_filters;
        this->sync();
    }
    return *this;
}

void dtkCoreParameterFile::setValue(const QString& filename)
{
    QFileInfo fileinfo = QFileInfo(filename);
    m_dir = fileinfo.dir().path();
    m_basename = fileinfo.baseName();
    this->sync();
}

void dtkCoreParameterFile::setValue(const QVariant& v)
{
    if (v.canConvert<dtkCoreParameterFile>()) {
        *this = v.value<dtkCoreParameterFile>();

    } else if (v.canConvert<QVariantHash>()) {
        auto map = v.toHash();

        m_label = map["label"].toString();
        m_doc = map["doc"].toString();

        m_basename = map["basename"].toString();
        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        QFileInfo fileinfo = v.toString();
        m_dir = fileinfo.dir().path();
        m_basename = fileinfo.baseName();
    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterFile>())
                  << ". Nothing is done.";
        this->syncFail();
        return;
    }
    this->sync();
}

QString dtkCoreParameterFile::fileName(void) const
{
    return m_dir + QDir::separator() + m_basename;
}

QString dtkCoreParameterFile::baseName(void) const
{
    return m_basename;
}

QDataStream& operator << (QDataStream& s, const dtkCoreParameterFile& p)
{
    s << p.label();
    s << p.baseName();
    s << p.dir();
    auto filters = p.filters();
    s << filters.size();
    for (int i = 0; i < filters.size(); ++i) {
        s << filters[i];
    }
    s << p.documentation();

    return s;
}

QDataStream& operator >> (QDataStream& s, dtkCoreParameterFile& p)
{
    QString label; s >> label;
    QString basename; s >> basename;
    QString dir; s >> dir;
    int count; s >> count;
    QStringList filters;
    for (int i = 0; i < count; ++i) {
        QString filter; s >> filter;
        filters << filter;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterFile(label, basename, dir, filters, doc);
    return s;

}

QDebug operator << (QDebug dbg, dtkCoreParameterFile p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "basename " << p.baseName() << ", "
                  << "dir " << p.dir() << ", "
                  << "filters " << p.filters() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

//
// dtkCoreParameterFile.cpp ends here
