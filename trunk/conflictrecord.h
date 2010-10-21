#ifndef CONFLICTRECORD_H
#define CONFLICTRECORD_H

#include <QObject>
#include "contentrecord.h"
#include <QHash>

class ConflictRecord : public QObject
{
Q_OBJECT
public:
    explicit ConflictRecord(QObject *parent = 0);
    virtual ~ConflictRecord();

    bool operator == (const ConflictRecord& another) const;
    bool operator != (const ConflictRecord& another) const;

    bool addRecord(ContentRecord* record);
    inline QList<ContentRecord* > conflictedRecords() { return _keys; }
    inline unsigned conflictedRecordsCount() { return _keys.size(); }
    inline unsigned size() { return _conflictedRecords->keys().size(); }
    void removeRecordAtRow(unsigned row);
    inline QList<ContentRecord* >::iterator begin() { return _keys.begin(); }
    inline QList<ContentRecord* >::iterator end() { return _keys.end(); }
    inline QList<ContentRecord* >::const_iterator begin() const { return _keys.begin(); }
    inline QList<ContentRecord* >::const_iterator end() const { return _keys.end(); }
    inline bool isEmpty() const { return this->_conflictedRecords->isEmpty(); }
    QList<ContentRecord* >::iterator erase(QList<ContentRecord* >::iterator it);

signals:

public slots:

protected:

    QHash<ContentRecord* , short> * _conflictedRecords;
    QList<ContentRecord* > _keys;

};

#endif // CONFLICTRECORD_H