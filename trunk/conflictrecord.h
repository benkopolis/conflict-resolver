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
    inline QList<ContentRecord* > conflictedRecords() { return _conflictedRecords.keys(); };

signals:

public slots:

protected:

    QHash<ContentRecord* , short> * _conflictedRecords;

};

#endif // CONFLICTRECORD_H
