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

#include <QtCore>

class dtkCoreSettingsTestCase : public QObject
{
    Q_OBJECT

public:
     dtkCoreSettingsTestCase(void) = default;
    ~dtkCoreSettingsTestCase(void) = default;

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testTrack(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkCoreSettingsTest.h ends here
