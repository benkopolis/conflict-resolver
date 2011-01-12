#ifndef TMXFILE_H
#define TMXFILE_H


#include <QtXml>
#include "files/glossaryfile.h"
#include "records/tmxrecord.h"
#include <QMultiHash>

class TMXFile : public GlossaryFile
{
Q_OBJECT
public:
    explicit TMXFile(QObject *parent = 0);

    virtual Error processWithTabs(QFile & file) ;
    virtual TMHeader header() const;

signals:

public slots:

    virtual bool saveContent(QString file);
    virtual bool saveReversedContent(QString file);

protected:

    virtual Error processHeader(QFile &file);
    virtual Error processBody(QDomElement body, QFile &file);
    virtual Error validateDocument(QString version, QFile &file);

private:

    QDomDocument _doc;
    TMHeader _tmxHeader;
    QDomElement _body;
    QDomElement _header;
    QHash<QString, QMultiHash<FuzzyStrings, ContentRecord* > * > _langs;
    TMHeader _rheader;
};

#endif // TMXFILE_H
