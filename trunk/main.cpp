#include <QtGui/QApplication>
#include <QDebug>
#include <QMultiMap>
#include "mainwindow.h"
#include "inifile.h"
#include "tests/Tests.h"


#if ZBY_DEBUG

TEST_MAIN

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IniFile::instance()->setIniFileDir("./base.ini");
    IniFile::instance()->readIniFile();
    MainWindow w;
    w.show();
    int res = a.exec();
    IniFile::instance()->saveIniFile();
    return res;
}

#endif
