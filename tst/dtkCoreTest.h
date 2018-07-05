#pragma once

#include <QtTest>

#define DTKCORETEST_MAIN_NOGUI(TestMain, TestObject)	\
    int TestMain(int argc, char *argv[]) {              \
        QCoreApplication app(argc, argv);               \
        TestObject tc;                                  \
        return QTest::qExec(&tc, argc, argv);           \
    }
