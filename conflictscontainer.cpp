#include "conflictscontainer.h"


ConflictsContainer::ConflictsContainer(QObject *parent) :
    QAbstractListModel(parent)
{
}

unsigned ConflictsContainer::conflictedRecordsCount() const
{
    unsigned count = 0;
    foreach(unsigned i, _sortedConflicts.keys())
        count = count + i;
    return count;
}

/**
  *
  */
void ConflictsContainer::onNext() {
    emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
    if(_currentConflict != _sortedConflicts.end())
        ++_currentConflict;
    if(_currentConflict == _sortedConflicts.end()) {
        --_currentConflict;
	return;
    }
    emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
}

/**
  *
  */
void ConflictsContainer::onPrev() {
    emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
    if(_currentConflict != _sortedConflicts.begin()) {
        --_currentConflict;
        emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
    }
}

/**
  *
  */
void ConflictsContainer::selectOnClick(const QModelIndex& index) {
    QModelIndex tmp = _selected;
    _selected = index;
    emit dataChanged(tmp, tmp);
    emit dataChanged(_selected, _selected);
}

/**
  *
  */
void ConflictsContainer::forceBegin() {
    _currentConflict = _sortedConflicts.begin();
    emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
}

/**
  *
  */
void ConflictsContainer::onRequestRowDeletion(const QModelIndex& index) {
    (*_currentConflict)->removeRecordAtRow(index.row()/2);
    emit dataChanged(index, index);
}

/**
  *
  */
void ConflictsContainer::onRequestAllDeletion() {
    QList<ContentRecord* >::iterator fd = (*_currentConflict)->begin();
    while(!(*_currentConflict)->isEmpty())
        fd = (*_currentConflict)->erase(fd);
    _currentConflict = _sortedConflicts.erase(_currentConflict);
    emit dataChanged(this->index(0, 0), this->index((*_currentConflict)->size()*2-1, 0));
}

/**
  * Slot wolany, gdy cos ma byc odlozone na poxniej
  */
void ConflictsContainer::onRequestDump() {
   QList<ContentRecord* > list = (*_currentConflict)->conflictedRecords();
   QMultiMap<unsigned, ConflictRecord* >::iterator tmp = _currentConflict;
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
void ConflictsContainer::onRequestDuplicatedDeletion() {
    QList<ContentRecord* >::iterator fd = (*_currentConflict)->begin();
    QList<ContentRecord* >::iterator look;
    while(fd != (*_currentConflict)->end()) {
	look = fd;
	++look;
        for(; look != (*_currentConflict)->end(); ) {
	    if(QString::compare((*fd)->target(), (*look)->target()) == 0) {
                look = (*_currentConflict)->erase(look);
	    } else ++look;
	}
	++fd;
    }
}
