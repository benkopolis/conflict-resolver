#include "tmxrecord.h"

TMXRecord::TMXRecord(QObject *parent) :
    TMRecord(parent)
{
}

QString TMXRecord::toListString() const {
    QString ret;
//    ret.append(_date.toString(QString("yyyy.MM.dd")));
//    ret.append(QString(" | "));
//    ret.append(_time.toString(QString("hh:mm:ss")));
//    ret.append(QString(" | "));
    ret.append(_sourceCode);
    ret.append(QString(" | "));
    ret.append(source());
    ret.append(QString(" | "));
    ret.append(_targetCode);
    ret.append(QString(" | "));
    ret.append(target());
    return ret;
}

QString TMXRecord::toRecordString() const {
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
    ret.append(source());
    ret.append(QChar('\t'));
    ret.append(_targetCode);
    ret.append(QChar('\t'));
    ret.append(target());
    return ret;
}

QString TMXRecord::toReversedRecordString() const {
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
    ret.append(target());     //
    ret.append(QChar('\t'));
    ret.append(_sourceCode); //
    ret.append(QChar('\t')); // with this
    ret.append(source());     //
    return ret;
}
