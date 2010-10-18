#include "conflictrecord.h"

ConflictRecord::ConflictRecord(QObject *parent) :
    QObject(parent)
{
    _conflictedRecords = new QHash<ContentRecord* , short>();
}

ConflictRecord::~ConflictRecord() {
    delete _conflictedRecords;
}

bool ConflictRecord::operator == (const ConflictRecord& another) const
{
    if(another._conflictedRecords->size() != this->_conflictedRecords->size())
        return false;
    foreach(ContentRecord* ii, this->_conflictedRecords->keys()) {
        if(!another._conflictedRecords->contains(ii))
            return false;
    }
    return true;
}

bool ConflictRecord::operator != (const ConflictRecord& another) const
{
    if(another._conflictedRecords->size() != this->_conflictedRecords->size())
        return true;
    foreach(ContentRecord* ii, this->_conflictedRecords->keys()) {
        if(!another._conflictedRecords->contains(ii))
            return true;
    }
    return false;
}

bool ConflictRecord::addRecord(ContentRecord* record)
{
    if(this->_conflictedRecords->contains(record))
        return false;
    this->_conflictedRecords->insert(record, 0);//[record] = 0;
    _keys = this->_conflictedRecords->keys();
    return true;
}

void ConflictRecord::removeRecordAtRow(unsigned row) 
{
    QHash<ContentRecord* , short>::iterator ii = this->_conflictedRecords->begin();
    for(int i = 0; i != row; ++ i)
        ++ii;
    this->_conflictedRecords->erase(ii);
}

QList<ContentRecord* >::iterator ConflictRecord::erase(QList<ContentRecord* >::iterator it)
{
    this->_conflictedRecords->remove(*it);
    return this->_keys.erase(it);
}
