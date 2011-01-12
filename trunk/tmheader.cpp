#include "tmheader.h"
#include <QTextStream>


TMHeader::TMHeader(QObject *parent) :
    QObject(parent)
{
    _recordsCount = 0;
}

TMHeader::TMHeader(const TMHeader& another) :
    QObject(another.parent())
{
    _dt = another._dt;
    _tdt = another._tdt;
    _authors = another._authors;
    _recordsCount = another._recordsCount;
    _sourceCode = another._sourceCode;
    _comment = another._comment;
    _targetCode = another._targetCode;
    _rest = another._rest;
}

// Example headers
// %20100422~120101	%+A!	%TU=00000308	%EN	%Wordfast translation memory version v.5	%PL
// %This is a header - do not delete, move or sort.
//
// %20100507~173730	%User ID,ZBY,ZBY zby	%TU=00000000	%PL-PL	%Wordfast TM v.546/00	%EN-GB	%-----------

bool TMHeader::operator != (const TMHeader& another) const {
    if(this->_authors != another._authors)
        return true;
    if(this->_comment != another._comment)
        return true;
    if(this->_dt != another._dt)
        return true;
    if(this->_recordsCount !=  another._recordsCount)
        return true;
    if(this->_rest != another._rest)
        return true;
    return false;
}


Error TMHeader::readHeader(const QString &h) {
    Error err;
    err.addAttribute("error_source", h);
    if(this->isDateTime(h) == false) {
	err.setErrorMessage("Niepoprawna data w naglowku");
	return err;
    }
    QString hh(h);
    QTextStream in(&hh, QIODevice::ReadOnly | QIODevice::Text);
    QString temp, text;
    QChar tab('\t'), tempChar;
    in >> _tdt; // skip date
    _authors.clear();
    do {
	if(tempChar != QChar())
	    _authors = _authors.append(tempChar);
	in >> temp;
	_authors = _authors.append(temp);
	in >> tempChar;
    } while(tempChar != tab);
    in >> temp;
    bool ok = false;
    _recordsCount = temp.mid(4, 8).toUInt(&ok);
    if(!ok)
    {
	err.setErrorMessage("Zly format liczby rekordow.");
	return err;
    }
    in >> _sourceCode;
    tempChar = QChar();
    do {
	if(tempChar != QChar())
	    _comment = _comment.append(tempChar);
	in >> temp;
	_comment = _comment.append(temp);
	in >> tempChar;
    } while(tempChar != tab);
    in >> _targetCode;
    while(in.atEnd() == false) {
	in >> temp;
	_rest = _rest.append(temp);
    }
    return err;
}
/*
  %20101019~120420	%User ID,JD,JD jdebowska	%TU=00000000	%PL	%Wordfast TM v.546/00	%EN	%-----------
  %20100422~120101	%+A!	%TU=00000000	%PL	%Wordfast translation memory version v.5	%EN	%This is a header - do not delete, move or sort.
  */
QString TMHeader::writeHeader() {
    QString ret;
    ret = ret.append("%20101019~120420");
    ret = ret.append(QChar('\t'));
    ret = ret.append("%User ID,JD,JD jdebowska");
    ret = ret.append(QChar('\t'));
    ret = ret.append(QString("%TU="));
    QString n = QString::number(_recordsCount, 10);
    QString tmp;
    for(int i = 0; i < 8 - n.length(); ++i)
	tmp = tmp.append(QString("0"));
    tmp = tmp.append(n);
    ret = ret.append(tmp);
    ret = ret.append(QChar('\t'));
    ret = ret.append(_sourceCode);
    ret = ret.append(QChar('\t'));
    ret = ret.append("%Wordfast TM v.546/00");
    ret = ret.append(QChar('\t'));
    ret = ret.append(_targetCode);
    ret = ret.append(QChar('\t'));
    ret = ret.append("%-----------");
    return ret;
}

QString TMHeader::writeReversedHeader() {
    QString ret;
    ret = ret.append("%20101019~120420");
    ret = ret.append(QChar('\t'));
    ret = ret.append("%User ID,JD,JD jdebowska");
    ret = ret.append(QChar('\t'));
    ret = ret.append(QString("%TU="));
    QString n = QString::number(_recordsCount, 10);
    QString tmp;
    for(int i = 0; i < 8 - n.length(); ++i)
	tmp = tmp.append(QString("0"));
    tmp = tmp.append(n);
    ret = ret.append(tmp);
    ret = ret.append(QChar('\t'));
    ret = ret.append(_targetCode); // switched
    ret = ret.append(QChar('\t'));
    ret = ret.append("%Wordfast TM v.546/00");
    ret = ret.append(QChar('\t'));
    ret = ret.append(_sourceCode); // with this
    ret = ret.append(QChar('\t'));
    ret = ret.append("%-----------");
    return ret;
}

bool TMHeader::isDateTime(const QString& str) {
    if(str.length() < 15)
	return false;
    bool ok;
    int y, m, d, h, min, s;
    y = str.mid(1, 4).toInt(&ok, 10);
    if(ok == false)
	return false;
    m = str.mid(5, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    d = str.mid(7, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    h = str.mid(10, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    min = str.mid(12, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    s = str.mid(14, 2).toInt(&ok, 10);
    if(ok == false)
	return false;
    _dt.setDate(QDate(y, m, d));
    _dt.setTime(QTime(h, min, s, 0));
    return true;
}
