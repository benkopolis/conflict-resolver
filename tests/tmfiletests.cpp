#include "tmfiletests.h"

TMFileTests::TMFileTests(QObject *parent) :
    QObject(parent)
{
}

void GlossaryFileTests::initTestCase()
{
    qDebug() << "BEGIN GLOSSARY FILE TESTS";
}

void GlossaryFileTests::init()
{
    _gloss = new GlossaryFile(this);
    _testStrings.push_back("..........,,,,,,, ......., :::;;;;");
    _testStrings.push_back("1234,654 345.45.432.");
    _testStrings.push_back("Ala 1111dmfg1111 ......d... .d.d dadla...");
    _testStrings.push_back("11111mmmmm1mm1;mm1m:1m1111m,aaaaaaaaa44444444444444aaaaaaaaa,,,");
    _testStrings.push_back("Ala,ma 3 koty &");
    _testStrings.push_back("ala.333 ma, jeden,dwa trzy.");
}

void GlossaryFileTests::cleanup()
{
    delete _gloss;
    _testStrings.clear();
}

void GlossaryFileTests::cleanupTestCase()
{
    qDebug() << "END GLOSSARY FILE TESTS";
}


void TMFileparseTest()
{
    QFile f("C:\\Users\\zby\\Desktop\\tmx\\UKE TM - Raport_rynek_telekomunikacyjny_2009_zm.doc.txt");
    QCOMPARE(f.open(QFile::ReadOnly), true);
    QCOMPARE(_gloss->processWithTabs(f), true);
}
