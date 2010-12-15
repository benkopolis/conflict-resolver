#ifndef TMXFILE_H
#define TMXFILE_H


#include <QtXml>
#include "files/glossaryfile.h"
#include "records/tmxrecord.h"

class TMXFile : public GlossaryFile
{
Q_OBJECT
public:
    explicit TMXFile(QObject *parent = 0);

    virtual bool processWithTabs(QFile & file) ;
    virtual TMHeader header() const;

signals:

public slots:

protected:

    virtual bool processHeader();
    virtual bool processBody(QDomElement body);

private:

    QDomDocument _doc;
    TMHeader _tmxHeader;
    QDomElement _body;
    QDomElement _header;
};

#endif // TMXFILE_H
