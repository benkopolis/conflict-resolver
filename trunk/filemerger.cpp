#include "filemerger.h"
#include "inifile.h"
#include <QStack>

FileMerger::FileMerger(QObject *parent) :
    QObject(parent)
{
}

GlossaryFile* FileMerger::mergeFiles(GlossaryFile* one, GlossaryFile* two) const {
    return 0;
}

void FileMerger::findInnerConflicts(GlossaryFile* it) {
    QMultiHash<FuzzyStrings, ContentRecord* >::iterator outer = it->_content->begin(), inner=it->_content->begin();
    QStack<FuzzyStrings> toRemove;
    for(;outer != it->_content->end();++outer) {
// find dulicates and with the same source
        for(inner = outer; inner != it->_content->end(); ++inner) {
            ++inner;
            if(inner == it->_content->end())
                break;
        }
    }
}


void FileMerger::findDuplicated(const FuzzyStrings& key, GlossaryFile * it) {
    const QList<ContentRecord* > vals = it->_content->values(key);
    QMultiHash<FuzzyStrings, ContentRecord* > toRemove;
    for(QList<ContentRecord* >::const_iterator ii = vals.begin(); ii != vals.end(); ++ii) {
        for(QList<ContentRecord* >::const_iterator jj = ii; ii != vals.end(); ++ii) {
            ++jj;
            if(jj == vals.end())
                break;
            if((*ii)->source() == (*jj)->source()) {
                if((*ii)->target() == (*jj)->target())
                    toRemove.insertMulti(key, *jj);
                else
                    it->_conflicts->value(key)->addRecord(*jj);
            }
        }
    }
}
