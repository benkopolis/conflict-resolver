#include <QtGui/QApplication>
#include <QDebug>
#include <QMultiMap>
#include "mainwindow.h"
#include "inifile.h"
#include "tests/Tests.h"
#include "engine/fuzzyenginethread.h"

#if ZBY_DEBUG

TEST_MAIN

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IniFile::instance()->setIniFileDir("./base.ini");
    IniFile::instance()->readIniFile();
    MainWindow w;
    FuzzyEngineThread fet;
    IniFile::instance()->setFuzzyEngine(&fet);
    fet.buffSize(IniFile::instance()->fbufferX(), IniFile::instance()->fbufferY());
//    fet.start(QThread::NormalPriority);
    w.show();
    int res = a.exec();
    IniFile::instance()->setFBufferX(fet.getX());
    IniFile::instance()->setFBufferY(fet.getY());
    IniFile::instance()->saveIniFile();
    return res;
}

#endif
