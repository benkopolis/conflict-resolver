#include <QtGui/QApplication>
#include <QDebug>
#include <QMultiMap>
#include "mainwindow.h"
#include "inifile.h"

QString correctText(const QString& text)
{
    QStringList words = text.split(QRegExp(QString("(?:\\s)")));
    QString res;
    QRegExp r(QString("(?:\\.|,|;|:)"));
    foreach(QString s, words)
    {
	if(s.contains(r))
	{
	    QStringList inner = s.split(r);
	    QString ires;
	    foreach(QString is, inner)
	    {
		ires.append(is);
		ires.append(QChar(' '));
	    }
	    res.append(ires);
	} else
	    res.append(s);
	res.append(QChar(' '));
    }
    return res;
}

bool validateText(const QString& text)
{
    QRegExp numCount("(?:[0-9])");
    QRegExp wsCount("(?:\\s)");
    QRegExp nonCount("(?:\\W)");
    numCount.indexIn(text);
    int cc = numCount.captureCount();
    wsCount.indexIn(text);
    int wc = wsCount.captureCount();
    nonCount.indexIn(text);
    int nc = nonCount.captureCount();
    return (text.length() - wc)/2 > cc ? ((text.length() - wc)/2 > nc ? true : false) : false;
}



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
