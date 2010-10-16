#include "tmsaver.h"
#include <QDebug>

TMSaver::TMSaver(QObject *parent) :
    Saver(parent)
{
}

bool TMSaver::saveContent(QString& file, TMHeader& rheader, QHash<FuzzyStrings, QList<ContentRecord* > >& conflicts, unsigned all) {
    QFile f(file);
    if(f.open(QIODevice::Append | QIODevice::Text) == false) {
	qDebug() << " nie udalo sie otworzyc " << endl;
	return false;
    }
    f.close();
    QTextStream fs(&file, QIODevice::ReadWrite);
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
    QHash<FuzzyStrings, QList<ContentRecord* > >::iterator currentList = conflicts.begin();
    QList<ContentRecord* >::iterator ii;
    while(currentList != conflicts.end()) {
	for(ii = currentList->begin(); ii != currentList->end() ; ++ii) {
	    fs << (*ii)->toRecordString() << endl;
	}
	++currentList;
    }
    f.close();
    return true;
}

bool TMSaver::saveReversedContent(const QString& file, TMHeader& rheader, QHash<FuzzyStrings, QList<ContentRecord* > >& conflicts, unsigned all) {
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
    QHash<FuzzyStrings, QList<ContentRecord* > >::iterator currentList = conflicts.begin();
    QList<ContentRecord* >::iterator ii;
    while(currentList != conflicts.end()) {
	for(ii = currentList->begin(); ii != currentList->end() ; ++ii) {
	    fs << (*ii)->toReversedRecordString() << endl;
	}
	++currentList;
    }
    f.close();
    return true;
}

