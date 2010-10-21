#include "filemergertests.h"

FileMergerTests::FileMergerTests(QObject *parent) :
    QObject(parent)
{
}

void FileMergerTests::initTestCase()
{
    qDebug() << "BEGIN UNIT TESTS OF FILE MERGER";
}

void FileMergerTests::init()
{

}

void FileMergerTests::cleanup()
{

}

void FileMergerTests::cleanupTestCase()
{
    qDebug() << "END UNIT TESTS OF FILE MERGER";
}
