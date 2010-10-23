#ifndef GLOSSARYFILETESTS_H
#define GLOSSARYFILETESTS_H

#include <QObject>
#include <QtTest/QtTest>
#include "Tests.h"
#include "glossaryfile.h"

class GlossaryFileTests : public QObject
{
Q_OBJECT
public:
    explicit GlossaryFileTests(QObject *parent = 0);

signals:

public slots:

private slots:

    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void validateTest();
    void correctTest();

private:

    GlossaryFile* _gloss;
    QStringList _testStrings;
};

DECLARE_TEST(GlossaryFileTests)

#endif // GLOSSARYFILETESTS_H
