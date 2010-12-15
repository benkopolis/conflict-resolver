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
ContentModel::ContentModel(bool fuzzySerach, ContentType type, QObject *parent):
    QAbstractListModel(parent)
{
    _merger.setFuzzySearch(fuzzySerach);
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
bool ContentModel::addFile(QString fileName, bool confront) {
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
        if(confront == true)
        {
            _merger.findConflictsInContext(_mainFile, gf);
            gf->setConflicts(_mainFile->conflicts());
        }
	GlossaryFile *tmp_gf = _merger.mergeFiles(_mainFile, gf);
	if(tmp_gf == 0)
	    return false;
	_mainFile = tmp_gf;
    }
    if(_mainFile != 0)
    {
        if(confront == false)
            _merger.findInnerConflicts(_mainFile);
        else
            _mainFile->setConflicts(gf->conflicts());
	_conflicts = _mainFile->conflicts();
    }
    else
	return false;
    emit totalRecords(_mainFile->allCount());
    emit corruptedCount(_mainFile->corrupted());
    emit fuzzyCount(_merger.fuzzyCount());
    emit conflictsCount(_mainFile->conflicts()->size(), _merger.duplicatedCount());
    return res;
}

bool ContentModel::findAgain()
{
    foreach(ConflictRecord* cr, _mainFile->conflicts()->values())
    {
	cr->setParent(0);
	delete cr;
    }
    _mainFile->conflicts()->clear();
    _merger.findInnerConflicts(_mainFile);
    _conflicts = _mainFile->conflicts();
    emit conflictsCount(_mainFile->conflicts()->size(), _merger.duplicatedCount());
    return true;
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
}

/**
  *
  */
void ContentModel::sort() {

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














