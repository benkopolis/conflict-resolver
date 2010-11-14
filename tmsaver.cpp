#include "tmsaver.h"
#include <QDebug>
#include <QTextStream>

TMSaver::TMSaver(QObject *parent) :
    Saver(parent)
{
}

bool TMSaver::saveContent(const QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all)
{
    QFile f(file);
    if(f.open(QIODevice::Text |  QIODevice::ReadWrite  | QIODevice::Append) == false)
    {
	qDebug() << " nie udalo sie otworzyc " << endl;
	return false;
    }
    QTextStream fs(&f);
    rheader.setRecordCount(all);
    QString header = rheader.writeHeader();
    if(rheader != TMHeader())
    {
        if(f.size() == 0)
        { /// TODO zmiana ilosci rekordow w istniejacym naglowku
	    fs << header << endl;
        }
        else
        {
	    QString all_file, tmpf;
	    QTextStream af(&all_file);
            fs.seek(0);
	    fs.readLine();
            while(fs.atEnd() == false)
            {
		tmpf = fs.readLine();
		af << tmpf << endl;
	    }
            f.remove();
            if(f.open(QIODevice::WriteOnly | QIODevice::Text) == false)
            {
                qDebug() << " nie udalo sie otworzyc " << endl;
                return false;
            }
            fs.seek(0);
	    fs << header << endl;
	    fs << all_file;
	}
    }
    QFile dump("duties.txt"); // TODO - wybor pliku, tak zeby dawalo rade zapisywac na win7
    dump.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream dstream(&dump);
    QHash<FuzzyStrings, ContentRecord* >::iterator currentList = conflicts.begin();
    while(currentList != conflicts.end())
    {
	if((*currentList)->status() == ContentRecord::Confirmed || (*currentList)->status() == ContentRecord::NotResolved
	   || (*currentList)->status() == ContentRecord::None)
	{
	    fs << (*currentList)->toRecordString() << endl;
	}
	else if((*currentList)->status() == ContentRecord::Delayed)
	{
	    dstream << (*currentList)->toRecordString() << endl;
	}
	else if((*currentList)->status() == ContentRecord::Denied)
	{
	    ; // do nothing? ok
	}
        ++currentList;
    }
    dump.close();
    f.close();
    return true;
}

bool TMSaver::saveReversedContent(const QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all)
{
    QFile f(file);
    if(f.open(QIODevice::Append | QIODevice::Text) == false) {
	qDebug() << " nie udalo sie otworzyc " << endl;
	return false;
    }
    QTextStream fs(&f);
    rheader.setRecordCount(all);
    QString header = rheader.writeReversedHeader();
    if(rheader != TMHeader())
    {
        if(f.size() == 0)
        {
            fs << header << endl;
        }
        else
        {
            QString all_file, tmpf;
            QTextStream af(&all_file);
            fs.seek(0);
            fs.readLine();
            while(fs.atEnd() == false)
            {
                tmpf = fs.readLine();
                af << tmpf << endl;
            }
            f.remove();
            if(f.open(QIODevice::WriteOnly | QIODevice::Text) == false)
            {
                qDebug() << " nie udalo sie otworzyc " << endl;
                return false;
            }
            fs.seek(0);
            fs << header << endl;
            fs << all_file;
        }
    }
    QFile dump("duties.txt"); // TODO - wybor pliku, tak zeby dawalo rade zapisywac na win7
    dump.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream dstream(&dump);
    QHash<FuzzyStrings,ContentRecord* >::iterator currentList = conflicts.begin();
    QList<ContentRecord* >::iterator ii;
    while(currentList != conflicts.end())
    {
	if((*currentList)->status() == ContentRecord::Confirmed || (*currentList)->status() == ContentRecord::NotResolved
	   || (*currentList)->status() == ContentRecord::None)
	{
	    fs << (*currentList)->toReversedRecordString() << endl;
	}
	else if((*currentList)->status() == ContentRecord::Delayed)
	{
	    dstream << (*currentList)->toReversedRecordString() << endl;
	}
	else if((*currentList)->status() == ContentRecord::Denied)
	{
	    ; // do nothing? ok
	}
	++currentList;
    }
    f.close();
    return true;
}

bool TMSaver::saveContent(QTextStream& bufor, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all)
{
    if(rheader != TMHeader())
    {
        rheader.setRecordCount(all);
        QString header = rheader.writeHeader();
        bufor << header << endl;
    }
    QHash<FuzzyStrings, ContentRecord* >::iterator currentList = conflicts.begin();
    while(currentList != conflicts.end())
    {
        bufor << (*currentList)->toRecordString() << endl;
        ++currentList;
    }
    return true;
}

bool TMSaver::saveReversedContent(QTextStream& bufor, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all)
{
    if(rheader != TMHeader())
    {
        rheader.setRecordCount(all);
        QString header = rheader.writeReversedHeader();
        bufor << header << endl;
    }
    QHash<FuzzyStrings,ContentRecord* >::iterator currentList = conflicts.begin();
    QList<ContentRecord* >::iterator ii;
    while(currentList != conflicts.end())
    {
        bufor << (*currentList)->toReversedRecordString() << endl;
        ++currentList;
    }
    return true;
}
