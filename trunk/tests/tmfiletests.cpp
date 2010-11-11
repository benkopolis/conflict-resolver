#include "tmfiletests.h"

TMFileTests::TMFileTests(QObject *parent) :
    QObject(parent)
{
}

void TMFileTests::initTestCase()
{
    qDebug() << "BEGIN TM FILE TESTS";
}

void TMFileTests::init()
{
    _gloss = new TMFile(this);
}

void TMFileTests::cleanup()
{
    delete _gloss;
}

void TMFileTests::cleanupTestCase()
{
    qDebug() << "END TM FILE TESTS";
}


void TMFileTests::parseTest()
{
    QFile f("C:\\Users\\zby\\Desktop\\tmx\\UKE TM - Raport_rynek_telekomunikacyjny_2009_zm.doc.txt");
    QCOMPARE(f.open(QFile::ReadOnly), true);
    QCOMPARE(_gloss->processWithTabs(f), true);
}
