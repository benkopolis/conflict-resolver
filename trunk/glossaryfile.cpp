#include "glossaryfile.h"
#include <QStack>
#include <QTextStream>
#include <QRegExp>
#include <QDebug>
#include "inifile.h"
#include "tmsaver.h"


GlossaryFile::GlossaryFile(QObject *parent) :
    QObject(parent)
{
    _conflicts = new QMultiHash<FuzzyStrings, ConflictRecord* >();
    _content = new QMultiHash<FuzzyStrings, ContentRecord* >();
    _corrupted = 0;
    _all = 0;
}

/**
  *
  */
bool GlossaryFile::processWithTabs(QFile & file) {
    QTextStream f(&file);
    QFile dump("dump.txt");
    dump.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream dstream(&dump);
    QString temp, ln1, ln2;
    QString text;
//    _header.clear();
//    QTextStream forHeader(&_header);
//    forHeader << f.readLine(); // przeczytany naglowek
//    processHeader();
    ContentRecord* tmr=0;
    QRegExp rexp(IniFile::instance()->m_regex, Qt::CaseInsensitive);
    bool con = false;
    QChar tab('\t'), nl('\n'), tempChar;
    while(!f.atEnd()) { // czytaj linie w pliku
	QString line(f.readLine());
	if(line.contains(rexp) == false) {
	    dstream << line << endl;
	    ++_corrupted;
	    continue;
	}
	QTextStream iline(&line);
	tmr = new ContentRecord(this);
	do {
	    if(tempChar != QChar())
		text = text.append(" ");
	    iline >> temp;
	    text = text.append(temp);
	    iline >> tempChar;
	    if(iline.atEnd()){
		++_corrupted;
		dstream << line << endl;
		con = true;
		break;
	    }
	} while(tempChar != tab);
	if(con) continue;
	tmr->setSource(text);
	text.clear();
	tempChar = QChar();
	do {
	    if(tempChar != QChar())
                text = text.append(" ");
	    iline >> temp;
	    text = text.append(temp);
	    iline >> tempChar;
	    if(tempChar == tab){
		++_corrupted;
		dstream << line << endl;
		con = true;
		break;
	    }
	} while(iline.atEnd() == false || tempChar != tab);
	if(con) continue;
	tmr->setTarget(text);
	text.clear();
	while(iline.atEnd() == false) {
	    iline >> temp;
	    text.append(temp);
	    text.append(" ");
	}
	text = text.mid(0, text.length() - 1);
	tmr->setComment(text);
        this->_content->insertMulti(FuzzyStrings(tmr->source()), tmr);
	text.clear();
	++_all;
    }
    dump.close();
    return true;
}

/**
  *
  */
bool GlossaryFile::saveContent(QString file) {
    bool r=false;
    TMSaver tms;
    TMHeader tmh;
    r = tms.saveContent(file, tmh, *this->_content, this->_all);
    return r;
}

/**
  *
  */
bool GlossaryFile::saveReversedContent(QString file) {
    bool r=false;
    TMSaver tms;
    TMHeader tmh;
    r = tms.saveReversedContent(file, tmh, *this->_content, this->_all);
    return r;
}

QString GlossaryFile::correctText(const QString& text)
{
    qDebug() << "in: " << text;
    QRegExp exc("(\\.{3,3}\\s)");
    QRegExp threedots("((\\s|\\w)\\.\\.\\.\\s)");
    QRegExp space(QString("(?:\\s)"));
    int ex = exc.indexIn(text);
    QString cleared = removeMultiple(text);
    qDebug() << "cleared: " << cleared;
    QStringList words = cleared.split(space);
    QString res;/*
    QRegExp r(QString("((\\.{1,1}|,|;|\\:)|\\S)"));
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
    }*/
    res.trimmed();

    qDebug() << "out: " << res;
    return res;
}

bool GlossaryFile::validateText(const QString& text)
{
    if(text.isEmpty())
	return false;
    QRegExp numCount("([0-9])");
    QRegExp wsCount("(\\s)");
    QRegExp nonCount("(\\W|\\.|,|\\:|;)");
    qDebug() << text;
    int cc=0, wc=0, nc=0;
    int pos1 = numCount.indexIn(text);
    qDebug() << "pos: " << pos1;
    if(pos1 != -1)
	cc = numCount.capturedTexts().size() -1;
    qDebug() << "numbers: " << cc;
    int pos2 = wsCount.indexIn(text);
    qDebug() << "pos: " << pos2;
    if(pos2 != -1)
	wc = wsCount.capturedTexts().size() - 1;
    qDebug() << "white spaces: " << wc;
    int pos3 = nonCount.indexIn(text);
    qDebug() << "pos: " << pos3;
    if(pos3 != -1)
	nc = nonCount.capturedTexts().size() - 1;
    qDebug() << "non word: " << nc;
    int badness = cc + wc + nc;
    qDebug() << "badness: " << badness << " and text.length/2: " << text.length()/2;
    if(badness > text.length()/2)
	return false;
    return true;
}

QString GlossaryFile::removeMultiple(const QString& text)
{
    QString res = text;
    res.replace(QRegExp("(?:\\.{3,3}\\s)"), "^^^ ");
    res.replace(QRegExp("(?:\\.{2,})"), ".");
    res.replace(QRegExp("(?:,{2,})"), ",");
    res.replace(QRegExp("(?:\\:{2,}"), ":");
    res.replace(QRegExp("(?:;{2,}"), ";");
    res.replace("^^^ ", "... ");
    res.replace(QRegExp("(\\s{2,})"), QString(" "));
    return res;
}

/**
  *
  */
bool GlossaryFile::isDateTime(const QString& str, QDate* date, QTime* time) const {
    if(str.length() < 15)
	return false;
    bool ok;
    int y, m, d, h, min, s;
    y = str.mid(0, 4).toInt(&ok, 10);
    if(ok == false)
	return false;
    m = str.mid(4, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    d = str.mid(6, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    if(date != 0)
	date->setDate(y, m, d);
    h = str.mid(9, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    min = str.mid(11, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    s = str.mid(13, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    if(time != 0)
	time->setHMS(h, min, s);
    return true;
}
