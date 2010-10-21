#include "tmsaver.h"
#include <QDebug>

TMSaver::TMSaver(QObject *parent) :
    Saver(parent)
{
}

bool TMSaver::saveContent(QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all) {
    QFile f(file);
    if(f.open(QIODevice::Text |  QIODevice::ReadWrite) == false) {
	qDebug() << " nie udalo sie otworzyc " << endl;
	return false;
    }
//    f.close();
    QTextStream fs(&f);
    if(rheader != TMHeader())
    {
	if(f.size() == 0) { /// TODO zmiana ilosci rekordow w istniejacym naglowku
	    rheader.setRecordCount(all);
	    QString header = rheader.writeHeader();
	    fs << header << endl;
	} else {
	    QString all_file, tmpf;
	    QTextStream af(&all_file);
	    rheader.setRecordCount(all);
	    QString header = rheader.writeHeader();
	    fs.readLine();
	    while(fs.atEnd() == false) {
		tmpf = fs.readLine();
		af << tmpf << endl;
	    }
	    fs << header << endl;
	    fs << all_file;

	}
    }
    QHash<FuzzyStrings, ContentRecord* >::iterator currentList = conflicts.begin();
    while(currentList != conflicts.end()) {
        fs << (*currentList)->toRecordString() << endl;
        ++currentList;
    }
    f.close();
    return true;
}

bool TMSaver::saveReversedContent(const QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all) {
/// TODO ooooooooooooooooooooooooooooooooooooooooooooooooooooo
    QFile f(file);
    if(f.open(QIODevice::Append | QIODevice::Text) == false) {
	qDebug() << " nie udalo sie otworzyc " << endl;
	return false;
    }
    QTextStream fs(&f);
    if(f.size() == 0) { /// TODO zmiana ilosci rekordow w istniejacym naglowku
	rheader.setRecordCount(all);
	QString header = rheader.writeReversedHeader();
	fs << header << endl;
    }
    QHash<FuzzyStrings,ContentRecord* >::iterator currentList = conflicts.begin();
    QList<ContentRecord* >::iterator ii;
    while(currentList != conflicts.end()) {
        fs << (*currentList)->toReversedRecordString() << endl;
	++currentList;
    }
    f.close();
    return true;
}

