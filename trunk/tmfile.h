#ifndef TMFILE_H
#define TMFILE_H

#include "glossaryfile.h"
#include "tmheader.h"

class TMFile : public GlossaryFile
{
Q_OBJECT
public:
    explicit TMFile(QObject *parent = 0);

    virtual bool processWithTabs(QFile & file) ;
    virtual TMHeader header() const;

    void processHeader();

signals:

public slots:

protected:
    TMHeader _rheader;
};

#endif // TMFILE_H
