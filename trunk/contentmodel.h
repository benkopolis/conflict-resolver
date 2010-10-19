#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QFile>
#include <QList>
#include <QColor>
#include <QHash>
#include <QMultiMap>
#include <QRect>
#include "contentrecord.h"
#include "tmrecord.h"
#include "fuzzystrings.h"
#include "tmheader.h"
#include "glossaryfile.h"


//////
////// duties.txt - plik na bledne itp rekordy
//////

bool operator < (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two);
//bool operator == (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two);
bool operator > (const QList<ContentRecord* >& one, const QList<ContentRecord* >& two);


class ContentModel : public QAbstractListModel
{
Q_OBJECT
public:

    enum ContentType { GLOSSARY, TM, UNKNOWN };

    explicit ContentModel(QObject *parent = 0);
    explicit ContentModel(ContentType type, QObject *parent = 0);
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    /**
      * Dodaje zawartosc pliku, do reszty zawartosci. W zaleznosci od przekazanych do modelu informacji
      * moze byc dokonywana automatyczna filtracja.
      */
    virtual bool addFile(QString fileName);

    /**
      * Zapisywanie zawartosci.
      */
    bool saveContent(QString file);
    /**
      * Zapisywanie odwroconej bazy
      */
    bool saveReversedContent(QString file);
    /**
      * Zapisywanie zawartosci, oraz zapisywanie rezczy odlozonych na pozniej
      */
    bool saveContent(QString file, QString dumpFile);

    inline void setDateTime(const QDateTime& dt) { _filter = dt; };
    inline void setAscending(const bool asc) { _ascending = asc; };
    inline void setDontFilterConflicts(const bool dfc) {_dontFilterConflicts = dfc; };
    inline QModelIndex selected() const { return _selected; };
    inline ContentType type() const { return _type; };
    ContentRecord* realData(const QModelIndex& index);
    inline unsigned contentSize() const { return _conflicts.size(); }
    inline unsigned sortedContentSize() const { return _sortedConflicts.size(); };
    inline unsigned dumpSize() const { return _dump.size(); }

    QList<QRect> itemsSourceRects(const QModelIndex& index); // rects, sometimes multi for one line
    QStringList itemsSourceStrings(const QModelIndex& index); // simple lines o strings
    QList<QRect> itemsTargetRects(const QModelIndex& index); // rects, sometimes multi for one line
    QStringList itemsTargetStrings(const QModelIndex& index); // simple lines o strings
    QRect itemsRect(const QModelIndex& index);

    inline QHash<FuzzyStrings, QList<ContentRecord* > >* conflicts() { return &_conflicts; }

    bool checkWithAntiDict(QString dict, bool s, bool t);

signals:

    void conflictsCount(unsigned count);
    void fuzzyCount(unsigned count);
    void totalRecords(unsigned count);
    void corruptedCount(unsigned count);

public slots:

    void unsort();
    void sort();

    /**
      * Iteruje po aktualnej liscie konfliktow, powodujac, ze wszystkie
      * rekordy przeliczaja na nowo swoj wyglad.
      */
    void onRequestItemToCountRects(const QRect& rect);

    /**
      *
      */
    bool onRequestSaveDump(QString dumpFile);
    /**
      * Wykonywane jest filtrowanie zawawrtosci.
      */
    void filterContent();
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

private:

    void countConflicts();
    bool isGoodDateTime(TMRecord* tmp) ;
    static int priority(QList<ContentRecord* >& list);




    QMultiMap<int, QList<ContentRecord* > >::iterator _sortedList;
    QHash<FuzzyStrings, QList<ContentRecord* > >::iterator _currentList;
    unsigned _conflictsCount;
    unsigned _corrupted;
    unsigned _fuzzyCount;
    unsigned _all;
    QModelIndex _selected;
    QString _dumpFile;
    QStringList _files;
    QList<ContentRecord* > _dump;
    QDateTime _filter;
    bool _ascending;
    ContentType _type;
//    QMap <unsigned, ContentRecord* > * _records;
    QHash<FuzzyStrings, QList<ContentRecord* > > _conflicts;
    QMultiMap<int, QList<ContentRecord* > > _sortedConflicts; // TODO
    bool _dontFilterConflicts;

    GlossaryFile* _mainFile;
    QHash<QString, GlossaryFile* > _openedFiles;

    unsigned _fuzzyValue;
};

#endif // CONTENTMODEL_H
