#ifndef FILEMERGER_H
#define FILEMERGER_H

#include <QObject>
#include "files/tmfile.h"
#include "files/glossaryfile.h"

class FileMerger : public QObject
{
Q_OBJECT
public:
    explicit FileMerger(QObject *parent = 0);

    virtual void findInnerConflicts(GlossaryFile* it);
    virtual void findConflictsInContext(GlossaryFile* it, GlossaryFile* context);
    inline unsigned duplicatedCount() const { return _duplicatedCount; }
    inline unsigned conflictsCount() const { return _conflictsCount; }
    inline unsigned fuzzyCount() const { return _fuzzyCount; }
    inline void setFuzzySearch(bool f) { _fuzzySearch = f; }
    inline bool fuzzySearch() const { return _fuzzySearch; }

signals:

    void duplicatedCount(unsigned c);

public slots:

    void initCounters();

    /**
      * trzeba pamietac o tym, zeby oba parametry byly tego samego typu - ale moze dzialac chyba tez przy roznych typach,
      * tylko wtedy zrobi sie mieszany plik.
      */
    virtual GlossaryFile* mergeFiles(GlossaryFile* one, GlossaryFile* two) const;

private:

    void findDuplicated(const FuzzyStrings& key, GlossaryFile *it);

    unsigned _duplicatedCount;
    unsigned _conflictsCount;
    unsigned _fuzzyCount;

    bool _fuzzySearch;

};

#endif // FILEMERGER_H
