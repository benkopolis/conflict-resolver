#ifndef GLOSSARYFILE_H
#define GLOSSARYFILE_H

#include <QObject>
#include <QMultiHash>
#include "fuzzystrings.h"
#include "contentrecord.h"
#include <QFile>
#include <QDate>

class GlossaryFile : public QObject
{
Q_OBJECT
public:
    explicit GlossaryFile(QObject *parent = 0);

    virtual bool processWithTabs(QFile & file) ;

    bool isDateTime(const QString& str, QDate* date, QTime* time) const;
    inline QMultiHash<FuzzyStrings, ContentRecord* > * content() { return _content; }
    inline QMultiHash<FuzzyStrings, ContentRecord* > * conflicts() { return _conflicts; }



signals:

public slots:

    void findInnerConflicts();

protected:

    void findDuplicated(QMultiHash<FuzzyStrings, ContentRecord* >::iterator key);

    QMultiHash<FuzzyStrings, ContentRecord* > * _content;
    QMultiHash<FuzzyStrings, ContentRecord* > * _conflicts;
    QString _header;



};

#endif // GLOSSARYFILE_H
