#include "fuzzystrings.h"
#include <QHash>
#include <QTextStream>

uint qHash(const FuzzyStrings & key) {
    return qHash(key.base());
}

FuzzyStrings::FuzzyStrings(QObject *parent) :
    QObject(parent)
{
}

FuzzyStrings::FuzzyStrings(const QString& aBase, QObject *parent) :
    QObject(parent),
    _base(aBase.trimmed())
{
}

FuzzyStrings::FuzzyStrings(const FuzzyStrings& another):
    QObject(another.parent()),
    _base(another._base)
{
}

FuzzyStrings& FuzzyStrings::operator = (const FuzzyStrings& another) {
    if(&another == this)
	return *this;
    _base = another._base;
    return *this;
}

/**
  * Zwraca procentowo wyra¿on¹ wartoœæ podobieñstwa zadanego stringa, do stringa wewnêtrznego.
  */
unsigned FuzzyStrings::similarity(const QString& str) const {
    QString one(str), two(this->_base);
    QTextStream given(&one);
    QTextStream inner(&two);
    unsigned gwCount, iwCount;
    QRegExp rexp(QString("\\s"));
    gwCount = str.count(rexp) + 2;
    iwCount = this->base().count(rexp) + 2;
    QStringList t=str.split(rexp), s=this->base().split(rexp);
    unsigned **arr;
    unsigned res = 0, cost = 0;
    arr = new unsigned* [iwCount];
    for(unsigned i=0; i < iwCount; ++i) {
	arr[i] = new unsigned [gwCount];
	for(unsigned g=0; g < gwCount; ++g) {
	    arr[i][g] = 0;
	}
    }
    for(unsigned i=0; ; ++i) {
	if(i < iwCount) {
	    arr[i][0] = i;
	}
	if(i < gwCount) {
	    arr[0][i] = i;
	}
	if(i > gwCount && i > iwCount)
	    break;
    }
    /// koniec inicjalizacji
//    for i from 1 to m
//	for j from 1 to n
//	    if s[i] = t[j] then cost := 0
//			   else cost := 1
//	    d[i, j] := minimum(d[i-1, j] + 1,       // usuwanie
//			       d[i, j-1] + 1,       // wstawianie
//			       d[i-1, j-1] + cost)  // zamiana
    for(unsigned i=1; i < iwCount; ++i) {
	for(unsigned g=1; g<gwCount; ++g) {
	    if(s.at(i) == t.at(g))
		cost = 0;
	    else
		cost = 1;
	    if(arr[i-1][g] < arr[i][g-1] && arr[i-1][g]+1 < arr[i-1][g-1]+cost)
		arr[i][g] = arr[i-1][g] + 1;
	    else if(arr[i][g-1] < arr[i-1][g] && arr[i][g-1]+1 < arr[i-1][g-1]+cost)
		arr[i][g] = arr[i][g-1]+1;
	    else
		arr[i][g] = arr[i-1][g-1]+cost;
	}
    }
    res =  arr[iwCount-1][gwCount-1];
    float avg = iwCount + gwCount;
    avg = avg / 2;
    res = (avg - res)/avg;
    res = res*100;

    /// czyszczenie
    for(unsigned i = 0; i < iwCount; ++i) {
	delete [] arr[i];
    }
    delete [] arr;
    return res;
}

/**
  * Zwraca procentowo wyra¿on¹ wartoœæ podobieñstwa zadanego fuzzystringa.
  */
unsigned FuzzyStrings::similarity(const FuzzyStrings& str) const {
    return this->similarity(str.base());
}

bool FuzzyStrings::operator == (const FuzzyStrings& another) const {
    if(another._base == this->_base)
	return true;
    return false;
}
