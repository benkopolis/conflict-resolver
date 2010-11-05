#ifndef TMFILETESTS_H
#define TMFILETESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include "tmfile.h"

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

#endif // TMFILETESTS_H
