#ifndef TMFILETESTS_H
#define TMFILETESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include "files/tmfile.h"
#include "Tests.h"

class TMFileTests : public QObject
{
Q_OBJECT
public:
    explicit TMFileTests(QObject *parent = 0);

signals:

public slots:

    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void parseTest();

private:

    TMFile *_gloss;

};

DECLARE_TEST(TMFileTests)

#endif // TMFILETESTS_H
