#ifndef TMRECORD_H
#define TMRECORD_H

#include <QDateTime>
#include "contentrecord.h"

class TMRecord : public ContentRecord
{
Q_OBJECT
public:
    explicit TMRecord(QObject *parent = 0);
    TMRecord( const QByteArray & source , const QByteArray & target , const unsigned lineNumber ,const QDate& date,
	      const QTime& time, const QString& sourceCode, const QString& targetCode, const QString& one,
	      const QString& two, QObject* parent = 0);

    inline QDate date() const { return _date; };
    inline void setDate(QDate date) { _date = date; };
    inline QTime time() const { return _time; };
    inline void setTime(QTime time) { _time = time; };
    inline QString sourceCode() const { return _sourceCode; };
    inline void setSourceCode(QString sourceCode) { _sourceCode = sourceCode; };
    inline QString targetCode() const { return _targetCode; };
    inline void setTargetCode(QString targetCode) { _targetCode = targetCode; };
    inline QString author() const { return _author; };
    inline void setAuthor(QString idOne) { _author = idOne; };
    inline QString authorId() const { return _authorId; };
    inline void setAuthorId(QString idTwo) { _authorId = idTwo; };

    virtual QString toListString() const;
    virtual QString toRecordString() const;
    virtual QString toReversedRecordString() const;

signals:

public slots:

protected:

    QDate _date;
    QTime _time;
    QString _sourceCode;
    QString _targetCode;
    QString _author;
    QString _authorId;

};

#endif // TMRECORD_H
