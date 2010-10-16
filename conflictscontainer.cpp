#include "conflictscontainer.h"


ConflictsContainer::ConflictsContainer(QObject *parent) :
    QAbstractListModel(parent)
{
}

/**
  *
  */
void ConflictsContainer::onNext() {
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
void ConflictsContainer::onPrev() {
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
    if(_sortedList != _sortedConflicts.begin()) {
	--_sortedList;
	emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
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
    _sortedList = _sortedConflicts.begin();
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
}

/**
  *
  */
void ConflictsContainer::onRequestRowDeletion(const QModelIndex& index) {
    (*_currentList).removeAt(index.row()/2);
    emit dataChanged(index, index);
}

/**
  *
  */
void ConflictsContainer::onRequestAllDeletion() {
    QList<ContentRecord* >::iterator fd = (*_sortedList).begin();
    while(!(*_sortedList).isEmpty())
	fd = (*_sortedList).erase(fd);
    _sortedList = _sortedConflicts.erase(_sortedList);
    emit dataChanged(this->index(0, 0), this->index((*_sortedList).size()*2-1, 0));
}

/**
  * Slot wolany, gdy cos ma byc odlozone na poxniej
  */
void ConflictsContainer::onRequestDump() {
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
void ConflictsContainer::onRequestDuplicatedDeletion() {
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
