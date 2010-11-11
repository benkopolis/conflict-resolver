#ifndef FUZZYSTRINGS_H
#define FUZZYSTRINGS_H

#include <QObject>
#include <QStringList>

class FuzzyStrings;

uint qHash(const FuzzyStrings & key);

class FuzzyStrings : public QObject
{
Q_OBJECT
public:

    friend uint qHash(const FuzzyStrings & key);

    explicit FuzzyStrings(QObject *parent = 0);
    FuzzyStrings(const QString& aBase, QObject *parent = 0);
    FuzzyStrings(const FuzzyStrings& another);

    /**
      * Zwraca procentowo wyrażoną wartość podobieństwa zadanego stringa, do stringa wewnętrznego.
      */
    unsigned similarity(const QString& str) const;

    /**
      * Zwraca procentowo wyrażoną wartość podobieństwa zadanego fuzzystringa.
      */
    unsigned similarity(const FuzzyStrings& str) const;

    /**
      * Zwraca bazowy string
      */
    inline QString base() const { return _base; };

    /**
      * Pozwala ustawic bazowy string.
      */
    inline void setBase(const QString& aBase) { _base = aBase.trimmed(); };

    bool operator == (const FuzzyStrings& another) const;
    FuzzyStrings& operator = (const FuzzyStrings& another);

signals:

public slots:

private:

    QString _base;
};

#endif // FUZZYSTRINGS_H
