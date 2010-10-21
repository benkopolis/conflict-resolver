#ifndef FILEMERGERTESTS_H
#define FILEMERGERTESTS_H

#include <QObject>
#include <QtTest/QtTest>

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

#endif // FILEMERGERTESTS_H
