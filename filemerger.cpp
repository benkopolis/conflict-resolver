#include "filemerger.h"
#include "inifile.h"
#include <QStack>
#include <QTextStream>
#include <QDateTime>
#include "tmsaver.h"

FileMerger::FileMerger(QObject *parent) :
    QObject(parent)
{
    initCounters();
}

void FileMerger::initCounters()
{
    _duplicatedCount = 0;
    _conflictsCount = 0;
    _fuzzyCount = 0;
}

GlossaryFile* FileMerger::mergeFiles(GlossaryFile* one, GlossaryFile* two) const {
    if(one == 0 || two == 0)
        return 0;
    QString ones, twos, rs;
    QTextStream ostr(&ones), tstr(&twos), r(&rs);
    TMSaver tms;
    if(one->header().sourceCode() != two->header().sourceCode())
        return 0;
    if(one->header().targetCode() != two->header().targetCode())
        return 0;
    TMHeader tmp_h;
    tms.saveContent(ostr, tmp_h, *one->content(), one->allCount());
    tms.saveContent(tstr, tmp_h, *two->content(), two->allCount());
    r << one->header().writeHeader();
    r << ones;
    r << twos;
    QString temp_file_name("Zby_TMP_F");
    temp_file_name.append(QDateTime::currentDateTime().toString("d.M.yy.Hmsz"));
    QFile temp_file(temp_file_name);
    if(temp_file.open(QIODevice::WriteOnly | QIODevice::Text) == false)
        return 0;
    else
    {
        QTextStream stemp(&temp_file);
        stemp << rs;
    }
    temp_file.close();
    if(temp_file.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        return 0;
    GlossaryFile* gf = new GlossaryFile();
    if(gf->processWithTabs(temp_file) == false)
    {
        delete gf;
        gf = 0;
    }
    temp_file.remove();
    return gf;
}

void FileMerger::findInnerConflicts(GlossaryFile* it)
{
    QMultiHash<FuzzyStrings, ContentRecord* >::iterator outer, inner;
    QList<FuzzyStrings> keys = it->_content->keys();
    foreach(FuzzyStrings fs, keys)
    {
        findDuplicated(fs, it);
    }
    for(outer = it->_content->begin();outer != it->_content->end();++outer)
    {
        for(inner = outer; inner != it->_content->end(); ++inner) {
            if(inner == outer)
                ++inner;
            if(inner == it->_content->end())
                break;
            foreach(ConflictRecord* confr, it->_conflicts->values(outer.key()))
            {
                if(confr->recordMatch(inner.value()))
                {
                    if(confr->contains(inner.value()) == false)
                    {
                            confr->addRecord(inner.value());
                            ++_conflictsCount;
                            ++_fuzzyCount;
                    }
                }
            }
        }
    }
}


void FileMerger::findDuplicated(const FuzzyStrings& key, GlossaryFile * it)
{
    const QList<ContentRecord* > vals = it->_content->values(key);
    QMultiHash<FuzzyStrings, ContentRecord* > toRemove;
    for(QList<ContentRecord* >::const_iterator ii = vals.begin(); ii != vals.end(); ++ii)
    {
        for(QList<ContentRecord* >::const_iterator jj = ii; ii != vals.end(); ++ii)
        {
            ++jj;
            if(jj == vals.end())
                break;
            if((*ii)->source() == (*jj)->source())
            {
                if((*ii)->target() == (*jj)->target())
                {
                    toRemove.insertMulti(key, *jj);
                }
                else
                {
                    foreach(ConflictRecord* confr, it->_conflicts->values(key))
                    {
                        if(confr->recordMatch(*jj))
                        {
                            confr->addRecord(*jj);
                            ++_conflictsCount;
                        }
                    }
                }
            }
        }
    }
    _duplicatedCount += toRemove.size();
    foreach(ContentRecord* contr, toRemove.values())
        it->_content->remove(contr->sourceF(), contr);
}