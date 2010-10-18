#include "tmfile.h"
#include <QTextStream>
#include <QRegExp>
#include "tmrecord.h"
#include "inifile.h"

TMFile::TMFile(QObject *parent) :
    GlossaryFile(parent)
{
}


/**
  *
  */
bool  TMFile::processWithTabs(QFile & file) {
    QTextStream f(&file);
    QFile dump("dump.txt");
    dump.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream dstream(&dump);
    QString temp, ln1, ln2;
    QString text;
    _header.clear();
    QTextStream forHeader(&_header);
    forHeader << f.readLine(); // przeczytany naglowek
    processHeader();
    TMRecord* tmr=0;
    QDate d;
    QTime t;
    QRegExp rexp(IniFile::instance()->m_regex, Qt::CaseInsensitive);
    QChar tab('\t'), nl('\n'), tempChar;
    while(!f.atEnd()) { // czytaj linie w pliku
	QString line(f.readLine());
	if(line.contains(rexp) == false) {
	    dstream << line << endl;
	    ++_corrupted;
	    continue;
	}
	QTextStream iline(&line);
	iline >> temp;
	if(this->isDateTime(temp, &d, &t) == false) {
	    ++_corrupted;
	    dstream << line << endl;
	    continue;
	}
	tmr = new TMRecord(this);
	tmr->setDate(d);
	tmr->setTime(t);
	iline >> temp;
	if(iline.atEnd()){
	    ++_corrupted;
	    dstream << line << endl;
	    continue;
	}
	tmr->setAuthor(temp);
	iline >> temp;
	if(iline.atEnd()){
	    ++_corrupted;
	    dstream << line << endl;
	    continue;
	}
	tmr->setAuthorId(temp);
	iline >> ln1;
	if(iline.atEnd()){
	    ++_corrupted;
	    dstream << line << endl;
	    continue;
	}
	tmr->setSourceCode(ln1);
	bool con = false;
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
	iline >> ln2;
	if(iline.atEnd()){
	    ++_corrupted;
	    dstream << line << endl;
	    continue;
	}
	tmr->setTargetCode(ln2);
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
	} while(iline.atEnd() == false);
	if(con) continue;
	tmr->setTarget(text);
        _content->insertMulti(FuzzyStrings(tmr->source()), tmr);
	text.clear();
	++_all;
    }
    dump.close();
    return true;
}


/**
  *
  */
void TMFile::processHeader() {
    _rheader.readHeader(_header);
}
