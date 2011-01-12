#ifndef CONTENTRECORD_H
#define CONTENTRECORD_H

#include <QObject>
#include <QRect>
#include <QFontMetrics>
#include <QStringList>
#include <QDebug>
#include "fuzzystrings.h"

class ContentRecord : public QObject
{
Q_OBJECT
public:

    typedef enum { None, NotResolved, Confirmed, Delayed, Denied } ConflictStatus;


    explicit ContentRecord(QObject *parent = 0);
    ContentRecord( QString source ,QString target , unsigned lineNumber , QObject * parent = 0 );

    inline unsigned lineNumber() const { return _lineNumber; };
    inline void setLineNumber(unsigned lineNumber) { _lineNumber = lineNumber; }

    inline QString source() const { return _source.base(); };
    inline void setSource(const QString & source ) { _source = FuzzyStrings(source); };
    inline QString target() const { return _target.base(); };
    inline void setTarget( const QString & target ) { _target = FuzzyStrings(target); };

    inline FuzzyStrings sourceF() const { return _source; };
    inline void setSourceF(const QString & source ) { _source = (source); };
    inline FuzzyStrings targetF() const { return _target; };
    inline void setTargetF( const QString & target ) { _target = (target); };

    inline QString comment() const { return _comment; }
    inline void setComment( const QString & comment) { _comment = comment; }


    virtual QString toListString() const;
    virtual QString toRecordString() const;
    virtual QString toReversedRecordString() const;

    void countDrawDate(const QFontMetrics& metrics, const QRect& size, int offsetFromTop);

    QList<QRect> sourceRects() const;
    QList<QRect> targetRects() const;
    QStringList sourceStrings() const;
    QStringList targetStrings() const;
    QRect boundingRect() const;

    inline ConflictStatus status() const { return _status; };


signals:

public slots:

    inline void confirmInConflict() { _status = Confirmed; };
    inline void delayInConflict() { if(_status == NotResolved || _status==Denied) _status = Delayed; };
    inline void toResolve() { if(_status == None) _status=NotResolved; };
    inline void denyInConflict() { if(_status==NotResolved) _status= Denied; };

protected:

    QRect _last;
    QRect _bounding;
    QList<QRect> _sourceRects;
    QList<QRect> _targetRects;
    QStringList _sourceStrings;
    QStringList _targetStrings;
    unsigned _lineNumber;
    QFontMetrics _metrics;

    QString _attributes[3];

    FuzzyStrings _source;
    FuzzyStrings _target;
    QString _comment;
    ConflictStatus _status;


private:


    void makeLists(QString tmp, QRect p, int lineH, int charsInLine,
			  QStringList& _splitted, QList<QRect>& _coloringRects);

};

#endif // CONTENTRECORD_H
