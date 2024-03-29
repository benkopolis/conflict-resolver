#ifndef GLOSSARYFILE_H
#define GLOSSARYFILE_H

#include <QObject>
#include <QMultiHash>
#include "fuzzystrings.h"
#include "records/contentrecord.h"
#include <QFile>
#include <QDate>
#include "records/conflictrecord.h"
#include "tmheader.h"
#include "commons/error.h"

class FileMerger;

class GlossaryFile : public QObject
{
Q_OBJECT
public:

    friend class FileMerger;

    explicit GlossaryFile(QObject *parent = 0);

    virtual Error processWithTabs(QFile & file) ;
    virtual TMHeader header() const;

    bool isDateTime(const QString& str, QDate* date, QTime* time) const;
    inline QMultiHash<FuzzyStrings, ContentRecord* > * content() { return _content; }
    inline QMultiHash<FuzzyStrings, ConflictRecord* > * conflicts() { return _conflicts; }
    inline void setConflicts(QMultiHash<FuzzyStrings, ConflictRecord* > * c) { delete _conflicts; _conflicts = c; }
    inline unsigned corrupted() const { return _corrupted; }
    inline unsigned allCount() const { return _all; }

    static QString correctText(const QString& text);
    static bool validateText(const QString& text, bool* store = 0);
    static QString removeMultiple(const QString& text);
    static int getCapCount(const QRegExp& r, const QString& t);
    static QString replaceSplitters(const QString& word);

private:


signals:

public slots:


    virtual bool saveContent(QString file);
    virtual bool saveReversedContent(QString file);

protected:

    virtual Error processHeader();

    enum Splitters {
        Dot=0,
        Coma=1,
        Colon=2,
        Semicolon=3
    };

    QMultiHash<FuzzyStrings, ContentRecord* > * _content;
    QMultiHash<FuzzyStrings, ConflictRecord* > * _conflicts;
    QString _header;
    unsigned _corrupted;
    unsigned _all;



};

#endif // GLOSSARYFILE_H
