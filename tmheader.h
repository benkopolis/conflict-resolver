#ifndef TMHEADER_H
#define TMHEADER_H

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include "commons/error.h"

// Example headers
// %20100422~120101	%+A!	%TU=00000308	%EN	%Wordfast translation memory version v.5	%PL
// %This is a header - do not delete, move or sort.
//
// %20100507~173730	%User ID,ZBY,ZBY zby	%TU=00000000	%PL-PL	%Wordfast TM v.546/00	%EN-GB	%-----------

class TMHeader : public QObject
{
Q_OBJECT
public:
    explicit TMHeader(QObject *parent = 0);
    TMHeader(const TMHeader& another);

    Error readHeader(const QString& h);
    QString writeHeader();
    QString writeReversedHeader();
    inline QString sourceCode() const { return _sourceCode; }
    inline QString targetCode() const { return _targetCode; }

    inline void setRecordCount(const unsigned rc) { _recordsCount = rc; }
    bool operator != (const TMHeader& another) const;

signals:

public slots:

private:

    bool isDateTime(const QString& str);

    QDateTime _dt;
    QString _tdt;
    QString _authors;
    unsigned _recordsCount;
    QString _sourceCode;
    QString _comment;
    QString _targetCode;
    QString _rest;

};

#endif // TMHEADER_H
