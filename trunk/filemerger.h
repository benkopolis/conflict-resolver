#ifndef FILEMERGER_H
#define FILEMERGER_H

#include <QObject>
#include "tmfile.h"
#include "glossaryfile.h"

class FileMerger : public QObject
{
Q_OBJECT
public:
    explicit FileMerger(QObject *parent = 0);



signals:

public slots:

    GlossaryFile* mergeFiles(GlossaryFile* one, GlossaryFile* two) const;

};

#endif // FILEMERGER_H
