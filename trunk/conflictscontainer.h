#ifndef CONFLICTSCONTAINER_H
#define CONFLICTSCONTAINER_H

#include <QObject>
#include <QAbstractListModel>
#include "contentrecord.h"
#include "filemerger.h"
#include "conflictrecord.h"


class ConflictsContainer : public QAbstractListModel
{
Q_OBJECT
public:
    explicit ConflictsContainer(QObject *parent = 0);

    friend class FileMerger;
    friend class ContentModel;

signals:


public slots:

    /**
      * Slot wolany na akcje next - zmienia atualna liste
      */
    void onNext();
    /**
      * Slot wolany na akcje prev - zmienia aktualna liste
      */
    void onPrev();
    /**
      * Slot wolany na wybranie elementu z listy
      */
    void selectOnClick(const QModelIndex& index);
    /**
      * Wymusza poczatkowe odswierzenie
      */
    void forceBegin();
    /**
      * Wolany na usuniecie pojedynczego elementu
      */
    void onRequestRowDeletion(const QModelIndex& index);
    /**
      * Wolany na usuniecie listy wyswietlanych elementow
      */
    void onRequestAllDeletion();
    /**
      * Wolany na przeniesienie elementow na pozniej
      */
    void onRequestDump();
    /**
      * Wolany na usuniecie powtarzajacych sie, z pozostawieniem jednego reprezentanta
      */
    void onRequestDuplicatedDeletion();

protected:

    QMultiMap<unsigned, ConflictRecord* > _conflicts;

};

#endif // CONFLICTSCONTAINER_H
