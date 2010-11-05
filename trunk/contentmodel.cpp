#include <QFile>
#include <QStack>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include "contentmodel.h"
#include "tmrecord.h"
#include "inifile.h"
#include "tmsaver.h"
#include "tmfile.h"

bool operator < (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two) {
    return one.size() < two.size();
}

//bool operator == (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two);

bool operator > (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two) {
    return one.size() > two.size();
}

///
///		CONSTRUCTORS
///

/**
  *
  */
ContentModel::ContentModel(QObject *parent) :
    QAbstractListModel(parent)
{
    _type = UNKNOWN;
    _conflictsCount = 0;
    _dontFilterConflicts = true;
    _ascending = false;
    _corrupted = 0;
    _all = 0;
    _fuzzyValue=0;
    _mainFile = 0;
    _fuzzyCount=0;
}

/**
  *
  */
ContentModel::ContentModel(ContentType type, QObject *parent):
    QAbstractListModel(parent)
{
    _type = type;
    _conflictsCount = 0;
    _dontFilterConflicts = true;
    _ascending = false;
    _corrupted = 0;
    _all = 0;
    _fuzzyValue=0;
    _fuzzyCount=0;
    _mainFile = 0;
}

///
///	    PUBLIC METHODS
///

/**
  *
  */
int ContentModel::rowCount ( const QModelIndex & parent ) const {
	return (*_sortedList).size()*2;
}

/**
  *
  */
QVariant ContentModel::data ( const QModelIndex & index, int role ) const {
    if(index.row()%2 == 0) {
	return (*_sortedList).at(index.row()/2)->source();
    } else if(index.row()%2 == 1) {
	return (*_sortedList).at(index.row()/2)->target();
    }
    return QVariant();
}

/**
  *
  */
bool ContentModel::setData ( const QModelIndex & index, const QVariant & value, int role ) {
    QString val = qvariant_cast<QString>(value);
    if(index.row()%2 == 0)
    {
	(*_sortedList).at(index.row()/2)->setSource(val);
	return true;
    }
    else if(index.row()%2 == 1)
    {
	(*_sortedList).at(index.row()/2)->setTarget(val);
	return true;
    }
    return false;
}

/**
  *
  */
ContentRecord* ContentModel::realData(const QModelIndex& index) {
    return (*_sortedList).at(index.row()/2);
}

/**
  *
  */
bool ContentModel::addFile(QString fileName) {
    QFile file(fileName);
    bool res = false;
    _files.append(fileName);
    //qDebug() << "adding new file!" << endl;
    if(file.open(QIODevice::ReadWrite | QIODevice::Text) == false) {
	//qDebug() << "Nie udalo sie otworzyc pliku" << endl;
	return false;
    }
    GlossaryFile* gf = 0;
    if(_type == TM)
        gf = new TMFile(this);
    else if(_type == GLOSSARY)
        gf = new GlossaryFile(this);
    res = gf->processWithTabs(file);
    file.close();
    _corrupted += gf->corrupted();
    this->_openedFiles.insert(fileName, gf);
    if(_mainFile == 0)
	_mainFile = gf;
    else
    {
	GlossaryFile *tmp_gf = _merger.mergeFiles(_mainFile, gf);
	if(tmp_gf == 0)
	    return false;
	_mainFile = tmp_gf;
    }
    if(_mainFile != 0)
	_merger.findInnerConflicts(_mainFile);
    else
	return false;
    _currentList = _conflicts.begin();
    emit totalRecords(_mainFile->allCount());
    emit corruptedCount(_mainFile->corrupted());
    emit fuzzyCount(_merger.fuzzyCount());
    emit conflictsCount(_merger.conflictsCount(), _merger.duplicatedCount());
    return res;
}


QList<QRect> ContentModel::itemsSourceRects(const QModelIndex& index) {
    return (*_sortedList).at(index.row())->sourceRects();
}

QStringList ContentModel::itemsSourceStrings(const QModelIndex& index) {
    return (*_sortedList).at(index.row())->sourceStrings();
}

QList<QRect> ContentModel::itemsTargetRects(const QModelIndex& index) {
    return (*_sortedList).at(index.row())->targetRects();
}

