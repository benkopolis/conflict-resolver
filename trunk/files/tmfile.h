#ifndef TMFILE_H
#define TMFILE_H

#include "glossaryfile.h"
#include "tmheader.h"

class TMFile : public GlossaryFile
{
Q_OBJECT
public:
    explicit TMFile(QObject *parent = 0);

    virtual Error processWithTabs(QFile & file) ;
    virtual TMHeader header() const;

signals:

public slots:

    virtual bool saveContent(QString file);
    virtual bool saveReversedContent(QString file);

protected:

    virtual Error processHeader();


    TMHeader _rheader;
};

#endif // TMFILE_H
