#include "glossaryfile.h"
#include <QStack>
#include <QTextStream>
#include <QRegExp>
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

bool GlossaryFile::validateText(const QString& text)
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