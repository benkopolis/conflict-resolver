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

TMHeader GlossaryFile::header() const
{
    return TMHeader();
}

/**
  *
  */
Error GlossaryFile::processWithTabs(QFile & file) {
    QTextStream f(&file);
    QFile dump("duties.txt"); // TODO - wybor pliku, tak zeby dawalo rade zapisywac na win7
    dump.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream dstream(&dump);
    QString temp, text;
    ContentRecord* tmr=0;
    bool con = false;
    QChar tab('\t'), nl('\n'), tempChar;
    while(!f.atEnd()) { // czytaj linie w pliku
	QString line(f.readLine());
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
	if(validateText(text) == false) {
	    ++_corrupted;
	    dstream << line << endl;
	    text.clear();
	    continue;
	}
	text = this->correctText(text);
	tmr->setSource(text);
	text.clear();
	tempChar = QChar();
	do {
	    if(tempChar != QChar())
                text = text.append(" ");
	    iline >> temp;
	    text = text.append(temp);
	    iline >> tempChar;
	} while(iline.atEnd() == false && tempChar != tab);
	if(con) continue;
	text = this->correctText(text);
	if(validateText(text) == false) {
	    ++_corrupted;
	    dstream << line << endl;
	    text.clear();
	    continue;
	}
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
    return Error();
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
    QRegExp space(QString("(?:\\s)"));
    QString cleared = removeMultiple(text);
    QStringList words = cleared.split(space);
    QString res;
    foreach(QString s, words)
    {
        QString tmp = replaceSplitters(s);
        res.append(tmp);
        res.append(QChar(' '));
    }
    res = res.trimmed();
    res.replace(QRegExp("(?:\\s{2,})"), QString(" "));
    return res;
}

bool GlossaryFile::validateText(const QString& text, bool* store)
{
    if(text.isEmpty())
	return false;
    QRegExp ampCount("(&)");
    QRegExp numCount("([0-9])");
    QRegExp wsCount("(\\s)");
    QRegExp nonCount("(\\W|\\.|,|\\:|;)");
    int cc=0, wc=0, nc=0, ac=0;
    cc =  GlossaryFile::getCapCount(numCount, text);
    wc = GlossaryFile::getCapCount(wsCount, text);
    nc = GlossaryFile::getCapCount(nonCount, text);
    ac = GlossaryFile::getCapCount(ampCount, text);
    int badness = cc - wc + nc -ac;
    int validness = badness - text.length()/2;
    if(badness > text.length()/2)
    {
	if(store)
	{
	    if(cc > text.length()/2 || validness <-5)
		*store = true;
	    else
		*store = false;
	}
	return false;
    }
    return true;
}

QString GlossaryFile::removeMultiple(const QString& text)
{
    QString res = text;
    res.replace(QRegExp("(?:\\.{3,3}(\\s|\\.)"), "__THREEZMDOTS__ ");
    res.replace(QRegExp("(?:\\.{2,})"), ".");
    res.replace(QRegExp("(?:,{2,})"), ",");
    res.replace(QRegExp("(?:\\:{2,}"), ":");
    res.replace(QRegExp("(?:;{2,}"), ";");
    res.replace("__THREEZMDOTS__ ", "... ");
    res.replace(QRegExp("(?:\\s{2,})"), QString(" "));
    return res;
}

QString GlossaryFile::replaceSplitters(const QString& word)
{
    QString w = word;
    static QRegExp splitters[4] = {QRegExp("(?:\\.)"), QRegExp("(?:,)"), QRegExp("(?:\\:)"), QRegExp("(?:;)")};
    w.replace(QRegExp("(?:\\.{3,3}(\\s|\\.)"), "__THREEZMDOTS__ ");
    QRegExp end("(\\.|,|;|\\:)");
    int e = GlossaryFile::getCapCount(end, w), iter = 0;
    while(iter < e)
    {
        iter++;
        if(w.contains(splitters[GlossaryFile::Dot]))
        {
            w.replace(splitters[GlossaryFile::Dot], QString(". "));
        }
        else if(w.contains(splitters[GlossaryFile::Coma]))
        {
            w.replace(splitters[GlossaryFile::Coma], QString(", "));
        }
        else if(w.contains(splitters[GlossaryFile::Colon]))
        {
            w.replace(splitters[GlossaryFile::Colon], QString(": "));
        }
        else if(w.contains(splitters[GlossaryFile::Semicolon]))
        {
            w.replace(splitters[GlossaryFile::Semicolon], QString("; "));
        }
    }
    w.replace("__THREEZMDOTS__ ", "... ");
    return w;
}

int GlossaryFile::getCapCount(const QRegExp& r, const QString& t)
{
    int pos = 0;
    int count = 0;
    while((pos = r.indexIn(t, pos)) > -1)
    {
        ++count;
        pos += r.matchedLength();
    }
    return count;
}

/**
  *
  */
bool GlossaryFile::isDateTime(const QString& str, QDate* date, QTime* time) const {
    if(str.length() < 14)
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
    if(str.contains(QRegExp("(~|=)")))
    {
	h = str.mid(9, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
	min = str.mid(11, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
	s = str.mid(13, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
    }
    else
    {
	h = str.mid(8, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
	min = str.mid(10, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
	s = str.mid(12, 2).toInt(&ok, 10);
	if(ok == false)
	    return false;
    }
    if(time != 0)
	time->setHMS(h, min, s);
    return true;
}

Error GlossaryFile::processHeader()
{
    return Error();
}
