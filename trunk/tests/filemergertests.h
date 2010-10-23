#ifndef FILEMERGERTESTS_H
#define FILEMERGERTESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include "Tests.h"

class FileMergerTests : public QObject
{
Q_OBJECT
public:
    explicit FileMergerTests(QObject *parent = 0);

signals:

public slots:

private slots:

    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

};

DECLARE_TEST(FileMergerTests)

#endif // FILEMERGERTESTS_H
