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
#include <dtkCore/dtkCoreIODevice.h>

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
    QFile file("foo.gz");
    QByteArray data = QByteArray("The quick brown fox\nhello world\n");
    dtkCoreIOCompressor compressor(&file);
    compressor.open(QIODevice::WriteOnly);
    compressor.write(data);
    compressor.close();
}

void dtkCoreIOCompressorTestCase::testRead(void)
{
    QByteArray data = QByteArray("The quick brown fox\n");
    QFile file("foo.gz");

    dtkCoreIOCompressor compressor(&file);
    compressor.open(QIODevice::ReadOnly);
    QByteArray text = compressor.readLine();
    QVERIFY(data == text);

    data = QByteArray("hello world\n");
    text = compressor.readLine();
    QVERIFY(data == text);
    compressor.close();
}

void dtkCoreIOCompressorTestCase::testdtkIODevice(void)
{
    QByteArray data = QByteArray("The quick brown fox\n");
    QIODevice *io = dtkCoreIODevice::create("foo.gz");
    QVERIFY(io != nullptr);
    io->open(QIODevice::ReadOnly);
    QByteArray text = io->readLine();
    QVERIFY(data == text);

    data = QByteArray("hello world\n");
    text = io->readLine();
    QVERIFY(data == text);
    io->close();
    delete io;

    // read uncompress

    data = QByteArray("The quick brown fox\nhello world\n");
    QFile file("foobar");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

    io = dtkCoreIODevice::create("foobar");
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