QStringList ContentModel::itemsTargetStrings(const QModelIndex& index) {
    return (*_sortedList).at(index.row())->targetStrings();
}

QRect ContentModel::itemsRect(const QModelIndex& index) {
    return (*_sortedList).at(index.row())->boundingRect();
}


bool ContentModel::checkWithAntiDict(QString dict, bool s, bool t, QString duties) {
    QFile f(dict);
    if(f.open(QFile::ReadOnly) == false || this->_openedFiles.isEmpty())
        return false;
    QHash<QString, unsigned> d;
    while(f.atEnd() == false) {
        QString temp(f.readLine());
//        temp.append(QChar(' '));
        d[temp] = 0;
    }
    qDebug() << "Wielkosc anty: " << d.size();
    f.close();
    QStack<ContentRecord* > toRemove;
    GlossaryFile* gf = this->_openedFiles.begin().value();
    QMultiHash<FuzzyStrings, ContentRecord* > *con = gf->content();
    qDebug() << "Wielkosc content: " << con->size();
    foreach(ContentRecord* cr, con->values()) {
        foreach(QString word, d.keys()) {
            if(s && cr->source().contains(word, Qt::CaseInsensitive))
                toRemove.push_front(cr);
            else if(t && cr->target().contains(word, Qt::CaseInsensitive))
                toRemove.push_front(cr);
        }
    }
    qDebug() << "Wielkosc remove: " << toRemove.size();
    QFile rejected(duties);
    if(rejected.open(QFile::Append | QFile::ReadWrite) == false) {
	qDebug() << "Nie udalo sie otworzyc duties.txt";
	return false;
    }
//    rejected.close();
    QTextStream rej(&rejected);
    rej << "moge pisac?" << endl;
    foreach(ContentRecord* cr, toRemove) {
        QString line = cr->toRecordString();
        rej << line << endl;
        FuzzyStrings fk = con->key(cr);
        con->remove(fk, cr);
    }
    rejected.close();
    return true;
}



/**
  *
  *			    PUBLIC SLOTS
  */

/**
  *
  */
void ContentModel::unsort() {
    QMultiMap<int, QList<ContentRecord* > >::iterator iter = _sortedConflicts.begin();
    _conflicts.clear();
    while(iter != _sortedConflicts.end()) {
	FuzzyStrings fs(iter->at(0)->source());
	_conflicts.insert(fs, *iter);
	++iter;
    }
    _currentList = _conflicts.begin();
}

/**
  *
  */
void ContentModel::sort() {
    QHash<FuzzyStrings, QList<ContentRecord* > >::iterator hashIter = _conflicts.begin();
    _sortedConflicts.clear();
    while(hashIter != _conflicts.end()) {
	_sortedConflicts.insertMulti(0 - hashIter->size(), *hashIter);
	++hashIter;
    }
    _sortedList = _sortedConflicts.begin();
}

bool ContentModel::saveContent(QString file) {
    if(_mainFile == 0)
        return false;
    return _mainFile->saveContent(file);
}

/**
  *
  */
bool ContentModel::saveReversedContent(QString file) {
    if(_mainFile == 0)
        return false;
    return _mainFile->saveReversedContent(file);
}

/**
  *
  */
void ContentModel::onRequestItemToCountRects(const QRect& rect) {
    QList<ContentRecord* >::iterator ii = _sortedList->begin();
    int i = 0;
    while(ii != _sortedList->end()) {
	ContentRecord* r = *ii;
	r->countDrawDate(QFontMetrics(QString("Courier New")), rect, i);
	++ii;
	i += r->boundingRect().height();
    }
}

/**
  *
  */
bool ContentModel::onRequestSaveDump(QString dumpFile) {
    QFile f(dumpFile);
    if(f.open(QIODevice::Append) == false) {
	//qDebug() << " nie udalo sie otworzyc DUMP " << endl;
	return false;
    }
    QTextStream fs(&f);
    if(f.size() == 0) {
;//	fs << _header << endl;
    }
    QList<ContentRecord* >::iterator ii;
    for(ii = _dump.begin(); ii != _dump.end() ; ++ii) {
	fs << (*ii)->toRecordString() << endl;
    }
    f.close();
    _dump.clear();
    return true;
}

/**
  *
  */
