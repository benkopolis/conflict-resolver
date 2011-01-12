#ifndef TMXRECORD_H
#define TMXRECORD_H

#include <QtXmlPatterns>
#include <QtXml>
#include "tmrecord.h"

class TMXRecord : public TMRecord
{
Q_OBJECT
public:
    explicit TMXRecord(QObject *parent = 0);

    virtual QString toListString() const;
    virtual QString toRecordString() const;
    virtual QString toReversedRecordString() const;

signals:

public slots:

};

#endif // TMXRECORD_H
