#include "tmfile.h"
#include <QTextStream>
#include <QRegExp>
#include "tmrecord.h"
#include "inifile.h"

TMFile::TMFile(QObject *parent) :
    GlossaryFile(parent)
{
}

TMHeader TMFile::header() const
{
    return this->_rheader;
}

/**
  *
  */
bool  TMFile::processWithTabs(QFile & file) {
    QTextStream f(&file);
    QFile dump("duties.txt"); // TODO - wybor pliku, tak zeby dawalo rade zapisywac na win7
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
    if(IniFile::instance()->m_regex.startsWith("(?:") == false)
	rexp.setPattern("(?:[0-9]{8,8}~[0-9]{6,6}\t*[A-Za-z]*\t[0-9]{1,}\t*\t*\t*)");
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
	if(validateText(text) == false) {
	    ++_corrupted;
	    dstream << line << endl;
	    text.clear();
	    continue;
	}
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
	if(validateText(text) == false) {
	    ++_corrupted;
	    dstream << line << endl;
	    text.clear();
	    continue;
	}
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
