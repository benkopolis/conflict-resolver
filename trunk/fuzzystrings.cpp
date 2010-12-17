#include "fuzzystrings.h"
#include <QHash>
#include <QTextStream>
#include <QDebug>
#include "inifile.h"
#include  "engine/fuzzyenginethread.h"

uint qHash(const FuzzyStrings & key) {
    return qHash(key.base());
}

FuzzyStrings::FuzzyStrings(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(conflict(uint)), IniFile::instance(), SLOT(onConflict(uint)));
}

FuzzyStrings::FuzzyStrings(const QString& aBase, QObject *parent) :
    QObject(parent),
    _base(aBase.trimmed())
{
    connect(this, SIGNAL(conflict(uint)), IniFile::instance(), SLOT(onConflict(uint)));
}

FuzzyStrings::FuzzyStrings(const FuzzyStrings& another):
    QObject(another.parent()),
    _base(another._base)
{
    connect(this, SIGNAL(conflict(uint)), IniFile::instance(), SLOT(onConflict(uint)));
}

FuzzyStrings& FuzzyStrings::operator = (const FuzzyStrings& another) {
    if(&another == this)
	return *this;
    _base = another._base;
    return *this;
}

void FuzzyStrings::print2DArrToDebug(unsigned** arr, int xlen, int ylen)
{
    QString output;
    QTextStream o(&output);
    for(int i =0; i<ylen; ++i)
    {
	for(int j=0; j<xlen; ++j)
	{
	    o << arr[j][i] << " ";
	}
	o << endl;
    }
    qDebug() << output;
}

/**
  * Zwraca procentowo wyra¿on¹ wartoœæ podobieñstwa zadanego stringa, do stringa wewnêtrznego.
  */
unsigned FuzzyStrings::similarity(const QString& str) {
    QString one(str), two(this->_base);
   // connect(this, SIGNAL(countFuzzy(QString,QString)), IniFile::instance()->fuzzyEngine(),
//	    SLOT(countFuzzy(QString,QString)), Qt::BlockingQueuedConnection);
 //   emit countFuzzy(one, two);
    return IniFile::instance()->fuzzyEngine()->extractResult(one, two);
}

/**
  * Zwraca procentowo wyra¿on¹ wartoœæ podobieñstwa zadanego fuzzystringa.
  */
unsigned FuzzyStrings::similarity(const FuzzyStrings& str) {
    return this->similarity(str.base());
}

bool FuzzyStrings::operator == (const FuzzyStrings& another) const {
    if(another._base == this->_base)
	return true;
    return false;
}
