#ifndef TMXRECORD_H
#define TMXRECORD_H

#include <QtXmlPatterns>
#include <QtXml>
#include "contentrecord.h"

class TMXRecord : public ContentRecord
{
Q_OBJECT
public:
    explicit TMXRecord(QObject *parent = 0);

signals:

public slots:

};

#endif // TMXRECORD_H
