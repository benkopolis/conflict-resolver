#include "tmrecord.h"

TMRecord::TMRecord(QObject *parent) :
    ContentRecord(parent)
{
}

TMRecord::TMRecord( const QByteArray & source , const QByteArray & target , const unsigned lineNumber ,
		    const QDate& date, const QTime& time, const QString& sourceCode, const QString& targetCode,
		    const QString& one, const QString& two, QObject* parent ):
    ContentRecord(source, target, lineNumber, parent),
    _date(date),
    _time(time),
    _sourceCode(sourceCode),
    _targetCode(targetCode),
    _author(one),
    _authorId(two)
{
}

QString TMRecord::toListString() const {
    QString ret;
//    ret.append(_date.toString(QString("yyyy.MM.dd")));
//    ret.append(QString(" | "));
//    ret.append(_time.toString(QString("hh:mm:ss")));
//    ret.append(QString(" | "));
    ret.append(_sourceCode);
    ret.append(QString(" | "));
    ret.append(_source);
    ret.append(QString(" | "));
    ret.append(_targetCode);
    ret.append(QString(" | "));
    ret.append(_target);
    return ret;
}

QString TMRecord::toRecordString() const {
    QString ret;
    ret.append(_date.toString(QString("yyyyMMdd")));
    ret.append(QChar('~'));
    ret.append(_time.toString(QString("hhmmss")));
    ret.append(QChar('\t'));
    ret.append(this->_author);
    ret.append(QChar('\t'));
    ret.append(this->_authorId);
    ret.append(QChar('\t'));
    ret.append(_sourceCode);
    ret.append(QChar('\t'));
    ret.append(_source);
    ret.append(QChar('\t'));
    ret.append(_targetCode);
    ret.append(QChar('\t'));
    ret.append(_target);
    return ret;
}

QString TMRecord::toReversedRecordString() const {
    QString ret;
    ret.append(_date.toString(QString("yyyyMMdd")));
    ret.append(QChar('~'));
    ret.append(_time.toString(QString("hhmmss")));
    ret.append(QChar('\t'));
    ret.append(this->_author);
    ret.append(QChar('\t'));
    ret.append(this->_authorId);
    ret.append(QChar('\t'));
    ret.append(_targetCode); //
    ret.append(QChar('\t')); // switched
    ret.append(_target);     //
    ret.append(QChar('\t'));
    ret.append(_sourceCode); //
    ret.append(QChar('\t')); // with this
    ret.append(_source);     //
    return ret;
}