void ContentModel::filterContent() {
//    TMRecord* tmr = 0;
}

/**
  *
  */
void ContentModel::onNext() {
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
    if(_sortedList != _sortedConflicts.end())
	++_sortedList;
    if(_sortedList == _sortedConflicts.end()) {
	--_sortedList;
	return;
    }
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
}

/**
  *
  */
void ContentModel::onPrev() {
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
    if(_sortedList != _sortedConflicts.begin()) {
	--_sortedList;
	emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
    }
}

/**
  *
  */
void ContentModel::selectOnClick(const QModelIndex& index) {
    QModelIndex tmp = _selected;
    _selected = index;
    emit dataChanged(tmp, tmp);
    emit dataChanged(_selected, _selected);
}

/**
  *
  */
void ContentModel::forceBegin() {
    _sortedList = _sortedConflicts.begin();
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
}

/**
  *
  */
void ContentModel::onRequestRowDeletion(const QModelIndex& index) {
    (*_currentList).removeAt(index.row()/2);
    emit dataChanged(index, index);
}

/**
  *
  */
void ContentModel::onRequestAllDeletion() {
    QList<ContentRecord* >::iterator fd = (*_sortedList).begin();
    while(!(*_sortedList).isEmpty())
	fd = (*_sortedList).erase(fd);
    _sortedList = _sortedConflicts.erase(_sortedList);
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
}

/**
  * Slot wolany, gdy cos ma byc odlozone na poxniej
  */
void ContentModel::onRequestDump() {
   QList<ContentRecord* > list = *_sortedList;
   QMultiMap<int, QList<ContentRecord* > >::iterator tmp = _sortedList;
   _dump.append(list);
   ++tmp;
   if(tmp == _sortedConflicts.end()) {
       this->onPrev();
   } else
       this->onNext();
   --tmp;
   _sortedConflicts.erase(tmp);
}

/**
  *
  */
void ContentModel::onRequestDuplicatedDeletion() {
    QList<ContentRecord* >::iterator fd = (*_sortedList).begin();
    QList<ContentRecord* >::iterator look;
    while(fd != (*_sortedList).end()) {
	look = fd;
	++look;
	for(; look != (*_sortedList).end(); ) {
	    if(QString::compare((*fd)->target(), (*look)->target()) == 0) {
		look = (*_sortedList).erase(look);
	    } else ++look;
	}
	++fd;
    }
}

/**
  *
  *	PRIVATE METHODS
  *
  */

/**
  *
  */
bool ContentModel::isGoodDateTime(TMRecord* tmp) {
    if(tmp != 0 && QDateTime(tmp->date(), tmp->time()) < _filter && _ascending == true) {
	return false;
    } else if(tmp != 0 && QDateTime(tmp->date(), tmp->time()) > _filter && _ascending == false) {
	return false;
    } else
	return true;
}

/**
  *
  */
void ContentModel::countConflicts() {
    _conflictsCount = 0;
    QHash<FuzzyStrings, QList<ContentRecord* > >::iterator ii, jj;
    for( ii = _conflicts.begin(); ii != _conflicts.end(); ++ii) {
//	for (jj = _conflicts.begin();jj != _conflicts.end(); ++jj){
//	    if(jj.key().similarity(ii.key()) >= this->_fuzzyValue) {
//		foreach(ContentRecord* cr, jj.value()) {
//		    ii.value().push_back(cr);
//		}//// dodac fuzzyValue do gui
//		++_fuzzyCount;
//	    }
//	    //// dodaje jj do listy ii
//	    //// po zamknieciu okna rozwiazywania konflitkow, porzadkuje FStr, zeby sie nie powtarzaly
//	    //// to znaczy, przy zapisywanie TM lub GLOSS do pliku, zapisane rekordy daje do hashmapy
//	}
	const QList<ContentRecord* >& tmp = ii.value();
	if(tmp.size() > 1) { // conflicts means every list with size bigger then 1
	    ++_conflictsCount;
	}
    }
    emit conflictsCount(_merger.conflictsCount(), _merger.duplicatedCount());
}

/**
  *
  */


/**
  *
  */
int ContentModel::priority(QList<ContentRecord* >& list) {
    return list.size();
}













