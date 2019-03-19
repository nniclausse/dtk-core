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

dtkCoreParameterFile::dtkCoreParameterFile(const QVariant& v) : dtkCoreParameterBase<dtkCoreParameterFile>()
{
    if (v.canConvert<dtkCoreParameterFile>()) {
        auto o(v.value<dtkCoreParameterFile>());
        *this = o;

    } else if (v.canConvert<QString>()) {
        m_filename = v.toString();

    } else {
        dtkWarn() << Q_FUNC_INFO << "QVariant type" << v.typeName()
                  << "is not compatible with current type"
                  << QMetaType::typeName(qMetaTypeId<dtkCoreParameterFile>())
                  << ". Nothing is done.";
    }
}

dtkCoreParameterFile::dtkCoreParameterFile(const dtkCoreParameterFile& o) : dtkCoreParameterBase<dtkCoreParameterFile>(o),
                                                                            m_filename(o.m_filename),
                                                                            m_dir(o.m_dir),
                                                                            m_filters(o.m_filters)
{

}

dtkCoreParameterFile::dtkCoreParameterFile(const QString& label, const QString& filename, const QString& dir, const QStringList& filters, const QString& doc) : dtkCoreParameterBase<dtkCoreParameterFile>(label, doc),
                                                                                                                                                                m_filename(filename),
                                                                                                                                                                m_dir(dir),
                                                                                                                                                                m_filters(filters)
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

        m_filename = map["filename"].toString();
        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        m_filename = v.toString();

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
        m_filename = o.m_filename;
        m_dir = o.m_dir;
        m_filters = o.m_filters;
        this->sync();
    }
    return *this;
}

void dtkCoreParameterFile::setValue(const QString& filename)
{
    m_filename = filename;
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

        m_filename = map["filename"].toString();
        m_dir = map["dir"].toString();
        m_filters = map["filters"].toStringList();

    } else if (v.canConvert<QString>()) {
        m_filename = v.toString();

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
    return m_filename;
}

QString dtkCoreParameterFile::dir(void) const
{
    return m_dir;
}

QStringList dtkCoreParameterFile::filters(void) const
{
    return m_filters;
}

QDataStream& operator << (QDataStream& s, const dtkCoreParameterFile& p)
{
    s << p.label();
    s << p.fileName();
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
    QString filename; s >> filename;
    QString dir; s >> dir;
    int count; s >> count;
    QStringList filters;
    for (int i = 0; i < count; ++i) {
        QString filter; s >> filter;
        filters << filter;
    }
    QString doc; s >> doc;

    p = dtkCoreParameterFile(label, filename, dir, filters, doc);
    return s;

}

QDebug operator << (QDebug dbg, dtkCoreParameterFile p)
{
    const bool old_setting = dbg.autoInsertSpaces();
    dbg.nospace() << p.variant().typeName() << " : { ";
    dbg.nospace() << "label " << p.label() << ", "
                  << "filename " << p.fileName() << ", "
                  << "dir " << p.dir() << ", "
                  << "filters " << p.filters() << ", "
                  << "documentation : " << p.documentation()
                  << " }";

    dbg.setAutoInsertSpaces(old_setting);
    return dbg.maybeSpace();
}

//
// dtkCoreParameterFile.cpp ends here
