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
    foreach(ConflictRecord* ii, this->_conflictedRecords->keys()) {
        if(!another._conflictedRecords->contains(ii))
            return false;
    }
    return true;
}

bool ConflictRecord::operator != (const ConflictRecord& another) const
{
    if(another._conflictedRecords->size() != this->_conflictedRecords->size())
        return true;
    foreach(ConflictRecord* ii, this->_conflictedRecords->keys()) {
        if(!another._conflictedRecords->contains(ii))
            return true;
    }
    return false;
}

bool ConflictRecord::addRecord(ContentRecord* record)
{
    if(this->_conflictedRecords->contains(record))
        return false;
    this->_conflictedRecords[record] = 0;
    return true;
}
