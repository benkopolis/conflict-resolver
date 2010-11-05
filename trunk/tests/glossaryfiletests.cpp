#include "glossaryfiletests.h"

GlossaryFileTests::GlossaryFileTests(QObject *parent) :
    QObject(parent)
{
}

void GlossaryFileTests::initTestCase()
{
    qDebug() << "BEGIN TM FILE TESTS";
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
    qDebug() << "END TM FILE TESTS";
}

void GlossaryFileTests::validateTest()
{
    QCOMPARE(_gloss->validateText(_testStrings.at(0)), false);
    QCOMPARE(_gloss->validateText(_testStrings.at(1)), false);
    QCOMPARE(_gloss->validateText(_testStrings.at(2)), false);
    QCOMPARE(_gloss->validateText(_testStrings.at(3)), false);
    QCOMPARE(_gloss->validateText(_testStrings.at(4)), true);
    QCOMPARE(_gloss->validateText(_testStrings.at(5)), true);
}

void GlossaryFileTests::correctTest()
{
//    QCOMPARE(_gloss->correctText(_testStrings.at(2)), QString("Ala 1111dmfg1111 . d... . d. d dadla."));
    QCOMPARE(_gloss->correctText(_testStrings.at(3)), QString("11111mmmmm1mm1; mm1m: 1m1111m, aaaaaaaaa44444444444444aaaaaaaaa,"));
    QCOMPARE(_gloss->correctText(_testStrings.at(4)), QString("Ala, ma 3 koty"));
    QCOMPARE(_gloss->correctText(_testStrings.at(5)), QString("ala. 333 ma, jeden, dwa trzy."));//tutaj ze spacja na koncu

}

