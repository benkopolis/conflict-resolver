#include <QtGui/QApplication>
#include <QDebug>
#include <QMultiMap>
#include "mainwindow.h"
#include "inifile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QMultiMap<int, int> m;
//    m.insert(0-1, 1); m.insert(0-2, 2); m.insert(0-3, 3);
//    QMultiMap<int, int>::iterator ii = m.begin();
//    while(ii != m.end()) {
//	qDebug() << ii.key() << " " << ii.value();
//	++ii;
//    }
    IniFile::instance()->readIniFile();
    MainWindow w;
    w.show();
    return a.exec();
}
