#ifndef GLOSSARYFILETESTS_H
#define GLOSSARYFILETESTS_H

#include <QObject>
#include <QtTest/QtTest>

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
};

#endif // GLOSSARYFILETESTS_H
