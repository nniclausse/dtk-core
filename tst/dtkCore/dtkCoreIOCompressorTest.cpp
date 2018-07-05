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

void dtkCoreIOCompressorTestCase::cleanup(void)
{
}

void dtkCoreIOCompressorTestCase::cleanupTestCase(void)
{
}

DTKCORETEST_MAIN_NOGUI(dtkCoreIOCompressorTest, dtkCoreIOCompressorTestCase)

//
// dtkCoreIOCompressorTest.cpp ends here
