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

#include "dtkCoreIOCompressorTest.h"

#include <dtkCore/dtkCoreIOCompressor>
#include <dtkCore/dtkCoreConfig.h>

#include <dtkCoreTest>

// ///////////////////////////////////////////////////////////////////
// dtkCoreIOCompressorTestCase implementation
// ///////////////////////////////////////////////////////////////////

void dtkCoreIOCompressorTestCase::initTestCase(void)
{
}

void dtkCoreIOCompressorTestCase::init(void)
{
}

void dtkCoreIOCompressorTestCase::testWrite(void)
{
#if defined(DTK_HAVE_ZLIB)
    QFile file("foo.gz");
    QByteArray data = QByteArray("The quick brown fox\nhello world\n");
    dtkCoreIOCompressorImpl compressor(&file);
    compressor.open(QIODevice::WriteOnly);
    compressor.write(data);
    compressor.close();
#endif
}

void dtkCoreIOCompressorTestCase::testRead(void)
{
#if defined(DTK_HAVE_ZLIB)
    QByteArray data = QByteArray("The quick brown fox\n");
    QFile file("foo.gz");
    dtkCoreIOCompressorImpl compressor(&file);
    compressor.open(QIODevice::ReadOnly);
    QByteArray text = compressor.readLine();
    QVERIFY(data == text);

    data = QByteArray("hello world\n");
    text = compressor.readLine();
    QVERIFY(data == text);
    compressor.close();
#endif
}

void dtkCoreIOCompressorTestCase::testCreator(void)
{
    QByteArray data = QByteArray("The quick brown fox\n");
    QIODevice *io = dtkCoreIOCompressor::create("foo.gz");
    QByteArray text;
#if defined(DTK_HAVE_ZLIB)
    QVERIFY(io != nullptr);
    io->open(QIODevice::ReadOnly);
    text = io->readLine();
    QVERIFY(data == text);

    data = QByteArray("hello world\n");
    text = io->readLine();
    QVERIFY(data == text);
    io->close();
    delete io;
#else
    QVERIFY(io == nullptr);
#endif

    // read uncompress
    data = QByteArray("The quick brown fox\nhello world\n");
    QFile file("foobar");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

    io = dtkCoreIOCompressor::create("foobar");
    data = QByteArray("The quick brown fox\n");
    QVERIFY(io != nullptr);
    io->open(QIODevice::ReadOnly);
    text = io->readLine();
    QVERIFY(data == text);

    data = QByteArray("hello world\n");
    text = io->readLine();
    QVERIFY(data == text);
    io->close();
    delete io;
}

void dtkCoreIOCompressorTestCase::cleanup(void)
{
}

void dtkCoreIOCompressorTestCase::cleanupTestCase(void)
{
}

DTKCORETEST_MAIN_NOGUI(dtkCoreIOCompressorTest, dtkCoreIOCompressorTestCase)

//
// dtkCoreIOCompressorTest.cpp ends here
