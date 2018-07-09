// Version: $Id$
//
//

// Commentary:
//  dtkCoreIOCompressor is just a renaming of qtiocompressor.
//  Plus small modification of the constructor (detect if gzip file)
//  Update by: Nicolas Niclausse
//
//  See EOF for Credits

// Change Log:
//
//

// Code:

#pragma once

#include <dtkCoreExport>

#include "dtkCoreConfig.h"

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCoreIOCompressor interface
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreIOCompressor : public QIODevice
{
    Q_OBJECT

public:
    enum StreamFormat {
        ZlibFormat,
        GzipFormat,
        RawZipFormat,
        UnsupportedFormat
    };

     dtkCoreIOCompressor(void) = default;
    ~dtkCoreIOCompressor(void) = default;

    virtual void setStreamFormat(StreamFormat);
    virtual StreamFormat streamFormat(void) const;

    static bool isGzipSupported(void);

    virtual bool isSequential(void) const override;

    virtual bool open(OpenMode) override;
    virtual void close(void) override;

    virtual void flush(void);

    virtual qint64 bytesAvailable(void) const override;

public:
    static QIODevice *create(const char *file_name, bool clean = false, int compressionLevel = 6, int bufferSize = 65500);
    static QIODevice *create(const QString& file_name, bool clean = false, int compressionLevel = 6, int bufferSize = 65500);
    static QIODevice *create(QIODevice *device, bool clean = false, int compressionLevel = 6, int bufferSize = 65500);

private:
    Q_DISABLE_COPY(dtkCoreIOCompressor);
};

#if defined(DTK_HAVE_ZLIB)

// ///////////////////////////////////////////////////////////////////
// dtkCoreIOCompressorImpl declaration
// ///////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCoreIOCompressorImpl : public dtkCoreIOCompressor
{
    Q_OBJECT

public:
     dtkCoreIOCompressorImpl(QIODevice *device, bool clean=false, int compressionLevel = 6, int bufferSize = 65500);
    ~dtkCoreIOCompressorImpl(void);

    void setStreamFormat(StreamFormat format) override;
    StreamFormat streamFormat(void) const override;

    static bool isGzipSupported(void);

    bool isSequential(void) const override;

    bool open(OpenMode mode) override;
    void close(void) override;

    void flush(void) override;

    qint64 bytesAvailable(void) const override;

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    static bool checkGzipSupport(const char *const versionString);

    class dtkCoreIOCompressorImplPrivate *d_ptr;
    Q_DECLARE_PRIVATE(dtkCoreIOCompressorImpl);
    Q_DISABLE_COPY(dtkCoreIOCompressorImpl);
};

#endif

// ///////////////////////////////////////////////////////////////////
// Credits
// ///////////////////////////////////////////////////////////////////

// Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// Contact: Nokia Corporation (qt-info@nokia.com)
//
// This file is part of a Qt Solutions component.
//
// Commercial Usage
// Licensees holding valid Qt Commercial licenses may use this file in
// accordance with the Qt Solutions Commercial License Agreement provided
// with the Software or, alternatively, in accordance with the terms
// contained in a written agreement between you and Nokia.
//
// GNU Lesser General Public License Usage
// Alternatively, this file may be used under the terms of the GNU Lesser
// General Public License version 2.1 as published by the Free Software
// Foundation and appearing in the file LICENSE.LGPL included in the
// packaging of this file.  Please review the following information to
// ensure the GNU Lesser General Public License version 2.1 requirements
// will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
//
// In addition, as a special exception, Nokia gives you certain
// additional rights. These rights are described in the Nokia Qt LGPL
// Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
// package.
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU
// General Public License version 3.0 as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL included in the
// packaging of this file.  Please review the following information to
// ensure the GNU General Public License version 3.0 requirements will be
// met: http://www.gnu.org/copyleft/gpl.html.
//
// Please note Third Party Software included with Qt Solutions may impose
// additional restrictions and it is the user's responsibility to ensure
// that they have met the licensing requirements of the GPL, LGPL, or Qt
// Solutions Commercial license and the relevant license of the Third
// Party Software they are using.
//
// If you are unsure which license is appropriate for your use, please
// contact Nokia at qt-info@nokia.com.

// ///////////////////////////////////////////////////////////////////

//
// dtkCoreIOCompressor.h ends here
