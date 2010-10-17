#ifndef GLOSSARYFILE_H
#define GLOSSARYFILE_H

#include <QObject>
#include <QMultiHash>
#include "fuzzystrings.h"
#include "contentrecord.h"
#include <QFile>
#include <QDate>
#include "conflictrecord.h"

class GlossaryFile : public QObject
{
Q_OBJECT
public:
    explicit GlossaryFile(QObject *parent = 0);

    virtual bool processWithTabs(QFile & file) ;

    bool isDateTime(const QString& str, QDate* date, QTime* time) const;
    inline QMultiHash<FuzzyStrings, ContentRecord* > * content() { return _content; }
    inline QMultiHash<FuzzyStrings, ConflictRecord* > * conflicts() { return _conflicts; }
    inline unsigned corrupted() const { return _corrupted; }
    inline unsigned allCount() const { return _all; }


signals:

public slots:

    void findInnerConflicts();
    bool saveContent(QString file);
    bool saveReversedContent(QString file);

protected:

    void findDuplicated(const FuzzyStrings& key) const;

    QMultiHash<FuzzyStrings, ContentRecord* > * _content;
    QMultiHash<FuzzyStrings, ConflictRecord* > * _conflicts;
    QString _header;
    unsigned _corrupted;
    unsigned _all;



};

#endif // GLOSSARYFILE_H
