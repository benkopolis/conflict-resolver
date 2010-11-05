#ifndef TMXFILE_H
#define TMXFILE_H

#include "glossaryfile.h"
#include "tmxfile.h"

class TMXFile : public GlossaryFile
{
Q_OBJECT
public:
    explicit TMXFile(QObject *parent = 0);

signals:

public slots:

};

#endif // TMXFILE_H
