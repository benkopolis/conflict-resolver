#ifndef TMSAVER_H
#define TMSAVER_H

#include "saver.h"
#include <QObject>
#include <QString>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QList>
#include "contentrecord.h"
#include "tmheader.h"
#include <QHash>
#include "fuzzystrings.h"


class TMSaver : public Saver
{
Q_OBJECT
public:
    explicit TMSaver(QObject *parent = 0);


    virtual bool saveContent(const QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all);
    virtual bool saveReversedContent(const QString& file, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all);
    virtual bool saveContent(QTextStream& bufor, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all);
    virtual bool saveReversedContent(QTextStream& bufor, TMHeader& rheader, QMultiHash<FuzzyStrings, ContentRecord* >& conflicts, unsigned all);

signals:

public slots:

};

#endif // TMSAVER_H
