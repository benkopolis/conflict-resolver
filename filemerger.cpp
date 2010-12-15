#include "filemerger.h"
#include "inifile.h"
#include <QStack>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include "tmsaver.h"
#include "tmxfile.h"


/***
  czytanie ze strumieni / bezposrednio czy z pliku tymczasowego
  walidacja tekstu - wyslac
  konflikty rozmyte - dubluja sie, poprawic efektywnosc
  */


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

/**
  * Merges two files.
  */
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
    r << one->header().writeHeader() << endl;
    r << ones;
    r << twos;
//    QFile onef("one.txt");
//    onef.open(QIODevice::Append | QIODevice::WriteOnly);
//    QTextStream sonef(&onef);
//    sonef << one->header().writeHeader() << endl;
    //sonef << ones;
//    QFile twof("two.txt");
//    twof.open(QIODevice::Append | QIODevice::WriteOnly);
//    QTextStream stwof(&twof);
//    stwof << twos;
//    onef.close();
//    twof.close();
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
    GlossaryFile* gf = 0;
    if(qobject_cast<TMFile* >(one) != 0)
        gf = new TMFile();
    else if(qobject_cast<TMXFile* >(one) != 0)
	gf = new TMFile();
    else
        gf = new GlossaryFile();
    if(gf->processWithTabs(temp_file) == false)
    {
        delete gf;
        gf = 0;
    }
    temp_file.remove();
    return gf;
}

/**
  * Finds all conflicts in one file.
  */
void FileMerger::findInnerConflicts(GlossaryFile* it)
{
    initCounters();
    QMultiHash<FuzzyStrings, ContentRecord* >::iterator outer, inner;
    QList<FuzzyStrings> keys = it->_content->keys();
    // duplicate and witch identical source search
    foreach(FuzzyStrings fs, keys)
    {
        findDuplicated(fs, it);
    }
    QStack<ConflictRecord*> toRm;
    // find duplicated conflict records
    foreach(ConflictRecord* r, it->conflicts()->values())
    {
        foreach(ConflictRecord* in, it->conflicts()->values())
        {
            if(r->contains(in) && *in != *r)
                toRm.push(in);
        }
    }
    // delete duplicated conflict records
    foreach(ConflictRecord* rm, toRm)
    {
        it->conflicts()->remove(it->conflicts()->key(rm), rm);
    }
    if(_fuzzySearch == true)
    {
	// find fuzzy conflicts
        for(outer = it->_content->begin();outer != it->_content->end();++outer)
        {
            for(inner = outer; inner != it->_content->end(); ++inner) {
                if(inner == outer)
                    ++inner;
                if(inner == it->_content->end())
                    break;
                ContentRecord* rinner = inner.value();
                ContentRecord* router = outer.value();
		if(rinner->sourceF().similarity(router->sourceF()) > SIMVAL)
		{
		    ConflictRecord* conr = new ConflictRecord(it);
		    conr->addRecord(rinner);
		    conr->addRecord(router);it->_conflicts->insert(router->sourceF(), conr);
		    ++_conflictsCount;
		    ++_fuzzyCount;
		}
                bool fuzzyok = false;
                foreach(ConflictRecord* confr, it->_conflicts->values(outer.key()))
                {
                    if(confr->recordMatch(inner.value()))
                    {
                        if(confr->contains(inner.value()) == false)
                        {
                                confr->addRecord(inner.value());
                                if(confr->contains(router))
                                    fuzzyok = true;
                                ++_conflictsCount;
                                ++_fuzzyCount;
                        }
                    }
                }
            }
        }
    }
    foreach(ConflictRecord* r, it->conflicts()->values())
    {
	foreach(ConflictRecord* in, it->conflicts()->values())
	{
            if(r->contains(in))
            {
                if(*in != *r)
                    toRm.push(in);
                else if(it->conflicts()->keys(in).size() > 1)
                    toRm.push(in);
	    } else if(r->recordMatch(in) && in != r)
	    {
//		r->merge(in);
//		toRm.push(in);
	    }
	}
    }
    foreach(ConflictRecord* rm, toRm)
    {
	it->conflicts()->remove(it->conflicts()->key(rm), rm);
    }
}

