#ifndef CONFLICTRECORD_H
#define CONFLICTRECORD_H

#include <QObject>
#include "contentrecord.h"
#include <QHash>
#include "inifile.h"

#define SIMVAL (IniFile::instance()->m_fval == 0 ? 75 : IniFile::instance()->m_fval)

class ConflictRecord : public QObject
{
Q_OBJECT
public:
    explicit ConflictRecord(QObject *parent = 0);
    virtual ~ConflictRecord();

    bool operator == (const ConflictRecord& another) const;
    bool operator != (const ConflictRecord& another) const;

    bool addRecord(ContentRecord* record);
    bool recordMatch(ContentRecord* record);
    inline QList<ContentRecord* > conflictedRecords() { return _keys; }
    inline unsigned conflictedRecordsCount() { return _keys.size(); }
    inline unsigned size() const { return _conflictedRecords->keys().size(); }

    inline bool contains(ContentRecord* r) const { return _conflictedRecords->contains(r); }
    bool contains(ConflictRecord* r) const;

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
