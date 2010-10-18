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

    static void findInnerConflicts(GlossaryFile* it);

signals:

public slots:

    GlossaryFile* mergeFiles(GlossaryFile* one, GlossaryFile* two) const;

private:

    static void findDuplicated(const FuzzyStrings& key, GlossaryFile *it);

};

#endif // FILEMERGER_H