/**
  * Finds duplicated sources (and targets - if t-s pair is duplicated it is marked for remove)
  * and creates simple conflicts.
  */
void FileMerger::findDuplicated(const FuzzyStrings& key, GlossaryFile * it)
{
    const QList<ContentRecord* > vals = it->_content->values(key);
    qDebug() << "ilosc tych samych wartosci: " << vals.size();
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
		    bool none = true;
                    foreach(ConflictRecord* confr, it->_conflicts->values(key))
                    {
                        if(confr->recordMatch(*jj))
                        {
			    none = false;
			    confr->addRecord(*jj);
                            ++_conflictsCount;
			}
                    }
		    if(none)
		    {
			ConflictRecord* confr = new ConflictRecord(it);
			confr->addRecord(*jj);
			confr->addRecord(*ii);
			it->_conflicts->insert((*ii)->sourceF(), confr);
		    }
                }
            }
        }
    }
    _duplicatedCount += toRemove.size();
    it->_all -= toRemove.size();
    foreach(ContentRecord* contr, toRemove.values())
        it->_content->remove(contr->sourceF(), contr);
}

/**
  * Finds conflicts and treating @param context as innery-resolved.
  */
void FileMerger::findConflictsInContext(GlossaryFile* it, GlossaryFile* context)
{
    initCounters();
    QMultiHash<FuzzyStrings, ContentRecord* >::iterator outer, inner;
    QList<FuzzyStrings> keys = context->_content->keys();
    // duplicate and witch identical source search
    foreach(FuzzyStrings fs, keys)
    {
	findDuplicated(fs, it);
    }
    QStack<ConflictRecord*> toRm;
    // find duplicated conflict records
    foreach(ConflictRecord* r, it->conflicts()->values())
    {
	foreach(ConflictRecord* in, it->conflicts()->values())
	{
	    if(r->contains(in) && *in != *r)
		toRm.push(in);
	}
    }
    // delete duplicated conflict records
    foreach(ConflictRecord* rm, toRm)
    {
	it->conflicts()->remove(it->conflicts()->key(rm), rm);
    }
    if(_fuzzySearch == true)
    {
	// find fuzzy conflicts
	for(outer = context->_content->begin();outer != context->_content->end();++outer)
	{
	    for(inner = it->_content->begin(); inner != it->_content->end(); ++inner) {
		ContentRecord* rinner = inner.value();
		ContentRecord* router = outer.value();
		if(rinner->sourceF().similarity(router->sourceF()) > SIMVAL)
		{
		    ConflictRecord* conr = new ConflictRecord(it);
		    conr->addRecord(rinner);
		    conr->addRecord(router);it->_conflicts->insert(router->sourceF(), conr);
		    ++_conflictsCount;
		    ++_fuzzyCount;
		}
		bool fuzzyok = false;
		foreach(ConflictRecord* confr, it->_conflicts->values(outer.key()))
		{
		    if(confr->recordMatch(inner.value()))
		    {
			if(confr->contains(inner.value()) == false)
			{
				confr->addRecord(inner.value());
				if(confr->contains(router))
				    fuzzyok = true;
				++_conflictsCount;
				++_fuzzyCount;
			}
		    }
		}
	    }
	}
    }
    foreach(ConflictRecord* r, it->conflicts()->values())
    {
	foreach(ConflictRecord* in, it->conflicts()->values())
	{
	    if(r->contains(in))
	    {
		if(*in != *r)
		    toRm.push(in);
		else if(it->conflicts()->keys(in).size() > 1)
		    toRm.push(in);
	    }
	}
    }
    foreach(ConflictRecord* rm, toRm)
    {
	it->conflicts()->remove(it->conflicts()->key(rm), rm);
    }
}



//  wnetrze find inner conflicts w ktorejs petl - zostawiam na wszelki wypadek, ale zalatwilem to inaczej
//                if(fuzzyok == false)
//                {
//                    if(rinner->sourceF().similarity(router->sourceF()) > SIMVAL)
//                    {
//                        ConflictRecord* conr = new ConflictRecord(it);
//                        conr->addRecord(rinner);
//                        conr->addRecord(router);it->_conflicts->insert(router->sourceF(), conr);
//                        ++_conflictsCount;
//                        ++_fuzzyCount;
//                    }
//                }
